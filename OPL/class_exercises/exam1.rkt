#lang racket

(define nil '())

(define (merge lst1 lst2)
    (cond
      ((null? lst1) lst2)   ;; keep merging list 2.
      ((null? lst2) lst1)   ;; keep merging list 1.
      ((equal? (car lst1) (car lst2)) nil)  ;; Deal with duplicates?
      (else  ;; else cons list1 / list2 together.
        (cons (car lst1) (cons (car lst2)
              (merge (cdr lst1) (cdr lst2)))))))

(define list1 (list 1 3 5 6))
(define list2 (list 2 4 6 8 10 12))

(define (square x) (* x x))

(define (apply-twice func)
  (lambda (x) (func (func x))))

(define (make-item item-name value condition)
 (list (cons item-name value) condition))

(define (item-name rec)
  (caar rec))

(define (item-value rec)
  (cdar rec))

(define (item-condition rec)
  (cadr rec))

(define (cons x y)
 (lambda (m)
   (cond ((eq? m 1) x)
         ((eq? m 2) y)
         (else ("error?")))))