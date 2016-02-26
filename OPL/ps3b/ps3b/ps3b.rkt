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
  (if (null? lst)
      nil                      ;; base case.
      (cons (* 2 (car lst))    ;; double everything in the list
            (double-list1 (cdr lst)))))  ;; Recursive call.

;b)
;; using scale-list 
(define (double-list2 lst)
  (define (scale-list items factor)
    (if (null? items)
        nil                    ;; base case.
        (cons (* (car items) factor)   ;; double it or whatever.
              (scale-list (cdr items) factor))))  ;; iterative call.
  (scale-list lst 2))  ;; Double it cuz its double list.

;c)
;; using map
(define (double-list3 lst)
  (map (lambda (x) (* x 2)) lst))  ;; (* x 2) doubles it

;; SICP exercise 2.21 (pp. 106), on square-list.

;; Recursive version
(define (square-list1 items)
   (if (null? items)
      nil            ;; base case.
      (cons (* (car items) (car items))  ;; square stuff
            (square-list1 (cdr items))   ;; recursion.
 )))

;; Map version
(define (square-list2 items)
  (map (lambda (x) (* x x)) items))

;; enum-range is a procedure that generates a list of ints
;; beginning with "a" and ending with "b" (inclusive).
;; here is a recursive-process definition:
(define (enum-range a b)
  (if (> a b)
      '()
      (cons a (enum-range (+ a 1) b))))

;; write an iterative-process version of this.
(define (enum-range-i a b)
  (define (iter-enum-range x y)
    (if (> x y)
      nil       ;; base case.
      (cons x (iter-enum-range (+ x 1) y))))  ;; iterative call.
  (iter-enum-range a b)) ;; seed it.

;; this is a list of the first 100 natural numbers
(define my-nats (enum-range-i 1 100))

;; using any combinations of maps, filters, accums create the following
;; numeric sequences or values

;; all odd numbers
(define (odds lst) 
  ;; Simple filter to get only the odd numbers.
  (filter odd? lst))

;; each number tripled
;; e.g. 3, 6, 9, ... , 300
(define (triples lst)
  ;; I used a map to triple each number.
  (map (lambda (x) (* x 3)) lst))

;; sum of squares
;; i.e., 1 + 4 + 9 + 16 + ... + 10000
(define (square-sum lst)
  (if (null? lst)
      0   ;; Base case of zero since its addition.
      ;; add the squares all together.
      (+ (* (car lst) (car lst)) (square-sum(cdr lst)))))

;; product of each item
;; = 1 * 2 * 3 * ... * 100
(define (products lst)
  (if (null? lst)
      1   ;; Base case of ONE since this a product.
      (* (car lst) (products(cdr lst)))))

;; suppose we have a list of lists.
;; each sublist contains two numbers; e.g.:
;; '((1 2) (3 4) (5 6) (7 8) ... (99 100))
;; write a fcn to accumulate the sum of the products
;; of each of the sublist pairs; i.e.:
;;
;; (1 * 2) + (3 * 4) + ... + (99 * 100)

(define (pair-seq a b)
  (if (> a b)
      nil      ;; base case of '().
      (cons (list a (+ a 1))
	    (pair-seq (+ a 2) b))))

(define my-nat-pairs (pair-seq 1 100))

;; write the accumulation function here
(define (sum-of-prod-lists lst)
  ;; Old code here. I did it first using recursion.
  #|
  (if (null? lst)
      0   ;; Base case of zero since its addition.
      
      ;; Add the pairs together.
      ;;  caar lst should return 1
      ;;  cadar lst should return 2
      ;; then we do (* 1 2) which returns 2
      ;; then we do (+ 2 (recursive call))
      ;; in the end we get something like what the assignment asks for:
      ;; (1 * 2) + (3 * 4) + ... etc
      (+ (* (caar lst) (cadar lst)) (sum-of-prod-lists(cdr lst)))))
  |#
  
  ;; Accumulate function here
  (accumulate (lambda (a b)  ;; Using lambda fnc similar to original code.
                      (+ (* (car a) (cadr a)) b))  ;; (1 * 2) + (3 * 4) + ... etc
                      0         ;; Base case of 0.
                      lst))     ;; Passing in the list.
      

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
  ;; Old code here. I did it first using recursion.
  #|
  (if (null? lst)
      0   ;; Base case of zero since its addition.
      
      ;; Add the pairs together.
      ;;  car lst should return 1
      ;;  cadr lst should return 2
      ;; then we do (* 1 2) which returns 2
      ;; then we do (+ 2 (recursive call))
      ;; in the end we get something like what the assignment asks for:
      ;; (1 * 2) + (3 * 4) + ... etc
      (+ (* (car lst) (cadr lst)) (sum-of-prods(cddr lst)))))
  |#
  
  #|
            V1 HERE

  ;; Accumulate function here
  (accumulate (lambda (a b)  ;; Using lambda fnc similar to original code.
                ;; DEBUG CODE
                (printf "a is ~a\nb is ~a\n" a b)
                
                ;; Using cond to figure out what we need to do.
                (cond 
                   ;; First round we must detect the 0 in b.
                   ((equal? 0 b) a)
                   
                   ;; Whenever we get a null, sum / product stuff.
                   ((pair? b) (list a (* (car b) (cadr b))))
                   
                   ;; Else cons together stuff into b.
                   (else (list a b) )
                )
                    
              )
              
              0            ;; Base case of null.
              lst))        ;; Passing in the list.
    |#
  #|  V2 HERE WITH NEARLY WORKING CODE EXCEPT FOR RETURNING THE ANSWER
         AS A LIST...
  ;; Accumulate function here
  (accumulate (lambda (a b)  ;; Using lambda fnc similar to original code.
                ;; DEBUG CODE
                ;; must disable this when submitting or testing!
                ;;(printf "a is ~a\nb is ~a\n" a b)
                
                ;; Using cond to figure out what we need to do.
                (cond 
                   ;; First round we must detect the 0 in b.
                   ((equal? 0 b) a)
                   
                   ;; Detect if b is a number.
                   ((number? b) (list (* a b)))
                   
                   ;; Detect pairs, so we know when to multiply and add together.
                   ;; basically we'd have like
                   ;; (4 30)
                   ;; now we want to do
                   ;; (3*4 + 30)
                   ;; and get something like
                   ;; (42)
                   ((equal? (length b) 2) (list (+ (* a (car b)) (cadr b))))
                   
                   ;; Whenever we get a null, sum / product stuff.
                   ((list? b) (append (list a) b))
                   
                   ;; Current problem: 
                   ;; I GET THE RIGHT ANSWER, BUT IN LIST FORM!!!
                   
                   ;; Else ???
                   (else printf("What am I doing here?\n"))
                )
                    
              )
              
              0            ;; Base case of null.
              lst))        ;; Passing in the list.
    |#
  

  
#|   
Output from the debug version shows how my sum-of-prods works:

(sum-of-prods '(1 2 3 4 5 6))
a is 6 | b is 0
a is 5 | b is (6 0)
a is 4 | b is 30
a is 3 | b is (4 30)
a is 2 | b is 42
a is 1 | b is (2 42)
44

(sum-of-prods '(21 39 71 46 98 11 37 36))
a is 36 | b is 0
a is 37 | b is (36 0)
a is 11 | b is 1332
a is 98 | b is (11 1332)
a is 46 | b is 2410
a is 71 | b is (46 2410)
a is 39 | b is 5676
a is 21 | b is (39 5676)
6495

|#
  
  ;; Technically this is like 3 lines of code but I added a ton of comments
  ;; for future reference.
  (accumulate (lambda (a b)  ;; Using lambda fnc similar to original code.
                ;; DEBUG CODE
                ;; must disable this when submitting or testing!
                ;; Also this debugging code IS HOW I FIGURED THIS STUFF OUT.
                ;;(printf "a is ~a | b is ~a\n" a b)
                
                ;; Using cond to figure out what we need to do.
                (cond 
                   ;; First round we must detect the 0 in b.
                   ;; That way we get a pair of (FIRST_NUMBER 0)
                   ((equal? 0 b) (list a 0))
                   
                   ;; Detect if b is a number.
                   ;; This happens when we've found a number we want to keep
                   ;; for the next round. So my solution was to "transform"
                   ;; the things into a list. Since a is the current item
                   ;; we want to save I keep it it in a list along with b
                   ;; which is the current sum.
                   ((number? b) (list a b))
                   
                   ;; Detect pairs, so we know when to multiply and add together.
                   ;; basically we'd have something like this:
                   ;; (4 30)
                   ;; now we want to do
                   ;; (3*4 + 30)
                   ;; and get something like
                   ;; 42
                   
                   ;; I also had issues originally returning this number
                   ;; as a list but I solved that issue by alternating between
                   ;; returning a list and a number.
                   ;; I return a list when we want to multiply products together
                   ;; and add them to the current sum.
                   ;; I return a number whenever we've just done this so that
                   ;; the answer ends up as a number since that's what the tests
                   ;; are expecting.
                   
                   ;; So I detect the pairs by getting the length of the list.
                   ;; I put this last because you aren't supposed to get the
                   ;; length of a number apparently hahahahahahaha and that
                   ;; caused errors before.
                   ((equal? (length b) 2) (+ (* a (car b)) (cadr b)))
                   
                   ;; Else isn't really needed but I kept it in here
                   ;; incase something failed or whatever.
                   (else b)
                )
              )
              
              0            ;; Base case of null.
              lst))        ;; Passing in the list.


;; SICP exercise 2.35 (pp. 120), redefining count-leaves as an
;; accumulation.  Fill in the below procedure. Replace '<??>.
;; note! you may recursively call this "count-leaves" fcn
;;  inside of it!
;; e.g.:
;;  (define tree (list 1 2 (list 3 4) (list 5 (list 6 7)))) 
;;  (count-leaves tree) => 7

#|
count-leaves looks like this:

(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else (+ (count-leaves (car x))
                 (count-leaves (cdr x))))))
|#

;; Attempting to mess around with this, basically the original
;; count-leaves inside some sort of accumulate function.
(define (count-leaves tree)
  (accumulate (lambda (x y)
                ;; DEBUG CODE
                ;;(printf "x is ~a\ny is ~a\n" x y)
                
                (cond ((null? x) 0)        ;; null gets nothing.
                      ((pair? x) (+ y 2))  ;; pairs get +2
                      (else (+ y 1)))      ;; everything else gets +1
              )
              0                            ;; base case of 0.
              ;; i don't really use the map for anything. this basically
              ;; returns all the elements without messing anything up.
              (map (lambda (x) x) tree)))  
             

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
  (accumulate 
      (lambda (x y)
          ;; DEBUG CODE
          ;; I WAS FAILING TESTS WITH THIS ON, SILLY ME.
          ;;(printf "x is ~a\ny is ~a\n" x y)
        
          ;; This was my original attempt as I thought it just needed to
          ;; generate a list or something.
          ;; Then I realized I needed to use the "p" procedure on the elements
          ;; of the list.
          ;;(cons x y)
          
          ;; Another attempt, which should call the procedure "p" on "x"
          ;; and cons it with y. X is any given element of the list, and
          ;; "y" is the final list at the end.
          (cons (p x) y)
        
      ) 
      nil 
      sequence))

(define (append-from-fold seq1 seq2)
  ;; This should just append the second list to the end of the first list.
  ;; e.g. '(1 2) '(3 4) should become (1 2 3 4)
  ;; I first tried just doing seq1 seq2 but noticed when I ran one
  ;; of the test cases it failed. Seems like this was the output:
  ;; '(3 4 1 2)
  ;; I tried swapping the order around of seq1 and seq2 and got the right output:
  ;; '(1 2 3 4)
  ;; I think the accumulate function is to blame, and swapping them around
  ;; fixed that bug.
  (accumulate cons seq2 seq1))

(define (length-from-fold sequence)
  (accumulate 
   #|
       I think this one is actually trivial if you bothered to do
       the other problems and use some debug code to figure out how the
       lambda x y / a b stuff works. Basically I use lambda (a b) in order to
       get each peace of the sequence. I then add 1 to b every time to
       do a quick count of the list. This passes the 3 tests and appears
       to work so I don't know what else I should have to explain for credit.
       
       TL&DR: this one is trivial.
   |#
   
   (lambda (a b)  ;; Using lambda fnc similar to original code.
      (+ b 1))    ;; This should just count the length of sequence haha.
   
   0 sequence))

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
  ;; From the Racket docs, found here:
  ;; https://docs.racket-lang.org/reference/pairs.html
  ;;(reverse items)
  
  ;; Detect the end of the recursion / empty lists.
  (if (null? items)
      nil        ;; BASE CASE OF NULL
      ;; Doing the recursive call first makes it reverse the
      ;; order of the items funny enough.
      ;; Also I found the "append" function on the docs where I also found
      ;; the "reverse" function which I initially tried and passed all 3 tests
      ;; for this function with.
      ;; Docs found here:
      ;; https://docs.racket-lang.org/reference/pairs.html
      ;; Specifically the "(append lst ...) part.
      (append (my-reverse (cdr items))    
              (list (car items)))          
  )
)

; deep reverse
; recursively reverse sublists
; e.g.
;  (deep-reverse '(1 2 3)) => '(3 2 1)
;  (deep-reverse '((1 2) (3 4))) => '((4 3) (2 1))
;  (deep-reverse '((1 2) (3 (4 5)))) => '(((5 4) 3) (2 1))

#|
This version prints out "'(((() 3) 2) 1)" which is almost right I think
for the first case.

(define (deep-reverse items) 
  ;; This one's a little tricker.
  ;; DEBUG CODE
  ;; must disable this when submitting or testing!
 #| (if (null? items)
      (printf "'()\n")
      (printf "Current item is ~a\n" (car items))
  ) |#
  
  ;; Need some conditions to solve this.
  (cond 
    ;; Base case / if the "items" list is null.
    ((null? items) nil)
    
    ;; See if we have a number.
    ;; If so, just do some more recursive calls first to make the list
    ;; reversed. Assuming there's only numbers anyway.
    ((number? (car items)) (list (deep-reverse (cdr items)) (car items)))
     
    ;; Otherwise recursive call.
    (else (deep-reverse (cdr items)))  ;; Recursive call.
  ))
|#

#|
This version almost reverses sub lists, it spits out something like this:
> (deep-reverse (list (list 1 2) (list 3 4)))
'((3 4) (1 2))

(define (deep-reverse items) 
  ;; This one's a little tricker.
  ;; DEBUG CODE
  ;; must disable this when submitting or testing!
 #| (if (null? items)
      (printf "'()\n")
      (printf "Current item is ~a\n" (car items))
  ) |#
  
  ;; Need some conditions to solve this.
  (cond 
    ;; Base case / if the "items" list is null.
    ((null? items) nil)
    
    ;; See if we have a number.
    ;; If so, just do some more recursive calls first to make the list
    ;; reversed. Assuming there's only numbers anyway.
    ;; This is basically like my-reverse if we find a number anyway.
    ((number? (car items)) (append (deep-reverse (cdr items)) (list (car items))))
    
    ;; If we find a pair then recursive call to deal with it.
    ;; We should be able to use the same code from my-reverse, just need
    ;; to account for the pair.
    ((pair? (car items)) (append (deep-reverse (cdr items)) (list (car items))))
    
    ;; Otherwise recursive call to find the base case.
    (else (deep-reverse (cdr items)))  ;; Recursive call.
  ))
|#

;; Hopefully this version works.
(define (deep-reverse items) 
  ;; This one's a little tricker.
  ;; DEBUG CODE
  ;; must disable this when submitting or testing!
 #| (if (null? items)
      (printf "'()\n")
      (printf "Current item is ~a\n" (car items))
  ) |#
  
  ;; Need some conditions to solve this.
  (cond 
    ;; Base case / if the "items" list is null.
    ((null? items) nil)
    
    ;; See if we have a number.
    ;; If so, just do some more recursive calls first to make the list
    ;; reversed. Assuming there's only numbers anyway.
    ;; This function is basically like my-reverse if we find a number anyway.
    ((number? (car items)) (append (deep-reverse (cdr items)) (list (car items))))
    
    ;; If we find a pair then do a recursive call to deal with it.
    ;; We should be able to use the same code from my-reverse, just need
    ;; to account for the pair needing to be reversed as well.
    ((pair? (car items)) 
            ;; Similar to my-reverse again.
            (append (deep-reverse (cdr items)) 
                    ;; But since this is a deep-reverse, this
                    ;; will need a recursive call in order to get sub lists 
                    ;; like "(3 4)" looking like "(4 3)" which is the point 
                    ;; of this function.
                    (list (deep-reverse (car items)))
            ))
    
    ;; Otherwise recursive call to find the base case.
    ;; Make sure to keep appending in reverse too.
    (else (append (deep-reverse (cdr items)) (list (car items))))
  ))
