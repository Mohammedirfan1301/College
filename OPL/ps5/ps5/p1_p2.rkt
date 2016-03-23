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
(define p1_1 #f)
#|
    Explicit Dispatch
      New Types

      New Operations

    Data-Directed
      New Types

      New Operations

    Message-Passing
      New Types

      New Operations

|#

;;;    Which organization would be most appropriate for a system in
;;;    which new types must often be added?  Change #f to #t after
;;;    answering.
(define p1_2 #t)
#|
    Data-Directed, since its simple to add new types to the system by just
    adding entries to a table.
|#


;;;    Which would be most appropriate for a system in which new
;;;    operations must often be added?  Change #f to #t after
;;;    answering.
(define p1_3 #t)
#|
    Message-Passing, since its easy to update the operations by just adding
    a conditional statement.
|#


n;; *******************************************************************

;;; Problem 2: Exercise 2.77

;;;    Describe in detail why this works. As an example, trace through
;;;    all the procedures called in evaluating the expression
;;;    (magnitude z) where z is the object shown in figure 2.24.
;;;    Change #f to #t after answering.
(define p2_1 #f)


;;;    In particular, how many times is apply-generic invoked?
;;;    What procedure is dispatched to in each case?
;;;    Change #f to #t after answering.
(define p2_2 #f)

;;; **************************** END OF FIILE ************************
