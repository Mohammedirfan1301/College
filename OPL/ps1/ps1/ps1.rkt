#lang racket

;; in all definitions, use lambda to create a procedure

;; exercise 1: procedure to square its argument
(define square
  (lambda (n)
    (* n n)))

;; exercise 2: write absolute value using the if statement
(define abs-using-if 
  (lambda (n)
    (if (< n 0)
        (- n)
        n)))

;; exercise 3: write absolute value using the cond statement
(define abs-using-cond
  (lambda (n)
    (cond ((< n 0) (- n))
          (else n))))

;; exercise 4: implement factorial (just copy in the given code)
;; use define syntax
(define fact
  (lambda (n)
    (if (= n 0)
        1
        (* n (fact (- n 1))))))

;; exercise 5: implement num of combinations of n things taken k at a time,
;; which is n! / k!(n - k)!
;; First do the division, then we can do the multiplication of k! * (n - k)!
;; Also need to separate out k! and (n - k)!
(define comb
  (lambda (n k)
    (/ (fact n)
       (* (fact k) 
          (fact (- n k))))))

;; exercise 6: triple its argument
(define triple
  (lambda (n)
    (* n 3)))

;; exercise 7: diff-of-triples
;; should return the first arg tripled minus the second arg tripled
(define diff-of-triples
  (lambda (n m)
    (- (triple n)
       (triple m))))

;; exercise 8: smallest-of-three
;; returns smallest of three args
;; you may not use the "min" function
;; you may use the boolean "and" function
;; I did this using three ifs, although you could use "and" as well.
(define smallest-of-three
  (lambda (a b c)
    (if (< a b) a
        (if (< b c) b              ;; this is the "else" to the above if (< a b)
            (if (<= c a) c a)))))   ;; this is the final "else"
                                    ;; the final "a" is a catch-all for all equal to

;; exercise 9: smallest-tripled
;; returns tripled value of smallest arg
;; This is basically "smallest-of-three" and then tripled!
;; AND we wrote both functions already, so just use them!
(define smallest-tripled
  (lambda (a b c)
    (triple (smallest-of-three a b c))))
