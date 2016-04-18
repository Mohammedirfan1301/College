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
	     ((and? exp) (eval-and exp env))
        ((for? exp) (eval-for exp env))
        ((lambda? exp)
        (make-procedure (lambda-parameters exp) (lambda-body exp) env))
        ((begin? exp) (eval-sequence (begin-actions exp) env))
        ((cond? exp) (mc-eval (cond->if exp) env))
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

;;; Adding uml:for
;;;
;;; Structure:
;;;   (uml:for (<var> <exp1> <exp2>) <body>)
;;;
;;; This should create an environment in which <var> is initially bound
;;; to the value of <exp1> and body is evaluated.
;;; then <var> is incremented. If it's less than <exp2>,
;;; then <body> is evaluated again, etc.
;;;
;;; for example, you should be able to write
;;;   (uml:for (i 1 3) (uml:set! n (uml:+ i n)))
;;; (assuming n was defined previously)
;;;
;;; e.g., the following should run as indicated
;;; > (mc-eval '(uml:define n 0) the-global-environment)
;;; ok
;;; > (mc-eval '(uml:for (i 1 3) (uml:set! n (uml:+ n i))) the-global-environment)
;;; ok
;;; > (mc-eval 'n the-global-environment)
;;; 6
;;;
;;; Do this by adding a procedure "for->combination"
;;; that rewrites the uml:for expression as a procedure that implements
;;; a recursive loop to carry out the iteration
;;; followed by an application of this procedure
;;; 
;;; you need to use uml:begin in your transformed expression to do these
;;; two things
;;; 
;;; follow the examples of cond->if and let->combination

;;; add your work here, and also add a line to mc-eval.

#|
    I was unable to figure out this assignment. I took a look at  the cond and let examples,
    and it seems like I need to define variables like the ones below. However, I'm not really
    sure how to use uml:begin to create the for expression. I was able to easily add for to the
    mc-eval.
|#
(define (for->combination exp)
  ; I have no idea what to do.
  (begin

    )
)

(define (for? exp) (tagged-list? exp 'uml:for))
(define (for-initial exp) (cadr exp))
(define (for-condition exp) (caddr exp))
(define (for-body exp) (cdddr exp))

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
	(list 'uml:< <)
   (list 'uml:not not)))   ;; Added in for uml:not


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
(define printed-uml:not? #t)
