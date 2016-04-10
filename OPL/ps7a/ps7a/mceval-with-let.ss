;;; mc-eval-with-let.ss
;;; Metacircular evaluator from section 4.1 of SICP

;;; MUST SET LANGUAGE TO R5RS
;;;
;;; this is necessary because environments implementation
;;; uses mutable cons cells

;;; enter the interpreter by evaluating in the REPL:
;;;   (mc-eval-loop)
;;;
;;; also, if you exit the interpreter, you can restart it without
;;; reinitializing the global environment with:
;;;   (driver-loop)

;;; mc-eval and mc-apply are the heart of the evaluator

(define (mc-eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        
        ((and? exp) (eval-and exp env))       ;; uml:and
        ((or? exp) (eval-or exp env))         ;; Added in for uml:or
        
        ((lambda? exp)
        (make-procedure (lambda-parameters exp) (lambda-body exp) env))
        ((begin? exp) (eval-sequence (begin-actions exp) env))
        ((cond? exp) (mc-eval (cond->if exp) env))
   
        ;; uml:not
        ((let? exp) (mc-eval (let->combination exp) env))
        ((application? exp)
        (mc-apply (mc-eval (operator exp) env)
		(list-of-values (operands exp) env)))
        (else (error "Unknown expression type -- MC-EVAL"))))


(define (mc-apply procedure arguments)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure procedure arguments))
        ((compound-procedure? procedure)
         (eval-sequence
          (procedure-body procedure)
	  (extend-environment (procedure-parameters procedure)
			      arguments
			      (procedure-environment procedure))))
        (else (error "Unknown procedure type -- MC-APPLY" procedure))))

;;; list-of-values is used to produce the list of arguments to which
;;; a procedure is to be applied

(define (list-of-values exps env)
  (if (no-operands? exps)
      '()
      (cons (mc-eval (first-operand exps) env)
	    (list-of-values (rest-operands exps) env))))


;;; eval-if evaluates the predicate part of an if expression in the
;;; given environment

(define (eval-if exp env)
  (if (true? (mc-eval (if-predicate exp) env))
      (mc-eval (if-consequent exp) env)
      (mc-eval (if-alternative exp) env)))


;;; eval-sequence is used by mc-apply to evaluate the sequence of 
;;; expressions in a procedure body and by eval to evaluate the
;;; sequence of expressions in a begin expression

(define (eval-sequence exps env)
  (cond ((last-exp? exps) (mc-eval (first-exp exps) env))
        (else (mc-eval (first-exp exps) env)
              (eval-sequence (rest-exps exps) env))))


;;; eval-assignment handles assignment to variables

(define (eval-assignment exp env)
  (set-variable-value! (assignment-variable exp)
                       (mc-eval (assignment-value exp) env)
                       env)
  'ok)


;;; eval-definition handles definition of variables

(define (eval-definition exp env)
  (define-variable! (definition-variable exp)
                    (mc-eval (definition-value exp) env)
                    env)
  'ok)


;;; Following are the procedures that define the syntax of our language
;;; We preface the usual scheme commands with "uml:" to allow us to 
;;; differentiate when we are using the metacircular evaluator to 
;;; evaluate expressions (it will only be used for "uml:" expressions)
;;; and when scheme code is being evaluated by the usual scheme 
;;; interpreter

;;; Self-evaluating entities: numbers and strings

(define (self-evaluating? exp)
  (cond ((number? exp) #t)
	((string? exp) #t)
	(else #f)))

;;; Variables

(define (variable? exp) (symbol? exp))

;;; Quotations

(define (quoted? exp) 
  (tagged-list? exp 'uml:quote))

(define (text-of-quotation exp) (cadr exp))

;;; Special forms (in general)

(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))

;;; Assignment--- set!

(define (assignment? exp) 
  (tagged-list? exp 'uml:set!))

(define (assignment-variable exp) (cadr exp))

(define (assignment-value exp) (caddr exp))

;;; Definitions

(define (definition? exp)
  (tagged-list? exp 'uml:define))

(define (definition-variable exp)
  (if (symbol? (cadr exp))
      (cadr exp)
      (caadr exp)))

(define (definition-value exp)
  (if (symbol? (cadr exp))
      (caddr exp)
      (make-lambda (cdadr exp)		;formal parameters
		   (cddr exp))))        ;body

;;; lambda expressions

(define (lambda? exp) (tagged-list? exp 'uml:lambda))

(define (lambda-parameters exp) (cadr exp))

(define (lambda-body exp) (cddr exp))

;;; constructor for lambda expressions, used by definition-value above

(define (make-lambda parameters body)
  (cons 'uml:lambda (cons parameters body)))

;;; if conditionals

(define (if? exp) (tagged-list? exp 'uml:if))

(define (if-predicate exp) (cadr exp))

(define (if-consequent exp) (caddr exp))

(define (if-alternative exp)
  (if (not (null? (cdddr exp)))
      (cadddr exp)
      'false))

;;; constructor for if expressions, to be used for cond->if to 
;;; transform cond expressions into if expressions

(define (make-if predicate consequent alternative)
  (list 'uml:if predicate consequent alternative))

;;; Procedures to implement uml:and as a special form in our new language
(define (eval-and exp env)
  (define (iter clauses)
    (if (null? clauses)
	#t
	(if (false? (mc-eval (car clauses) env))
	    #f
	    (iter (cdr clauses)))))
  (iter (and-clauses exp)))

(define (and? exp) (tagged-list? exp 'uml:and))

(define (and-clauses exp) (cdr exp))

;;;************************************************************************
;;; Procedures to implement uml:or as a special form in our new language
;;;************************************************************************
(define (eval-or exp env)
  (define (iter clauses)
    (if (null? clauses)
        #f                                        ;; if null, then false, or if all are false.
        (if (true? (mc-eval (car clauses) env))   ;; Short circuit if it finds a true.
            #t
            (iter (cdr clauses)))))
  (iter (or-clauses exp)))

(define (or? exp) (tagged-list? exp 'uml:or))

(define (or-clauses exp) (cdr exp))

#|

This code is very similar to uml:and, as uml:and implements most of the required
functionality. It works similar to uml:and by going through the list of the clauses
which are provided to the OR expression. Uml:or recursively calls mc-eval, which evaluates
each cause in the order that it is provided in the list. Whenever a clause evaluates to true,
the expression short-circuits just like in uml:and, except it short circuits on true vs false.

uml:or will return true if any clause provided is true, and it will return false if all clauses are
false, or if no clauses are provided to uml:or.

Tests / evidence that uml:or works:

(uml:or) -> false
(uml:or false) -> false
(uml:or true) -> true
(uml:or true true) -> true
(uml:or true false) -> true
(uml:or false false) -> false
(uml:or false true false) -> true
(uml:or false false false) -> false
       
;;; MC-Eval input: (uml:or)
;;; MC-Eval value: #f
;;; OR of nothing is false.

;;; MC-Eval input: (uml:or false)
;;; MC-Eval value: #f
;;; OR of only false expressions is false.

;;; MC-Eval input: (uml:or true)
;;; MC-Eval value: #t
;;; OR containing any true expression is true.

;;; MC-Eval input: (uml:or true true)
;;; MC-Eval value: #t
;;; OR containing any true expression is true.

;;; MC-Eval input: (uml:or true false)
;;; MC-Eval value: #t
;;; OR containing any true expression is true.

;;; MC-Eval input: (uml:or false false)
;;; MC-Eval value: #f
;;; OR of only false expressions is false.

;;; MC-Eval input: (uml:or false true false)
;;; MC-Eval value: #t
;;; OR containing any true expression is true.

;;; MC-Eval input: (uml:or false false false)
;;; MC-Eval value: #f
;;; OR of only false expressions is false.

|#


;;; begin expressions (a.k.a. sequences)

(define (begin? exp) (tagged-list? exp 'uml:begin))

(define (begin-actions exp) (cdr exp))

(define (last-exp? seq) (null? (cdr seq)))

(define (first-exp seq) (car seq))

(define (rest-exps seq) (cdr seq))

;;; constructor sequence->exp for use by cond->if that transforms
;;; a sequence into a single expression, using begin if necessary

(define (sequence->exp seq)
  (cond ((null? seq) seq)
	((last-exp? seq) (first-exp seq))
	(else (make-begin seq))))

(define (make-begin seq) (cons 'uml:begin seq))

;;; procedure applications

(define (application? exp) (pair? exp))

(define (operator exp) (car exp))

(define (operands exp) (cdr exp))

(define (no-operands? args) (null? args))

(define (first-operand args) (car args))

(define (rest-operands args) (cdr args))

;;; cond conditionals: a derived expression

(define (cond? exp) (tagged-list? exp 'uml:cond))

(define (cond-clauses exp) (cdr exp))

(define (cond-else-clause? clause)
  (eq? (cond-predicate clause) 'uml:else))

(define (cond-predicate clause) (car clause))

(define (cond-actions clause) (cdr clause))

(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))

(define (expand-clauses clauses)
  (if (null? clauses)
      'false
      (let ((first (car clauses))
	    (rest (cdr clauses)))
	(if (cond-else-clause? first)
	    (if (null? rest)
		(sequence->exp (cond-actions first))
		(error "ELSE clause isn't last -- COND->IF"
		       clauses))
	    (make-if (cond-predicate first)
		     (sequence->exp (cond-actions first))
		     (expand-clauses rest))))))

;;; Adding uml:let to the evaluator

(define (let? exp) (tagged-list? exp 'uml:let))

(define (let-variables exp)
    (map car (cadr exp)))

(define (let-values exp)
    (map cadr (cadr exp)))

(define (let-body exp)
    (cddr exp))

(define (let->combination exp)
    (let ((variables (let-variables exp))
          (values (let-values exp))
          (body (let-body exp)))
       (cons (cons 'uml:lambda (cons variables body))
             values)))

;;; Data structures for our evaluator

;;; for conditionals, we accept anything that isn't the explicit false
;;; object to be true

(define (true? x)
  (not (eq? x #f)))

(define (false? x)
  (eq? x #f))

;;; representing procedures

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))

(define (compound-procedure? p)
  (tagged-list? p 'procedure))

(define (procedure-parameters p) (cadr p))

(define (procedure-body p) (caddr p))

(define (procedure-environment p) (cadddr p))

;;; operations on environments

;;; an environment is represented as a list of frames

(define (enclosing-environment env) (cdr env))

(define (first-frame env) (car env))

(define the-empty-environment '())

;;; each frame of an environment is represented as a pair of lists:
;;; a list of the variables bound in that frame and a list of the 
;;; associated values

(define (make-frame variables values)
  (cons variables values))

(define (frame-variables frame) (car frame))

(define (frame-values frame) (cdr frame))

(define (add-binding-to-frame! var val frame)
  (set-car! frame (cons var (car frame)))
  (set-cdr! frame (cons val (cdr frame))))

;;; to extend an environment by a new frame that associates variables
;;; with values, we make a frame consisting of the list of variables
;;; and the list of values, and we adjoin this to the environment -- 
;;; signal an error if the number of variables does not match the 
;;; number of values

(define (extend-environment vars vals base-env)
  (if (= (length vars) (length vals))
      (cons (make-frame vars vals) base-env)
      (if (< (length vars) (length vals))
	  (error "Too many arguments supplied" vars vals)
	  (error "Too few arguments supplied" vars vals))))

;;; to look up a variable in an environment, we scan the list of 
;;; variables in the first frame.  If we find the desired variable,
;;; we return the corresponding element in the list of values.  If 
;;; we do not find the variable in the current environment, we search
;;; the enclosing environment, and so on.  If we reach the empty 
;;; environment, signal an "unbound variable" error.

(define (lookup-variable-value var env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
	     (env-loop (enclosing-environment env)))
	    ((eq? var (car vars))
	     (car vals))
	    (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
	(error "Unbound variable" var)
	(let ((frame (first-frame env)))
	  (scan (frame-variables frame)
		(frame-values frame)))))
  (env-loop env))

;;; to set a variable to a new value in a specified environment,
;;; we scan for the variable, just as in lookup-variable value,
;;; and change the corresponding value when we find it

(define (set-variable-value! var val env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
	     (env-loop (enclosing-environment env)))
	    ((eq? var (car vars))
	     (set-car! vals val))
	    (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
	(error "Unbound variable -- SET!" var)
	(let ((frame (first-frame env)))
	  (scan (frame-variables frame)
		(frame-values frame)))))
  (env-loop env))


;;; to define a variable, we search the first frame for a binding
;;; for the variable, and change the binding if it exists (just as
;;; in set-variable-value!).  If no such binding exists, we adjoin
;;; one to the first frame.

(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (define (scan vars vals)
      (cond ((null? vars)
	     (add-binding-to-frame! var val frame))
	    ((eq? var (car vars))
	     (set-car! vals val))
	    (else (scan (cdr vars) (cdr vals)))))
    (scan (frame-variables frame)
	  (frame-values frame))))


;;; The following functions are used to allow the metacircular
;;; evaluator to be run

(define (setup-environment)
  (let ((initial-env
	 (extend-environment (primitive-procedure-names)
			     (primitive-procedure-objects)
			     the-empty-environment)))
    (define-variable! 'true #t initial-env)
    (define-variable! 'false #f initial-env)
    (define-variable! 'nil '() initial-env)
    initial-env))

(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))

(define (primitive-implementation proc) (cadr proc))

(define primitive-procedures
  (list (list 'uml:car car)
	(list 'uml:cdr cdr)
	(list 'uml:cons cons)
	(list 'uml:null? null?)
	(list 'uml:+ +)
	(list 'uml:- -)
	(list 'uml:* *)
	(list 'uml:/ /)
	(list 'uml:= =)
	(list 'uml:> >)
	(list 'uml:< <)))


(define (primitive-procedure-names)
  (map car
       primitive-procedures))

(define (primitive-procedure-objects)
  (map (lambda (proc) (list 'primitive (cadr proc)))
       primitive-procedures))

(define (apply-primitive-procedure proc args)
  (apply-in-underlying-scheme
   (primitive-implementation proc) args))

(define apply-in-underlying-scheme apply)


(define input-prompt ";;; MC-Eval input: ")

(define output-prompt ";;; MC-Eval value: ")

(define (driver-loop)
  (prompt-for-input input-prompt)
  (let ((input (read)))
    (let ((output (mc-eval input the-global-environment)))
      (announce-output output-prompt)
      (user-print output)))
  (driver-loop))

(define (prompt-for-input string)
  (newline) (newline) (display string))

(define (announce-output string)
  (display string))

(define (user-print object)
  (if (compound-procedure? object)
      (display (list 'compound-procedure 
		     (procedure-parameters object)
		     (procedure-body object)
		     '<procedure-env>))
      (display object)))

(define the-global-environment (setup-environment))

(define *unparser-list-depth-limit* 7)
(define *unparser-list-breadth-limit* 10)

(define (error . args)
  (display (cons 'error: args)))

(define (mc-eval-loop)
  (set! the-global-environment (setup-environment))
  (driver-loop))

; Problem 2.
;
; definition of uml:not
; invoke mc-eval to add a procedure definition to implement
; uml:not in the-global-environment.

; how uml:not displays in the-global-environment
; after uml:not is working, display contents of
; the-global-environment in the REPL.
; then, copy-paste into a comment here how the procedure is
; represented internally.
; change this flag to true.
(define printed-uml:not? #f)







