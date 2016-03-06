#lang racket

;; Exercise 2.57 on pp. 151.
;; Extend the differentiator to handle sums and products of length 2+.

;; Don't remove the equation1 definition.
(define equation1 '(* x y (+ x 3)))  ; i.e., ((x^2)y + 3xy) dx

;; You will need to change the following procedures:
;; make-sum
;; augend
;; make-product
;; multiplicand

(define (variable? x) (symbol? x))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

;; per dotted-tail procedure notation, second and subsequent args
;; will get made into a list and provided in "augend"
;;
;; the constructor should deal with three cases:
;; [augend empty]      (make-sum 'x) is 'x
;; [augend length 1]   (make-sum 'x 3) is '(+ x 3)
;;                     (make-sum 'x 0) is 'x
;;                     (make-sum 1 2) is 3
;; [augend is 2+]      (make-sum 'x 'y 'x) is '(+ x y z)
;;
;; the code for the length 1 case is quite similar to the original
;; implementation; you should bring it in and modify it
(define (make-sum a1 . augend)
  ;(printf "a1 = ~s\taugend = ~s" a1 augend)
  (cond 
        ;; Null case is just "'x" or whatever a1 is.
        ;(printf "null case")
        ((null? augend) a1)
        
        ;; a1 is zero case.
        ((equal? a1 0) (car augend))
        
        ;; augend is length 1 & zero case.
        ((and (equal? (length augend) 1) 
              (equal? (car augend) 0)) a1)
        
        ;; Length 1 is "'(a1 + augend)
        ((and (equal? (length augend) 1) 
              (number? a1) (number? (car augend))) (+ a1 (car augend)))
        
        ; Otherwise just return a list of + a1 and all the augend values.
        (else (append (list '+ a1) augend))))

(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (addend s) (cadr s))

;; you're allowed to have augend also be a constructor
;; you will need to test for the length of the augend, and do
;; something different the length=1 case and length is 2+ case. 
(define (augend s)
  (cond 
        ;; length = 1 case
        ((equal? (length s) 3) (caddr s))
        
        ;; length = 2+ case
        (else (append (list '+) (cddr s)))))

;; like make-sum, this should work with 1, 2, or 3+ args
;; and perform reductions on 1 and 2 arg cases
(define (make-product m1 . multiplicand)
  ;(printf "a1 = ~s\taugend = ~s" a1 augend)
  (cond 
        ;; Null case is just "'x" or whatever a1 is.
        ;(printf "null case")
        ((null? multiplicand) m1)
        
        ;; m1 is 1 case.
        ((equal? m1 1) (car multiplicand))
        
        ;; multiplicand is length 1 & 1 case.
        ((and (equal? (length multiplicand) 1) 
              (equal? (car multiplicand) 1)) m1)
        
        ;; Length 1 is "'(* m1 augend)
        ((and (equal? (length multiplicand) 1) 
              (number? m1) 
              (number? (car multiplicand))) 
         (* m1 (car multiplicand)))
        
        ; Otherwise just return a list of * m1 and all the multiplicand values.
        (else (append (list '* m1) multiplicand))))

(define (product? x) (and (pair? x) (eq? (car x) '*)))

(define (multiplier p) (cadr p))

;; may also construct a product expression
(define (multiplicand p)
  (cond 
        ;; length = 1 case
        ((equal? (length p) 3) (caddr p))
        
        ;; length is >2, and check for augend
        ;(and (equal? (length p) 3)
             ;(equal? (
        
        ;; length = 2+ case
        (else (append (list '*) (cddr p)))))

;;; differentiation for exponents
(define (make-exponentiation x y)
  (cond ((= y 0) 1)
	((= y 1) x)
	(else (list '** x y))))

(define (exponentiation? x)
  (and (pair? x) (eq? (car x) '**)))

(define (base x) (cadr x))

(define (exponent x) (caddr x))

;;; deriv including exponentiation
(define (deriv exp var)
  (cond ((number? exp) 0)
	((variable? exp)
	 (if (same-variable? exp var) 1 0))
	((sum? exp)
	 (make-sum (deriv (addend exp) var)
		   (deriv (augend exp) var)))
	((product? exp)
	 (make-sum 
	  (make-product (multiplier exp)
			(deriv (multiplicand exp) var))
	  (make-product (deriv (multiplier exp) var)
			(multiplicand exp))))
	((exponentiation? exp)
	 (make-product (exponent exp)
		       (make-product (make-exponentiation (base exp) 
							  (- (exponent exp) 1))
				     (deriv (base exp) var))))
	(else
	 (error "unknown expression type -- DERIV" exp))))


