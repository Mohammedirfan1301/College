#lang racket

;; last modified Sat Feb 20 15:45:14 2016 fredm@cs.uml.edu

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define nil '())
;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



;; **********************************************************************
;;
;; 2. Consider the following procedure for operating on trees:
(define (tree-manip tree init leaf accum) 
  (cond ((null? tree) init) 
        ((not (pair? tree)) (leaf tree)) 
        (else (accum  
               (tree-manip (car tree) init leaf accum) 
               (tree-manip (cdr tree) init leaf accum)))))

;; Suppose that we provide a test tree, 
(define test-tree '(1 (2 (3 (4) 5) 6) 7))
;;
;; 2a. Write the parameters to tree-manip that will count the number
;;     of leaves in the tree, evaluating to 7 for test-tree; e.g.:
;;     (tree-manip test-tree <param1> <param2> <param3>). (Figure out
;;     the three parameters.)
;;
;; 2b. Write the parameters to tree-manip that will add the values of
;;     the leaves in the tree, evaluating to 28 for test-tree.
;;
;; 2c. Write the parameters to tree-manip that will triple each of the
;;     values in test-tree, evaluating to (3 (6 (9 (12) 15) 18) 21).

;; Answer:
;2a.
(define (count-leaves tree) 
  ;; give it the tree, starting value of 0,
  ;; (lambda (x) 1) will return 1 for each leaf,
  ;; and + to add all the leaves together.
  ;; Example output: (count-leaves test-tree) => 7
  (tree-manip tree 0 (lambda (x) 1) +)
)

;2b.
(define (sum-leaves tree) 
  ;; give it the tree, starting value of 0,
  ;; (lambda (x) x) will return the value of each leaf,
  ;; and + to add all the values together (sum it up).
  ;; Example output: (sum-leaves test-tree) => 28
  (tree-manip tree 0 (lambda (x) x) +)
)

;2c.
(define (triple-leaves tree) 
  ;; give it the tree, starting value of nil ('()),
  ;; (lambda (x) (* x 3)) will return (x*3) for each leaf,
  ;; and cons will add them all together in a list.
  ;; Example output: (sum-leaves test-tree) => '(3 (6 (9 (12) 15) 18) 21)
  (tree-manip tree nil (lambda (x) (* x 3)) cons)
)

;; **********************************************************************
;;
;; 3. SICP exercise 2.35 (pp. 120), another way of implementing
;; count-leaves as an accumulation.  Fill in the below procedure.
;;
;; uncomment line starting with "foldl" and replace with answer

(define (count-leaves-with-map t)
  ;; Need to sum up using + and 0 as the initial value.
  (foldl + 0 (map (lambda (leaf) 
                 ;; Need to determine if each leaf is a pair or not.
                 (if (pair? leaf)
                    2 ;; Yes, so add 2.
                    1 ;; Nope, so add 1.
                 )) 
              t)
  )
)  


;; **********************************************************************
;;
;; 4. Using flip, negate, and compose.
;;
;;     4a. Define and play with the functions flip, negate, and
;;     compose, as they are defined below.
;;
;;     4b. Define, for instance, a flipped cons function and a flipped
;;     minus function.
;;
;;     4c. Define the function odd? in terms of even? and negate.

(define (flip f)
  (lambda (x y)
    (f y x)))

(define (negate p)
  (lambda (x) 
    (if (p x) #f #t)))

(define (compose f g)
  (lambda (x)
    (f (g x))))

;;Answer:
;3.b 
(define (flip-cons lst1 lst2)
  ;; flip cons
  ((flip cons) lst1 lst2)
)

(define (flip-minus x y)  
  ;; flip minus
  ((flip -) x y)
)

;3.c
(define (flip-odd x)
  ;; negate in terms of even?
  ((negate even?) x)
)

;; **********************************************************************
;;
;; 5. SICP exercise 2.38 (pp. 121), introducing fold-right and fold-left.
;;
;; Write the defintion for fold-right (hint: Answer to fold-right is
;; in the question. Read the question carefully)
;;
;; Write down each step of substitution in comment line for each of
;; the following.
;;
;; What are the values of
;(fold-right / 1 (list 1 2 3))
;(fold-left / 1 (list 1 2 3))
;(fold-right list nil (list 1 2 3))
;(fold-left list nil (list 1 2 3))

;;Answer:
;; Given in the question that accumulate is also known as fold-right. So,
(define (fold-right op initial sequence) 
  (if (null? sequence)
      initial
      (op (car sequence)
          (fold-right op initial (cdr sequence))
      )
  )
)


;(fold-right / 1 (list 1 2 3))
;write substitution steps

;(fold-left / 1 (list 1 2 3))
;write substitution steps

;(fold-right list nil (list 1 2 3))
;write substitution steps

;(fold-left list nil (list 1 2 3))
;write substitution steps

;op property:
;--------------
;write the property (with example if possible)

;After answering the above replace #f to #t
(define p4 #f)


;; **********************************************************************
;;
;; 6. Use fold-right to define the function bucket. 
;;
;; It consumes a list of numbers, and returns a list of sublists of
;; adjacent equal numbers.
;;
;; For example:
;; (bucket '(1 1 2 2 2 3 1 1 1 2 3 3)) –> 
;;  '((1 1) (2 2 2) (3) (1 1 1) (2) (3 3))
;;
;; PLEASE NOTE
;; it's trivial to find the answer for this on the internet
;; please do not succumb
;; you won't learn very much unless you struggle with it
;;
;; think about each of the two objects that are consumed by the 
;; folding function as the fold proceeds
;;
;; and think about what sort of object should be produced by that
;; function 
;; 
;; for full credit on this, show your work,
;; including partial / broken solutions and explanations
;;
;; Fill in the below procedure
;; 
(define (bucket lst)
  ;; testing 1 2 3
  (fold-right 
    (lambda (x y)
      ;; DEBUG OUTPUT (COMMENT OUT FOR TESTING)
      ;;(printf "x = ~a\ty = ~a\n" x y)
      (if (null? x)
          nil           ;; Return nil for nil X's.
         (if (null? y)  ;; Otherwise check Y.
           (list (list x))  ;; True case, return number in list form.
           (if (equal? x (car y))  ;; Otherwise check if X is same as old X.
               (list (append x))     ;; True
               (list (append x))     ;; False
           )
         )
      )
    )
  nil lst)  ;; give it nil for initial and the lst for the sequence.
)

;; ************************ END OF FILE *********************************