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
  ; Simple accumulator.
  (lambda (x)
    (set! sum (+ sum x))
    sum
  )  
)

(define exercise-3.1-env #t)
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
  (define calls 0)        ; Number of times the monitor has been called.
  (define (reset_calls)   ; Resets the number of calls variable.
    (set! calls 0))
  (define (mf sym)
    (cond   
      ;; Reset symbol is the input
      ((eq? sym 'reset) reset_calls)
      
      ;; How many calls symbol is the input
      ((eq? sym 'how-many-calls?) calls)
      
      ;; Otherwise increase number of calls.
      (else (set! calls (+ calls 1))
            (f sym))))
  mf)

(define exercise-3.2-env #t)
;; change to #t after you include diagram


;; Exercise 3.3
;; https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-20.html#%_thm_3.3
(define (make-account balance password)
  ; From the SICP book
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  
  ; Displays an incorrect password error, like the test file wants.
  (define (display-incorrect useless)  ; the useless parameter is to stop errors.
    "Incorrect password")
  
   ; Modified this function from the SICP book.
  (define (dispatch pass sym)
    (if (eq? pass password)
        (cond ((eq? sym 'withdraw) withdraw)
              ((eq? sym 'deposit) deposit)
              (else (error "Unknown request -- MAKE-ACCOUNT" sym)))
        display-incorrect))
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
  ; From the SICP book
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  
  ; Displays an incorrect password error, like the test file wants.
  (define (display-incorrect useless)   ; the useless parameter is to stop errors.
    "Incorrect password")
  
  ; Modified this function from the SICP book.
  (define password-attempts 0)
  (define (dispatch pass sym)
    (if (eq? pass password)
        ; If the password is correct, see if the account is locked or not.
        (if (> password-attempts 7)
            ; Call the cops, the account is locked.
            call-the-cops    
            
            ; Account isn't locked, so continue.
            (begin (set! password-attempts 0)
                   (cond ((eq? sym 'withdraw) withdraw)
                         ((eq? sym 'deposit) deposit)
                         (else (error "Unknown request -- MAKE-ACCOUNT" sym)))))
        
        ; Increase password attempts and see if we should 
        ; call the cops or display an error.
        (begin (set! password-attempts         ; Increase by one each time
                     (+ password-attempts 1))  
               (if (> password-attempts 7)     ; Check to see if we should call the cops.
                   call-the-cops
                   display-incorrect))))
  dispatch)
  
; don't modify this
; Not sure why but I had to add the useless parameter to get tests 19 & 20 to pass.
; Since it kept complaining about the number of parameters.
(define (call-the-cops useless)
  "your account has been locked. please call customer service.")
  