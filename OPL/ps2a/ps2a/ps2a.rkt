#lang racket

;; recursive procedure for adding the first n natural numbers
;; e.g. (sum-recursive 0) is 0
;;      (sum-recursive 1) is 1
;;	(sum-recursive 2) is 3 [it's 2 + 1]
;;      (sum-recursive 3) is 6 [it's 3 + 2 + 1]
(define (sum-recursive n)
  ;; Base case of 0.
  (if (= n 0)
      0
      (+ n (sum-recursive (- n 1) ))))

;; iterative procedure for the same
(define (sum-iterative n)
  0)

;; recursive procedure for sum of squares of first n natural numbers
;; e.g., (sum-squares-recursive 0) is 0
;; 	 (sum-squares-recursive 1) is 1
;; 	 (sum-squares-recursive 2) is 5 (2^2 + 1^2)
(define (sum-squares-recursive n)
  0)

;; iterative procedure for the same
(define (sum-squares-iterative n)
  0)

;; recursive procedure for sum of squares of first n odd numbers
;; (starting with 1)
;; e.g., (sum-alt-squares-recursive 0) is 0
;; 	 (sum-alt-squares-recursive 1) is 1 (1^2)
;; 	 (sum-alt-squares-recursive 2) is 10 (3^2 + 1^2)
;; 	 (sum-alt-squares-recursive 3) is 35 (5^2 + 3^2 + 1^2)
(define (sum-alt-squares-recursive n)
  0)

;; iterative procedure for the same
(define (sum-alt-squares-iterative n)
  0)

;; following series converges to 2/3
;; (notice alternating addition and subtraction of the terms):
;;
;;  1     1     1     1     1
;; --- - --- + --- - --- + ---  etc.
;;  1     2     4     8     16
;;
;; implement as a recursive process, where the argument is the number of terms  
;; e.g. 
;; (two-thirds-series 0) is 1
;; (two-thirds-series 1) is 1/2
;; (two-thirds-series 2) is 3/4
;; HINTS: even? and odd? are predicates; (expt 2 3) is 2^3.
(define (two-thirds-series-r n)
  1)

;; iterative procedure for the same
(define (two-thirds-series-i n)
  1)

;; SICP exercise 1.11 (pp. 42). In this problem, you implement a
;; recursive mathematical function. Only do the recursive implementation. 
(define (f-recursive n)
  1)

;; SICP exercise 1.16 (pp. 46).
;; complete the fast-expt implementation using an iterative process
(define (fast-expt b n)
  1)

;; When implementing an iterative process in Scheme, the Scheme
;; interpreter uses tail-recursion.  Explain what this means.  Answer
;; this question in a comment block, and change #f to #t.
(define tail-recursion #f)

