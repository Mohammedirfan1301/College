#lang racket

;; recursive procedure for adding the first n natural numbers
;; e.g. (sum-recursive 0) is 0
;;      (sum-recursive 1) is 1
;;	(sum-recursive 2) is 3 [it's 2 + 1]
;;      (sum-recursive 3) is 6 [it's 3 + 2 + 1]
(define (sum-recursive n)
  (if (= n 0)  ;; Base case of 0.
      0
      ;; recursively add numbers together.
      (+ n (sum-recursive (- n 1) ))))

;; iterative procedure for the same
;; Based off the code given on Friday 1/29
;; URL: http://www.cs.uml.edu/ecg/pub/uploads/OPLspr16/jan29.rkt
(define (sum-iterative n)
  (define (count-helper count total)
  (if (= count 0)  ;; when we hit zero,
      total        ;; return the total
      (count-helper (- count 1)         ;; subtract 1 from count
                    (+ total count))))  ;; add count to total
  (count-helper n 0)) ;; count = n, total = 0

;; recursive procedure for sum of squares of first n natural numbers
;; e.g., (sum-squares-recursive 0) is 0
;; 	 (sum-squares-recursive 1) is 1
;; 	     (sum-squares-recursive 2) is 5 (2^2 + 1^2)

;; Simple square function for sum-squares-recursive
(define (square x)
  (* x x))

;; Recursive function.
(define (sum-squares-recursive n)
  ;; Base case of 0.
  (if (= n 0)
      0  ;; Same as sum-recursive but using the square function above.
      (+ (square n) (sum-squares-recursive (- n 1) ))))

;; iterative procedure for the same
(define (sum-squares-iterative n)
  (define (count-helper count total)
  (if (= count 0)  ;; when we hit zero,
      total        ;; return the total
      (count-helper (- count 1)                  ;; subtract 1 from count
                    (+ total (square count)))))  ;; add (count^2) to total
  (count-helper n 0))  ;; count = n, total = 0

;; recursive procedure for sum of squares of first n odd numbers
;; (starting with 1)
;; e.g., (sum-alt-squares-recursive 0) is 0
;; 	 (sum-alt-squares-recursive 1) is 1 (1^2)
;; 	 (sum-alt-squares-recursive 2) is 10 (3^2 + 1^2)
;;       (sum-alt-squares-recursive 3) is 35 (5^2 + 3^2 + 1^2)
(define (sum-alt-squares-recursive n)
  (if ( = n 0)
      0
      (if ( = n 1)
          1
          ;; this part translates into "(1 + 2(n-1))^2",
          ;; it's done recursively as required.
          (+ (square (+ 1 (* 2 (- n 1)))) (sum-alt-squares-recursive (- n 1))))))

;; iterative procedure for the same
(define (sum-alt-squares-iterative n)
  (define (count-helper count total)
  (if (= count 0)  ;; when count == 0,
      total        ;; return total sum of what we're doing.
      (count-helper (- count 1)  ;; decrement count each time.
                    ;; this is basically (1 + (2*(n-1)))^2,
                    ;; and we keep doing this until count becomes 0.
                    (+ total (square (+ 1 (* 2 (- count 1))))))))
  (count-helper n 0))   ;; count = n, total = 0

;; following series converges to 2/3
;; (notice alternating addition and subtraction of the terms):
;;
;;  1     1     1     1     1
;; --- - --- + --- - --- + ---  etc.
;;  1     2     4     8     16
;;
;; implement as a recursive process, where the argument is the number of terms
;; e.g.
;; (two-thirds-series 0) is 1
;; (two-thirds-series 1) is 1/2
;; (two-thirds-series 2) is 3/4
;; HINTS: even? and odd? are predicates; (expt 2 3) is 2^3.
(define (two-thirds-series-r n)
  (if (= n 0)
      1
      ;; Add positive and negative fractions recursively
      ( + (if (even? n) ;; detect if the number is even or odd.
             ;; this confusing thing either adds or subtracts,
             ;; by making numbers either negative or positive.
             ;; the inner () basically do:
             ;; "1 / (2^n)", alternate between pos / neg.
             ( + (/ 1 (expt 2 n) ))  ;; even case
             ( - (/ 1 (expt 2 n) ))  ;; odd case
         )
         ( two-thirds-series-r(- n 1) )    ;; recursive call
      )
  )
)

;; iterative procedure for the same
(define (two-thirds-series-i n)
  (define (count-helper count total)
  (if (= count 0)  ;; when count == 0,
      total        ;; return total sum of what we're doing.
      (count-helper (- count 1)  ;; decrement count each time.

         ;; this is similar to the recursive formula
         ;; I just copy / pasted the main logic into the iterative version,
         ;; and changed the "n" variable to count.
         (if (even? count) ;; detect if the number is even or odd.

             ;; this confusing thing either adds or subtracts,
             ;; by making numbers either negative or positive.
             ;; the inner () basically do:
             ;; "1 / (2^count)", alternate between pos / neg.
             ;; count in this case is basically "n" in the recursive case.
             ( + total (/ 1 (expt 2 count) ))  ;; even case
             ( - total (/ 1 (expt 2 count) ))  ;; odd case
         )
       )
  ))
  (count-helper n 1)  ;; count = n, total = 1 (for the base case of 1)
)

;; SICP exercise 1.11 (pp. 42). In this problem, you implement a
;; recursive mathematical function. Only do the recursive implementation.
(define (f-recursive n)
  (if (< n 3)
      ;; n < 3 case
      n

      ;; n >= 3 case
      ;; straight from exercise 1.11, which defines this as:
      ;; f(n) = f(n - 1) + (2 * f(n - 2)) + (3 * f(n - 3))
      (+ (f-recursive(- n 1))           ;; f(n - 1)
         (* 2 (f-recursive(- n 2)))  ;; (2 * f(n - 2))
         (* 3 (f-recursive(- n 3)))  ;; (3 * f(n - 3))
      )
  )
)

;; SICP exercise 1.16 (pp. 46).
;; complete the fast-expt implementation using an iterative process
(define (fast-expt b n)
  (define (iter-expt b n a)
      (if (= n 0)
          a               ;; base case, when n == 0, return a.
          (if (even? n)   ;; detect if the number is even or odd.

             (iter-expt (square b) (/ n 2) a)  ;; even case
             (iter-expt b (- n 1) (* a b))     ;; odd case
          )
       )
  )
  (iter-expt b n 1)    ;; seed a with a value of 1, as the prompt says to do so.
)

;; When implementing an iterative process in Scheme, the Scheme
;; interpreter uses tail-recursion.  Explain what this means.  Answer
;; this question in a comment block, and change #f to #t.
#|
   Tail recursion is where recursive procedures call themselves
   in order to solve a problem. This creates a nest of calls, which
   looks something like this:

   Assume we have a call like "recursive_function(+ n 1)", where N starts at 1,
   and a base case breaks at n == 4.

   First the interpreter does "(+ 1", and it then calls itself, leading to
   "(+ 1(+ 2". It would continue to call itself until the base case of "n == 4".
   The entire chain of calls would lead to the following:

   (+ 1 (+ 2 (+ 3 4))))  ;; assume this is a recursive addition, similar to sum-recursive
   (+ 1 (+ 2 7)))        ;; 3 + 4 = 7
   (+ 1 9)               ;; 2 + 7 = 9
   10                    ;; 1 + 9 = 10
   This would then return "10" as the final answer.

   This works pretty efficiently compared to other styles of recursion, as it allows
   you to perform recursion with a decent amount of efficiently (depending on the
   interpreter / compiler and whatever language you use).
|#
(define tail-recursion #t)
