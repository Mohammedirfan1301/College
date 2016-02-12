#lang racket

;; ps2c.rkt
;; last modified Thu Feb  4 20:13:43 2016 fredm@cs.uml.edu

;; SICP exercise 2.2 (pp. 89-90). In this problem you create data
;; structures in Scheme representing line segments in a plane.

(define (print-point p) 
   (newline) 
   (display "'(")   ;;don't remove the single quote. It is needed for
		    ;;auto grader
   (display (x-point p)) 
   (display ", ") 
   (display (y-point p)) 
   (display ")")) 

;; Fill in the below procedures  
;;
;; the idea here is that you are creating an abstraction of the X,Y
;; point object.
;; 
;; make-point is the constructor and x-point and y-point are the
;; selectors. 
;; 
;; you can use any internal representation you like as long as the
;; constructor and selectors are consistent with the internal
;; representation. 
;; Point 
(define (make-point x y) 
  1)

(define (x-point p) 
  1)

(define (y-point p) 
  1)
 
;; Segment 
;; similarly, make-seg is the constructor;
;; start-seg and end-seg are accessors.
;; midpoint-seg is an accessor that finds the midpoint of the line
;; segment. 
;; make sure to use your point object inside your line segment!
;; (two of them)
(define (make-seg start-point end-point) 
  1)

(define (start-seg segment) 
  1)   

(define (end-seg segment)
  1)
  
 ; should return a point
(define (midpoint-seg segment)
  1)
  
;; SICP exercise 2.3 (pp. 90). Here you represent rectangles and
;; construct procedures to compute perimeter and area.  Fill in the
;; below procedures
;; more constructors and selectors
;; you may use your point objects if you desire 

(define (make-rect x1 y1 x2 y2)
  1)

(define (corner1 rect)
  ; should return some kind of object representing a corner
  1)

(define (corner2 rect)
  ; should return the diagonally opposite corner
  1)

(define (width rect)
  ; must use corner1 and corner2 selectors
  1)

(define (height rect) 
  ; must use corner1 and corner2 selectors
  1)
  
;; area and perimeter 
;; must use your width and height abstractions!
(define (area rect) 
  1)

(define (perimeter rect) 
  1)

;; SICP exercise 2.4 -- using procedure closures to implement cons.
;;
;; Here is an alternative procedural representation of pairs. Note that
;; (my-car (my-cons x y)) yields x for any objects x and y.

;; Based on these definitions for my-cons and my-cdr:

(define (my-cons x y)
  (lambda (m) (m x y)))

(define (my-car z)
  (z (lambda (p q) p)))

;; what is the corresponding definition of my-cdr? (Hint: To verify
;; that this works, make use of the substitution model of Section
;; 1.1.5.)  Fix the code below to work.

(define (my-cdr z)
  1)

