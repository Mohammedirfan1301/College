#lang racket

;; ps3a
;; last updated Sun Feb  7 08:46:55 2016 fredm@cs.uml.edu

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define nil '())
;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; making lists from box-and-pointer diagrams
;; referring to the image files included in this assignment,
;; write expressions defining list1, list2, list3, and list4.
;; you may only use the cons procedure -- you may not
;;   use the list procedure nor the quoting function in
;;   creating the lists.
;;
;; for nil, you may either use nil or '().
;;
;; the correct answer is given for list1
;; 
;; note: test cases for these are only provided on the
;; server. providing them in the downloaded test file would
;; give away the answers.
(define list1
  (cons 1 
        (cons 2
              (cons 3 nil))))

(define list2 
  1)

(define list3
  1)

(define list4
  1)

;; now, define statements to produce these lists using
;; the quoting function (equivalent to their printed form).
;; the solution for list1 is provided as an exemplar
(define listq1
  '(1 2 3))

(define listq2
  '())

(define listq3
  '())

(define listq4
  '())

;; create box-and-pointer diagrams for the following list5 through list8.
;; you may create ASCII art and submit as comments,
;; or you may upload image files. Only PNG and JPG files may be 
;; submitted.
;; change each flag from #f to #t for each image you upload.
;; note: some of these may not be clean lists.

(define list5
  (cons 1 (list 2 3)))

(define list5flag #f)

(define list6
  (cons 3 (cons 4 5)))

(define list6flag #f)

(define list7
  (list 3 (cons 4 (list 5 6))))

(define list7flag #f)

(define list8
  (list (cons 3 4) (list 5 6)))

(define list8flag #f)

;; write procedures to sum up a list of numbers
;; first do it with recursive process, then iterative process
;; the base case must be that the sum of an empty list is 0.
(define (sum-list-r lst)
  1)

(define (sum-list-i lst)
  1)


;; Consider the following recursive procedure:
(define (list-prod lst) 
  (if (null? lst) 
      1 
      (* (car lst) 
         (list-prod (cdr lst))))) 

;; Answer (a) (b) and (d) using comment lines and change #f to #t 
;; For (c), fill in the procedure

;; a) How many times is list-prod called when evaluating the
;; expression (list-prod '(1 2 3 4)) ?
(define lpa #f)

;; b) What is the order of growth in space and time for the list-prod
;; procedure above?
(define lpb #f)

;; c) Write an iterative version of the procedure list-prod.
(define (list-prod-iter lst)
  1)

;; d) What is the order of growth in space and time for your iterative
;; list-prod procedure from part c?
(define lpd #f)

;; write a recursive definition / recursive process procedure
;; to compute sum of products of pairs of numbers in a list
;; e.g. 
;;   (sum-of-prods '(1 2 3 4 5 6)
;; should compute
;;   (+ (* 1 2) (+ (* 3 4) (+ (* 5 6) 0)))
;; which is 44.
;; please assume your fcn will always be given a list with
;;   an even number of numbers.
;; however, make sure the base case input of empty list
;;   produces a return value of 0.
(define (sum-of-prods lst)
  0)


;; SICP exercise 2.20 (pp. 104), on the dotted-tail notation.
;; While answering this question you may write helper procedures
(define (same-parity first . lst)
  1)

