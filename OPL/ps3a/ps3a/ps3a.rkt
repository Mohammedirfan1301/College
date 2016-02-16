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
(define list1                        ;; (1 2 3)
  (cons 1 
        (cons 2
              (cons 3 nil))))

(define list2   ;; Should look like this in Racket: (1 (2 3) 4)
  (cons 1                            ;; (1
        (cons (cons 2 (cons 3 nil))  ;; '(2 3)
              (cons 4 nil))))        ;;  4)
                    

(define list3   ;; Should look like this in Racket: ((1 2) (3 4))
  (cons (cons 1 (cons 2 nil)) ;; '(1 2)
              (cons (cons 3 (cons 4 nil)) nil)))  ;; '(3 4)

(define list4   ;; Should look like this in Racket: ((1 2))
  (cons (cons 1 (cons 2 nil)) nil))

;; now, define statements to produce these lists using
;; the quoting function (equivalent to their printed form).
;; the solution for list1 is provided as an exemplar
;; This should be (1 2 3) in Racket.
(define listq1
  '(1 2 3))

;; Should look like this in Racket: (1 (2 3) 4)
(define listq2
  '(1 (2 3) 4))

;; Should look like this in Racket: ((1 2) (3 4))
(define listq3
  '((1 2) (3 4)))

;; Should look like this in Racket: ((1 2))
(define listq4
  '((1 2)))

;; create box-and-pointer diagrams for the following list5 through list8.
;; you may create ASCII art and submit as comments,
;; or you may upload image files. Only PNG and JPG files may be 
;; submitted.
;; change each flag from #f to #t for each image you upload.
;; note: some of these may not be clean lists.

(define list5
  (cons 1 (list 2 3)))

;  ASCII Art below. → / ↓ are pointers to lists / cons.
;
;  [1][→]  [↓][/]
;          [2][→]  [3][/]
;

(define list5flag #t)

(define list6
  (cons 3 (cons 4 5)))

;  ASCII Art below. → / ↓ are pointers to lists / cons.
;
;  [3][→] [4][5]
;

(define list6flag #t)

(define list7
  (list 3 (cons 4 (list 5 6))))

;  ASCII Art below. → / ↓ are pointers to lists / cons.
;
;  [↓][/]
;  [3][→]  [4][→]  [↓][/]
;                  [5][→]  [6][/]
;

(define list7flag #t)

(define list8
  (list (cons 3 4) (list 5 6)))

;  ASCII Art below. → / ↓ are pointers to lists / cons.
;
;  [↓][→]      [↓][/]
;  [3][↓]      [5][→]  [6][/]
;     [4][/]

(define list8flag #t)

;; write procedures to sum up a list of numbers
;; first do it with recursive process, then iterative process
;; the base case must be that the sum of an empty list is 0.
(define (sum-list-r lst)
  (if (eq? lst '())
      0  ;; Base case of 0 + whatever
      (+ (car lst)
         (sum-list-r (cdr lst)))))

(define (sum-list-i lst)
  (define (iter-helper sum lst) ;; Iterative helper function
    (if (eq? lst '())  ;; '() is basically nil / null
        sum    ;; Base case
        (iter-helper (+ (car lst) sum)  ;; Feed in the sum
                     (cdr lst))         ;; Keep moving down the list.
    )
  ) ;; Seed iter-helper with 0 for sum and the top of the list.
  (iter-helper 0 lst)
)


;; Consider the following recursive procedure:
(define (list-prod lst) 
  (if (null? lst) 
      1 
      (* (car lst) 
         (list-prod (cdr lst))
      )
  )
) 

;; Answer (a) (b) and (d) using comment lines and change #f to #t 
;; For (c), fill in the procedure

;; a) How many times is list-prod called when evaluating the
;; expression (list-prod '(1 2 3 4)) ?
;
;  The stack would look like this:  
;  (* 1 (* 2 (* 3 (* 4 (* 1)))))
;  
;  This would mean list-prod would be called 5 times, 
;  since it would be called for 1, 2, 3, 4 and then finally
;  1 for null. It looks like this: (1 * 2 * 3 * 4 * 1)
;
(define lpa #t)

;; b) What is the order of growth in space and time for the list-prod
;; procedure above?
(define lpb #f)

;; c) Write an iterative version of the procedure list-prod.
(define (list-prod-iter lst)
  (define (iter-helper prod lst) ;; Iterative helper function
    (if (eq? lst '())  ;; '() is basically nil / null
        prod    ;; Base case
        (iter-helper (* (car lst) prod)  ;; Feed in the sum
                     (cdr lst))         ;; Keep moving down the list.
    )
  ) ;; Seed iter-helper with 0 for sum and the top of the list.
  (iter-helper 1 lst)
)

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
  (if (null? lst) 
      0 
      (+ 
         (* (car lst) (cdr lst))
         (list-prod  (cddr lst))
      )
  )
)


;; SICP exercise 2.20 (pp. 104), on the dotted-tail notation.
;; While answering this question you may write helper procedures



(define (same-parity first . lst)
  (define (iter-helper return lst) ;; Iterative helper function
    (if (null? lst)
        ;; return the list now, but in reverse order since it was found
        ;; in reverse and must be adjusted.
        (reverse return)
        
        ;; Otherwise keep adding just odd or even numbers, depending on which
        ;; one we started with.
        (iter-helper (if (even? first)                ;; Determine if the first number is odd or even.
                         
                         ;; even case
                         (if (even? (car lst))
                             (cons (car lst) return)  ;; Only add even numbers in this case!
                             return                   ;; Just pass the list.
                         )
                         
                         ;; odd case
                         (if (odd? (car lst))
                             (cons (car lst) return)  ;; Add only ODD numbers in this case.
                             return                   ;; Keep passing the list.
                         )
                     ) ;; This whole thing is the return list.
                     (cdr lst))                       ;; Keep moving along the chain in the list.
    )
  )
  (iter-helper (list first) lst)   ;; The seed is the first item, along with the lst we are checking.
)
