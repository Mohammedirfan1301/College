#lang racket

;; ps3b
;; last updated Wed Feb 17 07:49:03 2016 fredm@cs.uml.edu

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define nil '())

(define (square x) (* x x))

(define (scale-list items factor)
  (if (null? items)
      nil
      (cons (* (car items) factor)
            (scale-list (cdr items) factor))))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; Write a procedure called double-list in three different ways:
;; #1 Write a list manipulation procedure of your own to do this.
;; #2 Use the scale-list procedure on pp. 105 in your definition.
;; #3 Use the map procedure on pp. 105 in your definition.

;a)
(define (double-list1 lst)
  1)

;b)
;; using scale-list 
(define (double-list2 lst)
  1)

;c)
;; using map
(define (double-list3 lst)
  1)

;; SICP exercise 2.21 (pp. 106), on square-list.

(define (square-list1 items)
  1)

(define (square-list2 items)
  1)

;; enum-range is a procedure that generates a list of ints
;; beginning with "a" and ending with "b" (inclusive).
;; here is a recursive-process definition:
(define (enum-range a b)
  (if (> a b)
      '()
      (cons a (enum-range (+ a 1) b))))

;; write an iterative-process version of this.
(define (enum-range-i a b)
  1)

;; this is a list of the first 100 natural numbers
(define my-nats (enum-range-i 1 100))

;; using any combinations of maps, filters, accums create the following
;; numeric sequences or values

;; all odd numbers
(define (odds lst) 
  ;; some map/filter expr over
  1)

;; each number tripled
;; e.g. 3, 6, 9, ... , 300
(define (triples lst)
  ;; maps and/or filters over
  1)

;; sum of squares
;; i.e., 1 + 4 + 9 + 16 + ... + 10000
(define (square-sum lst)
  ;; probably an accumulation is involved here
  1)

;; product of each item
;; = 1 * 2 * 3 * ... * 100
(define (products lst)
  1)

;; suppose we have a list of lists.
;; each sublist contains two numbers; e.g.:
;; '((1 2) (3 4) (5 6) (7 8) ... (99 100))
;; write a fcn to accumulate the sum of the products
;; of each of the sublist pairs; i.e.:
;;
;; (1 * 2) + (3 * 4) + ... + (99 * 100)

(define (pair-seq a b)
  (if (> a b)
      '()
      (cons (list a (+ a 1))
	    (pair-seq (+ a 2) b))))

(define my-nat-pairs (pair-seq 1 100))

;; write the accumulation function here
(define (sum-of-prod-lists lst)
  ;; some accum
  1) 

;; now let's do it with a flat list; e.g.
;; if given: '(1 2 3 4 .... 99 100)
;; we want: (1 * 2) + (3 * 4) + ... (99 * 100)
;; you may assume the input list has an even # of elements
;;
;; this is not trivial!
;; the trick is to transform thing coming out of each accum
;; step into two different things depending on whether
;; you've just computed a product, or need to carry forward
;; a multiplicand to the next operation
(define (sum-of-prods lst)
  ;; just need a single accumulation if it's done right
  1)

;; SICP exercise 2.35 (pp. 120), redefining count-leaves as an
;; accumulation.  Fill in the below procedure. Replace '<??>.
;; note! you may recursively call this "count-leaves" fcn
;;  inside of it!
;; e.g.:
;;  (define tree (list 1 2 (list 3 4) (list 5 (list 6 7)))) 
;;  (count-leaves tree) => 7

(define (count-leaves tree)
  (accumulate '<??> '<??> (map '<??> '<??>)))

;; SICP exercise 2.33 (pp. 119), implementing map, append, and
;; length.  Replace '<??> with answer
;;
;; this are tricky little gems!
;; don't look up the answers -- struggle with them!
;;
;; to get credit for these, you must show your work. That might consist
;; of partially-working / partially-broken steps along the way to an
;; answer, or a narrative of what you were thinking about as you worked
;; your way to an answer.

(define (map-from-fold p sequence)
  (accumulate (lambda (x y) '<??> ) nil sequence))

(define (append-from-fold seq1 seq2)
  (accumulate cons '<??> '<??>))

(define (length-from-fold sequence)
  (accumulate '<??> 0 sequence))

;; Solve SICP exercise 2.27 on deep-reverse.
;;
;; Note: it is be easy enough to Google for the answer on this.
;; Obviously this will short-circuit your learning.  So don't do that.
;;
;; TO GET CREDIT FOR THIS: 
;;
;; Show steps along the way to your solution -- e.g., partly working
;; code, what inputs you tested it on, what results it produced, what
;; you did next.
;; 
;; No one spits out a solution for this fully-formed... 

; my-reverse
; this should be reverse the items at the top level of the list
; do this as warm-up
; e.g. 
;  (my-reverse '(1 2 3)) => '(3 2 1)
;  (my-reverse '((1 2) (3 4))) => '((3 4) (1 2))

(define (my-reverse items) 
  items)

; deep reverse
; recursively reverse sublists
; e.g.
;  (deep-reverse '(1 2 3)) => '(3 2 1)
;  (deep-reverse '((1 2) (3 4))) => '((4 3) (2 1))
;  (deep-reverse '((1 2) (3 (4 5)))) => '(((5 4) 3) (2 1))

(define (deep-reverse items) 
  items)

