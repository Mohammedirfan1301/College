#lang racket

;;; +++++++++ Required for auto grading ++++++++++++

;; Allow name nil to be used for the empty list.
(define nil '()) 			

;; Some other constants with non-traditional names:
(define true #t)
(define false #f)

;; For stream programming section 3.5
;; We use a force and delay which are slightly
;; different from the force and delay defined in the book:
;; delay (aka make-promise) handles recursive forcing.

(define the-empty-stream '())
(define stream-null? null?)
(define stream-car car)
(define (stream-cdr s)
  (force (cdr s)))

(define-syntax cons-stream
  (syntax-rules ()
    ((_ head tail)
     (cons head (delay tail)))))

(define (stream-ref a n)
  (if (= n 0)
      (stream-car a)
      (stream-ref (stream-cdr a) (- n 1))))

(define (stream-map proc s)
  (if (stream-null? s)
      the-empty-stream
      (cons-stream (proc (stream-car s))
                   (stream-map proc (stream-cdr s)))))

; Following is the general stream-map from Exercise 3.50
(define (stream-map-general proc . argstreams)
  (if (stream-null? (car argstreams))
      the-empty-stream
      (cons-stream 
       (apply proc (map stream-car argstreams))
       (apply stream-map-general (cons proc (map stream-cdr argstreams))))))

(define (stream-for-each proc s)
  (if (stream-null? s)
      the-empty-stream
      (begin (proc (stream-car s))
             (stream-for-each proc (stream-cdr s)))))

(define (stream-filter pred stream)
  (cond ((stream-null? stream) the-empty-stream)
        ((pred (stream-car stream))
         (cons-stream (stream-car stream)
                      (stream-filter pred
                                     (stream-cdr stream))))
        (else (stream-filter pred (stream-cdr stream)))))

(define (display-stream s)
  (stream-for-each display-line s))

(define (display-line x)
  (newline)
  (display x))

(define (stream-enumerate-interval low high)
  (if (> low high)
      the-empty-stream
      (cons-stream
       low
       (stream-enumerate-interval (+ low 1) high))))

(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))

(define integers (integers-starting-from 1))

(define (add-streams s1 s2)
  (stream-map-general + s1 s2))

(define (stream->list stream)
            (if (stream-null? stream)
                '()
                (cons (stream-car stream)
                      (stream->list (stream-cdr stream)))))

;;; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


;;; *******************************************************************
;;; Problem 1:
;;; 
;;; Use stream-map (pp. 320 of textbook) to define a procedure called
;;; convert-temps that takes a stream of temperatures in Fahrenheit
;;; and returns a stream of converted temperatures in Celsius. Recall
;;; that to convert Fahrenheit to Celsius, the equation is C = 5/9 *
;;; (F-32).

(define (convert-temps fahrenheit-stream)
  ;; Using stream-map to convert F to C using the provided formula:
  ;; C = 5/9 * F-32
  (stream-map (lambda (x) (* (/ 5 9) (- x 32))) fahrenheit-stream))


;;; ******************************************************************
;;; Problem 2:
;;; 
;;; Use stream-filter (pp. 322 of textbook) to define the stream of
;;; all integers that are evenly divisible by 2, 3, or 5.
;;;


(define (divisible? x y)
  (= (remainder x y) 0))

(define (divisible-by-2-3-5 int-stream)
  (stream-filter
       (lambda (x)
         (cond
           ((divisible? x 2) x)
           ((divisible? x 3) x)
           ((divisible? x 5) x)
           (else #f)))
   int-stream))



;;; ******************************************************************
;;; Problem 3:
;;; 
;;; Replace the lambda function to complete the following alternative
;;; definition of the integers stream:
;;;
;;; (define my-integers (cons-stream 1 (stream-map <??> my-integers)))
;;;

(define my-integers
  ;; This was in the book, it basically just does + 1 on all the integers.
  (cons-stream 1 (stream-map (lambda (x) (+ x 1)) my-integers)))

 
;;; ******************************************************************
;;; Problem 4:
;;; 
;;; Complete Exercise 3.51 on pp. 325 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.51
;;;
;;; In order to take a closer look at delayed evaluation, we will use
;;; the following procedure, which simply returns its argument after
;;; printing it:
;;;
#|
     (define (show x)
      (display-line x)
       x)
|#
;;;
;;; What does the interpreter print in response to evaluating each
;;; expression in the following sequence?
;;;
;;; Put your answer in comments and change the symbol #f to #t after
;;; answering.

(define p4_1 #t)
;;; (define x (stream-map show (stream-enumerate-interval 0 10)))
#|
All that is printed is a single "0".
This is because when stream-map gets called, it applies show to the
stream-enumerate-interval expression which gets delayed and only
the zero ends up showing up when show actually runs.
|#

(define p4_2 #t)
;;; (stream-ref x 5)
#|
What gets printed out is:
> (stream-ref x 5)

1
2
3
4
55

The 5 is printed twice because stream-ref must caculate out the first
5 elements until it hits the 6th element which is when it stops. It then
prints out what stream-ref wants, which is the "5". The first numbers, 1-5,
is basically from the calculations while the last 5 is from stream-ref.
|#

(define p4_3 #t)
;;; (stream-ref x 7)
#|
All that gets printed out is the following:
> (stream-ref x 7)

6
77

This is interesting because the first numbers, 1-5, do not need to be
recalculated since we already found them when we ran "(stream-ref x 5)".
As a result, the first five elements have already been found but the last
two need to be calculated, and that is why only 6 and 7 get printed out,
and then the result from stream-ref which is the second "7".

|#


;;; ******************************************************************
;;; There is no problem 5.


;;; ******************************************************************
;;; Problem 6:
;;; 
;;; Complete Exercise 3.53 on pp. 330 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.53
;;;
;;; Without running the program, describe the elements of the stream
;;; defined by
;;;
;;; (define s (cons-stream 1 (add-streams s s)))
;;;
;;; Put your answers in comments, and change the value of p6 from
;;; #f to #t after answering.
(define p6 #t)

#|
This stream will start at 1 and then apply (add-streams) to s and s when
the full list is needed. add-streams will double s since it is given s twice,
so the stream will be 1, and then powers of two.

|#


;;; ******************************************************************
;;; Problem 7:
;;; 
;;; Complete Exercise 3.54 on pp. 331 (see link below).
;;; http://mitpress.mit.edu/sicp/full-text/book/book-Z-H-24.html#%_thm_3.54
;;;
;;; Define a procedure mul-streams, analogous to add-streams, that
;;; produces the elementwise product of its two input streams. Use
;;; this together with the stream of integers to complete the
;;; following definition of the stream whose nth element (counting
;;; from 0) is n + 1 factorial:
;;;
;;; (define factorials (cons-stream 1 (mul-streams <??> <??>)))

(define (mul-streams s1 s2)
  (stream-map-general * s1 s2))

(define factorials 
  (cons-stream 1 (mul-streams factorials integers)))



;;; ************************ END OF FILE *****************************
