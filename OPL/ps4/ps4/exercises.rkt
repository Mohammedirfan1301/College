#lang racket

;;+++++++++++++++ Required for auto grading +++++++++++++++++++++++++
(define nil '())

(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

;; **********************************************************************

;;1. Exercise 2.36 on pp. 120, accumulating with lists of lists.
;; fill in code where it's got <??> in two places
;;
;; e.g.,
;; (accumulate-n + 0 '((1 2 3) (4 5 6) (7 8 9)))
;; 
;; should be
;; (12 15 18)
;;
;; (define (accumulate-n op init seqs)
;;   (if (null? (car seqs))
;;       nil
;;       (cons (accumulate op init <??>  )
;;             (accumulate-n op init <??> ))))
(define (accumulate-n op init seqs)
  seqs)


;; **********************************************************************

;;2. Exercise 2.53 on pp. 144, testing quote, pair?, and memq.
;; Write the answers and explanation in comment line and change #f to #t

;(list 'a 'b 'c)
(define p2_1 #f)

;(list (list 'george))
(define p2_2 #f)

;(cdr '((x1 x2) (y1 y2)))
(define p2_3 #f)

;(cadr '((x1 x2) (y1 y2)))
(define p2_4 #f)

;(pair? (car '(a short list)))
(define p2_5 #f)

;(memq 'red '((red shoes) (blue socks)))
(define p2_6 #f)

;(memq 'red '(red shoes blue socks))
(define p2_7 #f)

;; **********************************************************************

;;3. Exercise 2.54 on pp. 145, building your own version of equal?.
; Fill in the below procedure

(define (my-equal? list1 list2) 
   1) 

;;4. Exercise 2.55 on pp. 145, pushing the limits of quote.
;
; Eva Lu Ator types to the interpreter the expression
;
; (car ''abracadabra)
; 
; To her surprise, the interpreter prints back quote. Explain.
; 
; Write the answer and explanation for the below procedure call and replace
; #f with #t.

(define p4 #f)

;; **********************************************************************


