#lang racket

;; Recursive version of the sum-list function
(define (sum-list lst)
  (if (eq? lst '())
      0
      (+ (car lst)
         (sum-list (cdr lst)))))

;; Iterative version of the sum-list function.
(define (sum-iter lst)
  (define (iter-helper sum lst) ;; Iterative helper function
    (if (eq? lst '())  ;; '() is basically nil / null
        sum    ;; Base case
        (iter-helper (+ (car lst) sum)  ;; Feed in the sum
                     (cdr lst))         ;; Keep moving down the list.
    )
  ) ;; Seed iter-helper with 0 for sum and the top of the list.
  (iter-helper 0 lst)
)