#lang racket

;; Exercise 3.1
;; https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-20.html#%_thm_3.1
;; 
;; After writing and testing the code, draw the environment diagram that would
;; result from evaluating the three statements in the exercise.
;; 
;; Include as ASCII drawing in this file, or upload image named
;; exercise3.1-env.png (or .jpg)

(define (make-accumulator sum)
  (lambda (x)
    (set! sum (+ sum x))
    sum
  )  
)

(define exercise-3.1-env #f)
;; change to #t after you include diagram

;; Exercise 3.2
;; https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-20.html#%_thm_3.2
;;
;; After writing and testing the code, draw the environment diagram that would
;; result from evaluating the three statements in the exercise.
;; 
;; Include as ASCII drawing in this file, or upload image named
;; exercise3.2-env.png (or .jpg)

(define (make-monitored f)
  (let ((number-of-calls 0))
    (define (mf sym)
      (cond 
            ;; Reset symbol is the input
            ((eq? sym 'reset)
                  (begin (set! number-of-calls 0) 0))
            
            ;; How many calls symbol is the input
            ((eq? sym 'how-many-calls) 
                  number-of-calls)
            
            ;; Otherwise increase number of calls.
            (else (begin 
                    (set! number-of-calls 
                          (+ number-of-calls 1))
                    (f sym)))
            )
      )
  mf)
)

(define exercise-3.2-env #f)
;; change to #t after you include diagram


;; Exercise 3.3
;; https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-20.html#%_thm_3.3
(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (display-error)
    "Error, incorrect password")
  (define (dispatch p m)
    (if (eq? p password)
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              (else (error "Unknown request -- MAKE-ACCOUNT"
                           m)))
        display-error))
  dispatch)
                                       
;; Exercise 3.4
;; https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-20.html#%_thm_3.4
;;
;; this procedure should be called "make-account-secure"
;;
;; important note:
;;   once an account is locked, you should not be able to withdraw funds
;;   from it, even if then using the correct password!
(define (make-account-secure balance password)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (display-error)
    "Error, incorrect password")
  (define (dispatch p m)
    (if (eq? p password)
        (cond ((eq? m 'withdraw) withdraw)
              ((eq? m 'deposit) deposit)
              (else (error "Unknown request -- MAKE-ACCOUNT"
                           m)))
        display-error))
  dispatch)
  
; don't modify this
(define (call-the-cops)
  "your account has been locked. please call customer service.")
  