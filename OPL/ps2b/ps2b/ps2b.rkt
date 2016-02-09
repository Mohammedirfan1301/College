#lang racket

;; You may use these functions in your solutions!
;;
;;+++++++++++++++ Required for auto grading; don't remove +++++++++++++
(define (square x) (* x x))
(define (identity x) x)
(define (next x) (+ x 1))
(define (inc n) (+ n 1))
;;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; SICP exercise 1.30 (pp. 60), convert the recursive implementation
;; to iterative.
;;
;; Un-comment and fill in the below procedure
;; "term" is a procedure that transforms parameter "a"
;; "next" is a procedure acts as the successor function

#|
     I based this off of ps2a's iterative functions,
     I just changed it so it works like the recursive version.
|#
(define (sum term a next b)    ;; Sum function.
  (define (iter a result)      ;; Helper function takes A and result
    (if (> a b)   ;; Base case, done when this is true.
        result    ;; Iterative version needs to return result.
        ;; Increment A, and add a to the result variable.
        (iter (next a) (+ (term a) result))))
  (iter a 0))     ;; Seed the iter function with a / 0 for result.

;; Working towards higher-order procedures: Do SICP exercise 1.31 (a)
;; and (b) (pp. 60–61).  fill in the below procedures

;; (a) Recursive product procedure
(define (product1 term a next b)
  (if (> a b)
     1
     (* (term a)
        (product1 term (next a) next b))))

;; factorial procedure in terms of product
(define (factorial n)
  1)

;; Approximations to pi using john wallis' formula
(define (pi-term n)
  ;; Need to detect if the number is odd or even for using
  ;; the John Wallis formula
  (if (even? n)
       (/ (+ n 2) (+ n 1))
       (/ (+ n 1) (+ n 2))
  ))

;; e.g.,
;; (* (product1 pi-term 1 next 6) 4)
;; = 3.3436734693877552 or 3 421/1225


;; (b) Iterative product procedure
(define (product2 term a next b)
(define (iter a result)      ;; Helper function takes A and result
    (if (> a b)   ;; Base case, done when this is true.
        result    ;; Iterative version needs to return result.
        ;; Increment A, and multiply A with the result.
        (iter (next a) (* (term a) result))))
  (iter a 1))     ;; Seed the iter function with a / 1 for result.

;; SICP exercise 1.32 (a only): Implement accumulate and show how sum
;; and product can be defined with calls to accumulate. Specify
;; whether you have built the iterative or recursive version.  fill in
;; the below procedures

;; (a) Recursive process
(define (accumulate combiner null-value term a next b)
  1)

(define (sum1 term a next b)
  1)

(define (product term a next b)
  1)

;; (b) Iterative process
(define (accumulate1 combiner null-value term a next b)
  1)

;; SICP exercise 1.41 (pp. 77): Procedures that return procedures.
;; e.g.
;;  ((double inc) 3) is 5
;;  (((double double) inc) 3) is 7
;;  (((double (double double)) inc) 5) is 21
(define (double f)
  (lambda (z) z))

;; SICP exercise 1.42 (pp. 77): More procedures that return procedures.
;; e.g.,
;;  ((compose inc square) 6) is 37
;;  ((compose square inc) 6) is 49
;;  ((compose (compose square square) square) 2) is 256
;;  ((compose square (compose square square)) 2) is also 256
(define (compose f g)
  (lambda (z) z))

;; Here is an implementation of expnt, a procedure that generates
;; a procedure for raising its input to its argument.
;;
;;     E.g., (expnt 2) generates a procedure for squaring a
;;     number. The provided implementation of expnt generates a
;;     recursive process. Re-implement it as an iterative process
;;     (probably using a helper procedure).
;;
;; generates a procedure that raises its argument to the nth power
;; Recursive process
;; e.g. ((expnt 0) 10) is 1     (10^0)
;;      ((expnt 1) 10) is 10    (10^1)
;;      ((expnt 2) 10) is 100   (10^2)
;;      ((expnt 3) 10) is 1000  (10^3)
(define (expnt n)
  (if (= n 0) (lambda (x) 1)
      (if (= n 1)
          (lambda (x) x)
          (lambda (x) (* x ((expnt (- n 1)) x))))))

;; Iterative process
;; I based this off the recursive implementation, I just modified it so
;; that it ends up being iterative.
(define (expnt-iter n)
  (define (iter a result)        ;; Helper function takes A and result
    (if (= a 0) (lambda (a) 1)   
        (if (= a 1)
            result               ;; Base case
            ;; From the iterative part, uses the helper procedure.
            (lambda (result) (* result ((expnt (- a 1)) result))))))
  (iter n 1))     ;; Seed the iter function with a / 0 for result.
  
  

;; in the following procedures, rewrite to be equivalent
;; by transforming the let expressions into lambda's
(define (proc1 x y)
  (let ((a (+ x y))
	(b (- x y)))
    (+ (square a) (square b))))

(define (proc2 n)
  (let ((a (+ n 1))
	(b (+ n 2))
	(c (+ n 3)))
    (* a b c)))

(define (proc3 n)
  (let ((a (+ n 1)))
    (let ((b (* a 2)))
      (+ a b))))

;; in the following procedures, rewrite to be equivalent
;; by transforming the lambda expressions into let's

(define (proc4 x y)
  ((lambda (a b) (* a b))
   (* 3 x) (/ y 4)))

(define (proc5 n)
  ((lambda (y z) (* (- y 1) (- z 1)))
   (* n 2) (- n 3)))

(define (proc6 a b c)
  ((lambda (n)
     ((lambda (m)
        (* n m))
      (+ a b)))
   (+ b c)))


;;****************************** END OF FILE ******************************
