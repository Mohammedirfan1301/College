#lang racket

;;;+++++++++++++++ Starter Code ++++++++++++++++++++++++++++++++++++++

;;; re-written by fredm using hash instead of mutable pairs
(define (make-table)
  (let ((local-table (make-hash)))
    (define (lookup key-1 key-2)
      (hash-ref local-table (list key-1 key-2) #f))
    (define (insert! key-1 key-2 value)
      (hash-set! local-table (list key-1 key-2) value)
      )
 ;     'ok)
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc!) insert!)
            (else (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc!))

;;; Code for the generic arithmetic system.  Start
;;; to read and understand here.
(define (attach-tag type-tag contents)
  (cons type-tag contents))

(define (type-tag datum)
  (if (pair? datum)
      (car datum)
    (display (list "Bad tagged datum -- TYPE-TAG" datum))))

(define (contents datum)
  (if (pair? datum)
      (cdr datum)
    (display (list "Bad tagged datum -- CONTENTS" datum))))

(define (square x) (* x x))

(define (install-rectangular-package)
  ;; internal procedures
  (define (real-part z) (car z))
  (define (imag-part z) (cdr z))
  (define (make-from-real-imag x y) (cons x y))
  (define (magnitude z)
    (sqrt (+ (square (real-part z))
             (square (imag-part z)))))
  (define (angle z)
    (atan (imag-part z) (real-part z)))
  (define (make-from-mag-ang r a) 
    (cons (* r (cos a)) (* r (sin a))))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'rectangular x))
  (put 'real-part '(rectangular) real-part)
  (put 'imag-part '(rectangular) imag-part)
  (put 'magnitude '(rectangular) magnitude)
  (put 'angle '(rectangular) angle)
  (put 'make-from-real-imag 'rectangular
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'rectangular
       (lambda (r a) (tag (make-from-mag-ang r a))))
  )
;  "installed rectangular package")

(define (install-polar-package)
  ;; internal procedures
  (define (magnitude z) (car z))
  (define (angle z) (cdr z))
  (define (make-from-mag-ang r a) (cons r a))
  (define (real-part z)
    (* (magnitude z) (cos (angle z))))
  (define (imag-part z)
    (* (magnitude z) (sin (angle z))))
  (define (make-from-real-imag x y) 
    (cons (sqrt (+ (square x) (square y)))
          (atan y x)))

  ;; interface to the rest of the system
  (define (tag x) (attach-tag 'polar x))
  (put 'real-part '(polar) real-part)
  (put 'imag-part '(polar) imag-part)
  (put 'magnitude '(polar) magnitude)
  (put 'angle '(polar) angle)
  (put 'make-from-real-imag 'polar
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'polar
       (lambda (r a) (tag (make-from-mag-ang r a))))
  )
;  "installed polar package")

(define (real-part z) (apply-generic 'real-part z))
(define (imag-part z) (apply-generic 'imag-part z))
(define (magnitude z) (apply-generic 'magnitude z))
(define (angle z) (apply-generic 'angle z))

(define (make-from-real-imag x y)
  ((get 'make-from-real-imag 'rectangular) x y))

(define (make-from-mag-ang r a)
  ((get 'make-from-mag-ang 'polar) r a))

(define (add x y) (apply-generic 'add x y))
(define (sub x y) (apply-generic 'sub x y))
(define (mul x y) (apply-generic 'mul x y))
(define (div x y) (apply-generic 'div x y))

(define (install-scheme-number-package)
  (define (tag x)
    (attach-tag 'scheme-number x))
  (put 'add '(scheme-number scheme-number)
       (lambda (x y) (tag (+ x y))))
  (put 'sub '(scheme-number scheme-number)
       (lambda (x y) (tag (- x y))))
  (put 'mul '(scheme-number scheme-number)
       (lambda (x y) (tag (* x y))))
  (put 'div '(scheme-number scheme-number)
       (lambda (x y) (tag (/ x y))))
  (put 'make 'scheme-number
       (lambda (x) (tag x)))
  )
 ; "installed scheme number package")

(define (make-scheme-number n)
  ((get 'make 'scheme-number) n))

(define (install-rational-package)
  ;; internal procedures
  (define (numer x) (car x))
  (define (denom x) (cdr x))
  (define (make-rat n d)
    (let ((g (gcd n d)))
      (cons (/ n g) (/ d g))))
  (define (add-rat x y)
    (make-rat (+ (* (numer x) (denom y))
                 (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (sub-rat x y)
    (make-rat (- (* (numer x) (denom y))
                 (* (numer y) (denom x)))
              (* (denom x) (denom y))))
  (define (mul-rat x y)
    (make-rat (* (numer x) (numer y))
              (* (denom x) (denom y))))
  (define (div-rat x y)
    (make-rat (* (numer x) (denom y))
              (* (denom x) (numer y))))
  ;; interface to rest of the system
  (define (tag x) (attach-tag 'rational x))
  (put 'add '(rational rational)
       (lambda (x y) (tag (add-rat x y))))
  (put 'sub '(rational rational)
       (lambda (x y) (tag (sub-rat x y))))
  (put 'mul '(rational rational)
       (lambda (x y) (tag (mul-rat x y))))
  (put 'div '(rational rational)
       (lambda (x y) (tag (div-rat x y))))

  (put 'make 'rational
       (lambda (n d) (tag (make-rat n d))))
  )
;  "installed rational package")

(define (make-rat n d)
  ((get 'make 'rational) n d))

(define (install-complex-package)
  ;; imported procedures from rectangular and polar packages
  (define (make-from-real-imag x y)
    ((get 'make-from-real-imag 'rectangular) x y))
  (define (make-from-mag-ang r a)
    ((get 'make-from-mag-ang 'polar) r a))
  ;; internal procedures
  (define (add-complex z1 z2)
    (make-from-real-imag (+ (real-part z1) (real-part z2))
                         (+ (imag-part z1) (imag-part z2))))
  (define (sub-complex z1 z2)
    (make-from-real-imag (- (real-part z1) (real-part z2))
                         (- (imag-part z1) (imag-part z2))))
  (define (mul-complex z1 z2)
    (make-from-mag-ang (* (magnitude z1) (magnitude z2))
                       (+ (angle z1) (angle z2))))
  (define (div-complex z1 z2)
    (make-from-mag-ang (/ (magnitude z1) (magnitude z2))
                       (- (angle z1) (angle z2))))

  ;; interface to rest of the system
  (define (tag z) (attach-tag 'complex z))
  (put 'add '(complex complex)
       (lambda (z1 z2) (tag (add-complex z1 z2))))
  (put 'sub '(complex complex)
       (lambda (z1 z2) (tag (sub-complex z1 z2))))
  (put 'mul '(complex complex)
       (lambda (z1 z2) (tag (mul-complex z1 z2))))
  (put 'div '(complex complex)
       (lambda (z1 z2) (tag (div-complex z1 z2))))
  (put 'make-from-real-imag 'complex
       (lambda (x y) (tag (make-from-real-imag x y))))
  (put 'make-from-mag-ang 'complex
       (lambda (r a) (tag (make-from-mag-ang r a))))
  )
 ;  "installed complex package")

(define (make-complex-from-real-imag x y)
  ((get 'make-from-real-imag 'complex) x y))

(define (make-complex-from-mag-ang r a)
  ((get 'make-from-mag-ang 'complex) r a))

;;; install packages
(install-rectangular-package)
(install-polar-package)
(install-scheme-number-package)
(install-rational-package)
(install-complex-package)

;;; ALL OF THE MAGIC HAPPENS HERE
;;; make sure you understand this deeply and well
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
          (apply proc (map contents args))
	(display (list
		  "No method for these types -- APPLY-GENERIC"
		  (list op type-tags)))))))

;;; SOME TEST CODE
;(define n1 (make-scheme-number 1))	; (scheme-number . 1)
;(define n2 (make-scheme-number 2))	; (scheme-number . 2)
;;(add n1 n2)				
					; (scheme-number . 3)

;(define r1 (make-rat 3 4))		; (rational 3 . 4)
;(define r2 (make-rat 5 6))		; (rational 5 . 6)
;; (add r1 r2)
					; (rational 19 . 12)

;(define z1 (make-complex-from-real-imag 1 1)) ; (complex rectangular 1 . 1)
;(define z2 (make-complex-from-mag-ang 2 0))   ; (complex polar 2 . 0)
;;; (mul z1 z2)
;;; (complex polar 2.8284271247461903 . 0.7853981633974483)

;;;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; *******************************************************************

;;; Problem 5: Exercise 2.81

;; Louis Reasoner has noticed that apply-generic may try to coerce the
;; arguments to each other's type even if they already have the same
;; type. Therefore, he reasons, we need to put procedures in the coercion
;; table to "coerce" arguments of each type to their own type. For
;; example, in addition to the scheme-number->complex coercion shown
;; above, he would do:

;; (define (scheme-number->scheme-number n) n)
;; (define (complex->complex z) z)
;; (put-coercion 'scheme-number 'scheme-number
;;               scheme-number->scheme-number)
;; (put-coercion 'complex 'complex complex->complex)

;; a. With Louis's coercion procedures installed, what happens if
;; apply-generic is called with two arguments of type scheme-number or
;; two arguments of type complex for an operation that is not found in
;; the table for those types? For example, assume that we've defined a
;; generic exponentiation operation:

;; (define (exp x y) (apply-generic 'exp x y))

;; and have put a procedure for exponentiation in the Scheme-number
;; package but not in any other package:

;; ;; following added to Scheme-number package
;; (put 'exp '(scheme-number scheme-number)
;; (lambda (x y) (tag (expt x y)))) ; using primitive expt

;; What happens if we call exp with two complex numbers as arguments?

;;; PUT YOUR ANSWER HERE
#|

If we to call exp with two complex numbers as arguments, then apply-generic
will fail to obtain the method it needs and end up trying to coerce one complex
type into itself, by recursively calling apply-generic with the same type.
Since this is complex -> complex, apply-generic will end up
recursively calling itself forever.

|#


;; b. Is Louis correct that something had to be done about coercion with
;; arguments of the same type, or does apply-generic work correctly as
;; is?

;;; PUT YOUR ANSWER HERE
; He is wrong, apply-generic works fine as it currently is.

;; c. Modify apply-generic so that it doesn't try coercion if the two
;; arguments have the same type.

;;; PUT YOUR ANSWER HERE
;;; code and explanations





;;; **************************** END OF FILE *************************
