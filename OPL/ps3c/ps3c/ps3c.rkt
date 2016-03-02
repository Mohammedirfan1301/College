#lang racket

;; last modified Sat Feb 20 14:29:05 2016 fredm@cs.uml.edu
;; this assignment originally created at WPI

;; +++++++++++++++ Required for auto grading ++++++++++++++++++++++++++++
(define nil '())
;; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

;; **********************************************************************
;;
;; 1. Assume that we want to develop an inventory database for an
;; online CD store.  
;;
;; For each CD, the database stores its title, artist, price, how many
;; copies are in stock, and its category of music (such as rock,
;; blues, or country).  
;;
;; Write a data definition for CD inventories. When completing the
;; following exercises, please make sure to use map, filter, and
;; accumulate (aka, reduce) as much as reasonable.  
;; 
;; 1a. Create a constructor procedure with parameters, title, artist,
;; price, category, and units-in-stock, and corresponding accessors to
;; retrieve these fields.  
;; 
;; 1b. Populate an inventory (i.e., a list) with 10 or so records
;; created from your constructor.  
;;
;; 1c. Write a procedure all-titles that consumes an inventory and
;; produces a list of all titles in the inventory.  
;; 
;; 1d. Write a procedure titles-in-stock that consumes an inventory
;; and produces a list of all titles in the inventory with at least 1
;; copy in stock.  
;;
;; 1e. Write a procedure restock that consumes a CD title, number of
;; new copies of that CD and an inventory and produces an inventory in
;; which the named CD has the given number of additional copies (and
;; all other CDs remain the same).  
;; 
;; 1f. Write a procedure titles-by that consumes an artist name and
;; inventory and produces a list of titles of CDs by that artist.
;; 
;; 1g. Write a procedure copies-in-stock that consumes a CD title,
;; artist name and an inventory and produces the number of copies of
;; that item that are in stock.  Return 0 if the named CD isn't in the
;; inventory.
;; 
;; 1h. Write a procedure blues-sale that consumes an
;; inventory and produces an inventory in which all blues CDs are
;; discounted by 10%.
;; 
;; 1i. Write a procedure carry-cd? that consumes a
;; title and artist name and produces a boolean indicating whether
;; that item is in the inventory (whether in or out of stock).

;;;;;;;;;;1a.
;Constructors
; model the db as a list of records.
; don't change this code.
(define cdDB '() )

; Each record must be a compound object that bundles together 
; a title,  artist, price, category, and units-in-stock.
; 
; write code to do that and return a "record" object.
(define (make-record title artist price category units-in-stock)
  (list title artist price category units-in-stock))

; Insert one record into the database, by rebinding the global symbol
; cdDB to a new list with the new record appended.
; don't change this code
(define (insert-record rec)
  (set! cdDB (append cdDB (list rec))))

; Selectors
; these should retrieve the appropriate item from the record object.
;
; the sample ones below are broken because they return a fixed
; result regardless of the record object provided.
;
; write selector procedures for each of the fields of record.
(define (title rec)
  ;; Record looks like this: 
  ;; '("Revolver" "The Beatles" 14.99 rock 3)
  ;; Since rec is a list, we just want the first string.
  (first rec)    ;; Same as "car rec"
)

(define (artist rec)
  (second rec)   ;; Artist the is "second" item that we want. (same as "cadr rec")
)

(define (price rec)
  (third rec)    ;; Price is the "third" item that we want.   (same as "caddr rec")
)

(define (category rec)
  (fourth rec)   ;; Category is the "fourth" item that we want. (same as "cadddr rec")
)

(define (units-in-stock rec)
  (fifth rec)    ;; Units is the "fifth" item in the list that we want. (same as "(car (cddddr rec))")
)

;;;;;;;1b.

; insert a bunch of records.
; see examples in file "freds-db.rkt"
; make sure to submit that file back for autograding.
; but you should put your own here!!
; provide your own series of several (to many) insert-record operations.
; remember, insert-record is already provided;
; this should just work once you've implemented your constructor
; and selectors correctly.
(insert-record (make-record "Revolver" "The Beatles" 14.99 'rock 3))
(insert-record (make-record "Facelift" "Alice in Chains" 12.98 'Rock 7))
(insert-record (make-record "Pyromania" "Def Leppard" 6.78 'Classic-Rock 100))
(insert-record (make-record "Hysteria" "Def Leppard" 10.99 'Classic-Rock 99))
(insert-record (make-record "Vault: Def Leppard Greatest Hits" "Def Leppard" 10.99 'Classic-Rock 999))
(insert-record (make-record "Leftoverture" "Kansas" 4.79 'Classic-Rock 111))

;; Test cases for "titles in stock"
(insert-record (make-record "Foreigner" "Foreigner" 3.71 'Classic-Rock 0))          
(insert-record (make-record "Double Vision" "Foreigner" 4.99 'Classic-Rock 0))

;; Test cases for "blues-sale" function
(insert-record (make-record "Midnight Run" "Bobby Blue Bland" 8.1 'blues 2))
(insert-record (make-record "Phantom Blues" "Taj Mahal" 8.1 'blues 3))

;;;;;;;1c.
; all-titles
; map the title operator over the db.
; use the built-in "map" operation and your title selector procedure
; to return a list of all the titles in a database.
(define (all-titles db)
  (map title db))

;;;;;;1d.
; titles-in-stock
; use the built-in "filter" operation to filter a database to 
; keep only records with units-in-stock being more than zero.
; then, map the title selector over that result.

;; This is currently returning albums with "0" in stock...
(define (titles-in-stock db)
  ;; Call all-titles on the filtered database.
  (all-titles
    ;; Return only the records which are in stock (1 or more items in stock)
    (filter (lambda (rec) (> (units-in-stock rec) 0)) db)
  )
)

;;;;;;;1e.
; restock
; map a fcn over the database that returns either:
;  a new record with the num of copies increased by the restock count, or
;  just the existing record (if title doesn't match)
(define (restock this-title num-copies db)
  
  ;; Map over the DB and update the record.
  ;; This will then return the update database as required.
  (map (lambda (rec)
     ;; See if the title is equal, as we want to update the record if so.
     (if (equal? this-title (title rec))
         ;; Update the record.
         (make-record this-title (artist rec) (price rec) (category rec) num-copies)
               
         rec    ;; false case so do nothing but return the rec.
     ))
   db)
)

;;;;;;;;1f.
; titles-by
; filter the db by matching on artist, then map title over it.
(define (titles-by this-artist db)
  
  ;; Call all-titles on the filtered database.
  (all-titles
    ;; Return only the records with the given artist.
    (filter (lambda (rec) (equal? (artist rec) this-artist)) db)
  )
)

;;;;;;;;1g.
; copies-in-stock
; filter by by matching title and artist, then apply units-in-stock to it.
; make sure to deal with the case of the record not existing in the DB
; this should produce a number
(define (copies-in-stock this-title this-artist db)
  
  ;; Filter by title & artist. Check will hold the record (if it exists).
  ;; Apply "and" because we need to match BOTH title AND artist to find the record.
  (define check 
    (filter (lambda (rec) (and (equal? this-title (title rec))
                          (equal? (artist rec) this-artist))) db))
  
  ;; See if the record exists or not.
  (if (null? check)
    0                              ;; Return 0, we didn't find it.
    (units-in-stock (car check))   ;; Record exists so call units-in-stock on it.
  )                                ;; car because check looks like '(()) and we want just '()
)

;;;;;;;;1h. 
; blues-sale
; map a fcn over the db that either:
;  outputs a new record with adjusted price (if category is blues), or
;  just outputs the existing record
(define (blues-sale db)

  ;; Map over the DB and update the record.
  ;; This will then return the update database as required.
  (map (lambda (rec)
     ;; See if the title is equal, as we want to update the record if so.
     (if (equal? 'blues (category rec))
         ;; Update the record.
         (make-record (title rec) (artist rec) (* (price rec) .90) (category rec) (units-in-stock rec))
               
         rec    ;; false case so do nothing but return the rec.
     ))
   db)
)
  
;;;;;;;;1i.
; carry-cd?
; filter the db for a matching record,
; then return a boolean if units-in-stock is more than 0.
; make sure to deal with the case of the record not existing in the DB
(define (carry-cd? this-title this-artist db)
  
  ;; Check variable for matching by title / artist.
  ;; Just need to check the title.
  (define check (filter (lambda (rec) (equal? (title rec) this-title)) db) )
  
  ;; See if what we got was null or not.
  (if (null? check)
      #f  ;; Return false because check is null, so we don't have a matching record.
      
      ;; Call units-in-stock and see if it is greater than zero.
      (if (> (units-in-stock (car check)) 0)
          #t  ;; Greater than 0 so true.
          #f  ;; 0 or less, so false.
      )
  )
)
