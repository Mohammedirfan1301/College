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
   (if (null? (car seqs))
       nil
       ;; The first map will return the first element from each sequence.
       ;; The second map will return the remaining elements from each of the sequences.
       (cons (accumulate op init (map car seqs))
             (accumulate-n op init (map cdr seqs) ))))


;; **********************************************************************

;;2. Exercise 2.53 on pp. 144, testing quote, pair?, and memq.
;; Write the answers and explanation in comment line and change #f to #t

;(list 'a 'b 'c)
#|
The interpreter prints out the following: (a b c)
This is because it creates a list containing three symbols,
which is can be printed out as "a b c".
|#
(define p2_1 #t)

;(list (list 'george))
#|
The interpreter prints out: ((george))
This is since a (list (list)) becomes a list of a list,
with an outer list and an inner list, hence the double parentheses.
It prints out "george" inside the two lists because of the quote in 
front of george, which makes it a symbol.
|#
(define p2_2 #t)

;(cdr '((x1 x2) (y1 y2)))
#|
The interpreter prints out: '((y1 y2))
This is because cdr gets the second item in a list, 
which ends up being a list of two symbols.
|#
(define p2_3 #t)

;(cadr '((x1 x2) (y1 y2)))
#|
The interpreter prints out: '(y1 y2)
This is because cadr is "car (cdr)", which first gets 
the cdr of a list, and then the car of that list. Since 
this is a list of two lists containing two symbols each,
cdr of '((x1 x2) (y1 y2))) will print out the same as in p2_3,
'((y1 y2)). Getting the car of "'((y1 y2))" will get the first 
item in that list, which is a list containing two symbols.
|#
(define p2_4 #t)

;(pair? (car '(a short list)))
#|
The interpreter prints out: #f

If we break this down, it makes sense.
First we have the following list: (a short list)
If we then take the car of this list, we get "a"
pair? checks to see if the object is a pair or not,
in this case "a" is not a pair since its just one item.

|#
(define p2_5 #t)

;(memq 'red '((red shoes) (blue socks)))
#|
The interpreter prints out: #f

memq checks to see if a symbol is contained in a list.
It does not check sublists, and since the symbol red 
is inside a sublist it will not be found since memq just
sees two lists, and no symbols since it doesn't check the
two lists inside the main list.

|#
(define p2_6 #t)

;(memq 'red '(red shoes blue socks))
#|
The interpreter prints out: '(red shoes blue socks)

memq checks to see if a symbol is inside a list. The
intreperter was able to find the symbol red in this case
because it is a flat list of four symbols, and the symbol
red is present at the very beginning of the list (although it
could be present anywhere in the list).

Although the placement of the symbol red does matter. Doing a few
test outputs, memq will return the whole list starting when it finds
the symbol red and containing to the end after the symbol.

Example outputs for example:

> (memq 'red '(shoes blue socks red))
'(red)
> (memq 'red '(red shoes blue socks))
'(red shoes blue socks)
> (memq 'red '(shoes red blue socks))
'(red blue socks)

|#
(define p2_7 #t)

;; **********************************************************************

;;3. Exercise 2.54 on pp. 145, building your own version of equal?.
; Fill in the below procedure

(define (my-equal? list1 list2) 
   (cond
         ;; Check to see if the lists are null first.
         ((and (null? list1) (null? list2)) #t)
         
         ;; Check to see if just one of the lists is null.
         ((or (null? list1) (null? list2)) #f)
         
         ;; Compare the two lists recursively.
         ;; Must be a pair, and need to recursively compare
         ;; the two lists by comparing each item, and then cdr
         ;; to the next item.
         ((and (pair? list1) (pair? list2))
          (and (my-equal? (car list1) (car list2))
               (my-equal? (cdr list1) (cdr list2))))
         
         ;; Else call eq?
         (else (eq? list1 list2))))

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

#|

This is because a single quote, ', is the shorter version of "quote".
As a result ''abracadabra is the same thing as '(quote abracadabra),
which if evaluated in the interpreter will return the same thing,
''abracadabra. When you call car on '(quote abracadabra), you get
back a quote, which makes sense since this is a list of two items,
and car gets the first item which is a quote.

|#
(define p4 #t)

;; **********************************************************************


