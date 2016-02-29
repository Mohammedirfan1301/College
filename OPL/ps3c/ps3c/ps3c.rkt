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

;; Update one record
(define (update-record rec)
  (set! cdDB (remove rec cdDB))     ;; First we remove
  ;;(set! cdDB (append cdDB (list rec)))   ;; Then we append.
)

; Selectors
; these should retrieve the appropriate item from the record object.
;
; the sample ones below are broken because they return a fixed
; result regardless of the record object provided.
;
; write selector procedures for each of the fields of record.
(define (title rec)
  ;; This is an iterative helper function to search the DB for
  ;; the given record.
  ;; I did it iteratively because I couldn't figure out a recursive solution. ¯\_(ツ)_/¯
  (define (title-iter rec DB)
      (cond
         ;; We didn't find the record so return a nil.
         ((null? DB) nil)
        
         ;; FOUND IT! return the **TITLE**. 
         ;; (found this through trial and error in the console)
         ((equal? (car DB) rec) (caar DB))
         
         ;; Keep looping.
         (else (title-iter rec (cdr DB)))
      )
  )
  ;; Gotta seed the iterative helper function.
  (title-iter rec cdDB)
)

(define (artist rec)
  ;; This is an iterative helper function to search the DB for
  ;; the given record.
  ;; I did it iteratively because I couldn't figure out a recursive solution. ¯\_(ツ)_/¯
  (define (title-iter rec DB)
      (cond
         ;; We didn't find the record so return a nil.
         ((null? DB) nil)
        
         ;; FOUND IT! return the **ARTIST**. 
         ;; (found this through trial and error in the console)
         ((equal? (car DB) rec) (cadar DB))
         
         ;; Keep looping.
         (else (title-iter rec (cdr DB)))
      )
  )
  ;; Gotta seed the iterative helper function.
  (title-iter rec cdDB)
)

(define (price rec)
  ;; This is an iterative helper function to search the DB for
  ;; the given record.
  ;; I did it iteratively because I couldn't figure out a recursive solution. ¯\_(ツ)_/¯
  (define (title-iter rec DB)
      (cond
         ;; We didn't find the record so return a nil.
         ((null? DB) nil)
        
         ;; FOUND IT! return the **PRICE**. 
         ;; (found this through trial and error in the console)
         ((equal? (car DB) rec) (caddar DB))
         
         ;; Keep looping.
         (else (title-iter rec (cdr DB)))
      )
  )
  ;; Gotta seed the iterative helper function.
  (title-iter rec cdDB)
)

(define (category rec)
  ;; This is an iterative helper function to search the DB for
  ;; the given record.
  ;; I did it iteratively because I couldn't figure out a recursive solution. ¯\_(ツ)_/¯
  (define (title-iter rec DB)
      (cond
         ;; We didn't find the record so return a nil.
         ((null? DB) nil)
        
         ;; FOUND IT! return the **CATEGORY**. 
         ;; (found this through trial and error in the console)
         ((equal? (car DB) rec) (car (cdddar DB)))
         
         ;; Keep looping.
         (else (title-iter rec (cdr DB)))
      )
  )
  ;; Gotta seed the iterative helper function.
  (title-iter rec cdDB)
)

(define (units-in-stock rec)
  ;; This is an iterative helper function to search the DB for
  ;; the given record.
  ;; I did it iteratively because I couldn't figure out a recursive solution. ¯\_(ツ)_/¯
  (define (title-iter rec DB)
      (cond
         ;; We didn't find the record so return a nil.
         ((null? DB) nil)
        
         ;; FOUND IT! return the **UNITS IN STOCK**. 
         ;; (found this through trial and error in the console)
         ((equal? (car DB) rec) (cadr (cdddar DB)))
         
         ;; Keep looping.
         (else (title-iter rec (cdr DB)))
      )
  )
  ;; Gotta seed the iterative helper function.
  (title-iter rec cdDB)
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
  ;; Check variable for matching by title / artist.
  (define check null)
  
  ;; Match by title
  (set! check
    (filter 
       (lambda (rec) 
         (equal? (title rec) this-title)
       ) 
    db)
  )
  
  ;; See if what we got was null or not.
  (if (null? check)
      ;; true case, so the title doesn't match.
      this-title
      
      ;; false case, so update that record in the database.
      ;(list this-title (cadar check) (caddar check) (car (cdddar check)) num-copies)
      
      ;; This is broken badly.
      (update-record (make-record this-title (cadar check)(caddar check) (car (cdddar check)) num-copies))
 )
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
  ;; Check variable for matching by title / artist.
  (define check null)
  
  ;; Match by title & artist
  (set! check
    (filter 
       (lambda (rec) 
         (equal? (title rec) this-title)
         (equal? (artist rec) this-artist)
       ) 
    db)
  )
  
  ;; See if what we got was null or not.
  (if (null? check)
      ;; true case so return 0.
      0  
      
      ;; false case so apply units-in-stock to it.
      (units-in-stock (car check))
  )
)

;;;;;;;;1h. 
; blues-sale
; map a fcn over the db that either:
;  outputs a new record with adjusted price (if category is blues), or
;  just outputs the existing record
(define (blues-sale db)
  
  ;; need to filter all blues CDs, and discount by 10%.
  
  'foo)

;;;;;;;;1i.
; carry-cd?
; filter the db for a matching record,
; then return a boolean if units-in-stock is more than 0.
; make sure to deal with the case of the record not existing in the DB
(define (carry-cd? this-title this-artist db)
  ;; Check variable for matching by title / artist.
  (define check null)
  
  ;; Match by title & artist
  (set! check
    (filter 
       (lambda (rec) 
         (equal? (title rec) this-title)
       ) 
    db)
  )
  
  ;; See if what we got was null or not.
  (if (null? check)
      ;; true case so return false since there is no record...
      #f  
      
      ;; false case so apply units-in-stock to it.
      (if (> (units-in-stock (car check)) 0)
          #t  ;; Greater than 0 so true.
          #f  ;; 0 or less, so false.
      )
  )
)
