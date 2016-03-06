#lang racket

;; Exercise 2.58 on pp. 151.
;; Converting the differentiator to infix. Do subproblem (a) only.

;; You will need to change the following procedures:
;; make-sum
;; sum?
;; addend
;; make-product
;; product
;; multiplier
;; make-exponentiation
;; base
;; exponent

(define (variable? x) (symbol? x))

(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))

(define (=number? exp num)
  (and (number? exp) (= exp num)))


;; This should print out: "(x + 3)"
(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
	    ((=number? a2 0) a1)
        ((and (number? a1) (number? a2)) (+ a1 a2))
        ;; Print out like this instead: '(x + 3)
	    (else (list a1 '+ a2))))  

;; This should return "+" in the test file.
(define (sum? x)
  ;; Make it "cadr x" to get the "+"!
  (and (pair? x) (eq? (cadr x) '+)))

;; This should return "x" in the test file.
(define (addend s) (car s))

;; This should return "3" in the test file.
(define (augend s) (caddr s))


;; This should be modified to print out: '(x * 3)")
(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
	    ((=number? m1 1) m2)
	    ((=number? m2 1) m1)
	    ((and (number? m1) (number? m2)) (* m1 m2))
        ;; Print out like this instead: '(x * 3)")
	    (else (list m1 '* m2))))

;; This should print out "#t" for the test case.
(define (product? x) 
  ;; Similar to sum?, we want "cadr" to get to the "*".
  (and (pair? x) (eq? (cadr x) '*)))

;; This should print out "x" for the test file.
(define (multiplier p) (car p))

;; This should return "3" for the test file.
(define (multiplicand p) (caddr p))


;;; differentiation for exponents

;; This should print out: '(x ** 3)
(define (make-exponentiation x y)
  (cond ((= y 0) 1)
	     ((= y 1) x)
        ;; Print out like this instead: '(x ** 3)
	     (else (list x '** y))))

;; This should print out "#t" for the test case.
(define (exponentiation? x)
  ;; Similar to sum? / product?, we want "cadr" to get to the "**".
  (and (pair? x) (eq? (cadr x) '**)))

;; this should print out "'x" for the test file.
(define (base x) (car x))

;; this should print out "3" for the test file.
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
	       (make-sum (make-product (multiplier exp)
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


