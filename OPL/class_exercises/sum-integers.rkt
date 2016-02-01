#lang racket
(define (cube x)
  (* x (* x x)))

;; Problem 1
(define (sum-integers n m)
  ;; detect base case of n == m, e.g. 10 equals 10
  (if ( = n m )
      m  ;; return base case of 'm'
      (+ n (sum-integers (+ n 1) m)))) ;; else case does a recursive call for adding numbers
;; n + (n+1) + (n+2) + (n+3) ... etc until (n == m), which returns m, and ends the recusion.

;; Problem 2
;; (same as problem 1 but with cubes)
;; Currently gives the wrong answer
(define (sum-cubes n m)
  ;; detect base case of n^3 == m^3, e.g. 10 equals 10
  (if ( > n m )
      (cube m)  ;; return base case of 'm^3'
      (+ (cube n) (sum-cubes (+ n 1) m ) ) )) ;; else case does a recursive call for adding numbers
;; this one does n(cube) + n+1(cube) + etc

;; Problem 3
;; Sum every other integers.
;; Appears to work for (3, 10)
(define (sum-alt-int n m)
  (if ( > n m)
      0
      (+ n (sum-alt-int (+ n 2) m))))