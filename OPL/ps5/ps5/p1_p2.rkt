#lang racket

;;;+++++++++++++++ Required for auto grading +++++++++++++++++++++++++
(define nil '())

;;;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; *******************************************************************


;;; Problem 1: Exercise 2.76

;;;Answer:

;;;    For each of the three strategies -- generic operations with
;;;    explicit dispatch, data-directed style, and
;;;    message-passing-style; describe the changes that must be made
;;;    to a system in order to add new types or new operations.
;;;    Change #f to #t after answering.
(define p1_1 #t)
#|
*********************
* Explicit Dispatch *
*********************
Adding a new type requires updating all existing operations so that 
they support the new type.

Adding a new operation requires adding a new procedure, which should handle
all of the types within the new procedure.

*****************
* Data-Directed *
*****************
Adding a new type requires adding a procedure for each of the operations,
and adding them to the table of operations.

Adding a new operation requires adding a procedure for each type, which will
perform the operation, and adding them to the table of operations.

*******************
* Message-Passing *
*******************
Adding a new type requires writting a new constructor for the type.

Adding a new operation requires changing the existing constructors to
support the new operation.

|#

;;;    Which organization would be most appropriate for a system in
;;;    which new types must often be added?  Change #f to #t after
;;;    answering.
(define p1_2 #t)
#|
    Data-Directed, since it is simple to add new types to the system by just
    adding entries to a table.
|#


;;;    Which would be most appropriate for a system in which new
;;;    operations must often be added?  Change #f to #t after
;;;    answering.
(define p1_3 #t)
#|
    Message-Passing, since it is easy to update the operations by just adding
    a conditional statement.
|#


;; *******************************************************************

;;; Problem 2: Exercise 2.77

;;;    Describe in detail why this works. As an example, trace through
;;;    all the procedures called in evaluating the expression
;;;    (magnitude z) where z is the object shown in figure 2.24.
;;;    Change #f to #t after answering.
(define p2_1 #t)
#|
The operations was only defined for rectangular and polar, and not for complex.
This is why it failed, as the operations were not defined for the complex case.

By adding in the four lines suggested, the complex tag will be supported and the
error message from apply-generic will not appear.

Procedure Trace:

First we have the following operation:
(magnitude '(complex rectangular 3 . 4))

this then calls:
(apply-generic 'magnitude '(complex rectangular 3 . 4))

What happens is apply-generic calls the procedure it was given.
Ssince Z also has two tags, complex and rectangular, the complex tag 
gets stripped off, and we end up with:
(apply magnitude '((rectangular 3 . 4)))

Which then leads to:
(magnitude '(rectangular 3 . 4))

We can then go through and deal with the rectangular package:
(apply-generic 'magnitude '(rectangular 3 . 4))
(apply rectanguler-magnitude '((3 . 4))))
(rectanguler-magnitude '(3 . 4)))
= 5

|#

;;;    In particular, how many times is apply-generic invoked?
;;;    What procedure is dispatched to in each case?
;;;    Change #f to #t after answering.
(define p2_2 #t)
#|

Apply-generic is invoked twice.

The first time it is dispatched to the generic magnitude.
The second time is is dispatched to the rectangular magnitude.

|#


;;; **************************** END OF FIILE ************************
