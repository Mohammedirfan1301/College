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
  (cons x y))   ;; Make pair of two points

(define (x-point p) 
  (car p))      ;; Get first point of the pair (x)

(define (y-point p) 
  (cdr p))      ;; Get the second point of the pair (y)
 
;; Segment 
;; similarly, make-seg is the constructor;
;; start-seg and end-seg are accessors.
;; midpoint-seg is an accessor that finds the midpoint of the line
;; segment. 
;; make sure to use your point object inside your line segment!
;; (two of them)
(define (make-seg start-point end-point) 
  (make-point start-point end-point))   ;; Make a pair of points

(define (start-seg segment) 
  (x-point segment))        ;; Start is the x-point

(define (end-seg segment)             
  (y-point segment))        ;; End is the y-point
   
;; should return a point (e.g. use make-point, duh)
;; This function will use the mid-pt formula as following:
;; mid-pt formula is: (x1+x2) / 2 or (y1+y2) / 2
;; It will return the mid-pt of the x-points and the y-points.
(define (midpoint-seg segment)          
  ;; Returns the mid-pts
  (make-point 
   (/ (+ (x-point(start-seg segment)) (x-point(end-seg segment))) 2) ;; x-point
   (/ (+ (y-point(start-seg segment)) (y-point(end-seg segment))) 2) ;; y-point
  )
)
  
;; SICP exercise 2.3 (pp. 90). Here you represent rectangles and
;; construct procedures to compute perimeter and area.  Fill in the
;; below procedures
;; more constructors and selectors
;; you may use your point objects if you desire 

(define (make-rect x1 y1 x2 y2)
  ;; Make a pair of segments representing the rectangle.
  (make-point (make-point x1 y1) (make-point x2 y2)))

(define (corner1 rect)
  ; should return some kind of object representing a corner
  (car rect))

(define (corner2 rect)
  ; should return the diagonally opposite corner
  (cdr rect))

(define (width rect)
  ; must use corner1 and corner2 selectors
  ;; Add the two x-points of the rectangle together.
  (+ (x-point (corner1 rect)) (x-point (corner2 rect)))
)

(define (height rect) 
  ; must use corner1 and corner2 selectors
  ;; Add the two y-points together
  (+ (y-point (corner1 rect)) (y-point (corner2 rect)))
)
  
;; area and perimeter 
;; must use your width and height abstractions!
(define (area rect) 
  ;; Area formula is just A = width * height
  (* (width rect) (height rect))
)

(define (perimeter rect) 
  ;; Perimeter formula is just P = 2*Width + 2*Height
  (+ (* (width rect) 2) (* (height rect) 2))
)

;; SICP exercise 2.4 -- using procedure closures to implement cons.
;;
;; Here is an alternative procedural representation of pairs. Note that
;; (my-car (my-cons x y)) yields x for any objects x and y.

;; Based on these definitions for my-cons and my-cdr:

(define (my-cons x y)
  (lambda (m) (m x y))
)

(define (my-car z)
  (z (lambda (p q) p))
)

;; what is the corresponding definition of my-cdr? (Hint: To verify
;; that this works, make use of the substitution model of Section
;; 1.1.5.)  Fix the code below to work.

(define (my-cdr z)
  ;; I return q as cdr basically returns the second item
  ;; in a cons pair. Since my-car returns p, which is the first item
  ;; in the pair "p q", my-cdr should return q.
  (z (lambda (p q) q))
)

