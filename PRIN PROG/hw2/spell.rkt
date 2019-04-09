#lang racket

; *********************************************
; *  314 Principles of Programming Languages  *
; *  Spring 2019                              *
; *  Student Version                          *
; *********************************************

;; contains "ctv", "A", and "reduce" definitions
(require "include.rkt")

;; contains simple dictionary definition
(require "test-dictionary.rkt")

;; -----------------------------------------------------
;; HELPER FUNCTIONS

(define compares
  (lambda (hashlist hash)                     ; Compares hashlist to hash
    (cond ((= hashlist hash) -1) (else hash)) ; "Do not use eq? or equal?"
))

(define inDictionary
  (lambda (w bitvector)
    (define bool (reduce compares bitvector w)) ; Pass compares function to reduce to find #t or #f
    (cond ((= -1 bool) #t) (else #f))
))

(define spellcheck (lambda (hashfunctionlist w bitvector) (cond ((null? hashfunctionlist) #t) ; Base case
  ((and (inDictionary ((car hashfunctionlist) w) bitvector) ; Take first from hashfunctionlist
    (spellcheck (cdr hashfunctionlist) w bitvector)) #t) ; Recursive call, takes 2nd from list
  (else #f))
))

(define createhash 
  (lambda (hashfunctionlist w) (cond ((null? hashfunctionlist) '()) ; Base case
    (else (cons ((car hashfunctionlist) w) (createhash (cdr hashfunctionlist) w)))) ; Construct pair, i->e first from hashlist: result from createhash
))

(define createbv (lambda (hashfunctionlist dict)
  (cond ((null? dict) '()) ; Base case
    (else (append (createhash hashfunctionlist (car dict)) (createbv hashfunctionlist (cdr dict))) ; Recursive way of creating a bitvector, append first w/ second
  ))
))

;; -----------------------------------------------------
;; KEY FUNCTION

(define key
  (lambda (w)
    (reduce
     (lambda (a b)
       (+ (* 29 b) a))
     (map ctv w)
     5413)
))

;; -----------------------------------------------------
;; EXAMPLE KEY VALUES
;;   (key '(h e l l o))       = 111037761665
;;   (key '(m a y))           = 132038724
;;   (key '(t r e e f r o g)) = 2707963878412931

;; -----------------------------------------------------
;; HASH FUNCTION GENERATORS

;; value of parameter "size" should be a prime number
(define gen-hash-division-method
  (lambda (size) ;; range of values: 0..size-1
     (lambda (w)
       (modulo (key w) size))
))

;; value of parameter "size" is not critical
;; Note: hash functions may return integer values in "real"
;;       format, e.g., 17.0 for 17

(define gen-hash-multiplication-method
  (lambda (size) ;; range of values: 0..size-1
     (lambda (w)
       (floor (* size (- (* (key w) A) (floor (* (key w) A))))))
))


;; -----------------------------------------------------
;; EXAMPLE HASH FUNCTIONS AND HASH FUNCTION LISTS

(define hash-1 (gen-hash-division-method 70111))
(define hash-2 (gen-hash-division-method 89989))
(define hash-3 (gen-hash-multiplication-method 700426))
(define hash-4 (gen-hash-multiplication-method 952))

(define hashfl-1 (list hash-1 hash-2 hash-3 hash-4))
(define hashfl-2 (list hash-1 hash-3))
(define hashfl-3 (list hash-2 hash-3))

;; -----------------------------------------------------
;; EXAMPLE HASH VALUES
;;   to test your hash function implementation
;;
;; (hash-1 '(h e l l o))        ==> 26303
;; (hash-1 '(m a y))            ==> 19711
;; (hash-1 '(t r e e f r o g))  ==> 3010
;;
;; (hash-2 '(h e l l o))        ==> 64598
;; (hash-2 '(m a y))            ==> 24861
;; (hash-2 '(t r e e f r o g))  ==> 23090
;;
;; (hash-3 '(h e l l o))        ==> 313800.0
;; (hash-3 '(m a y))            ==> 317136.0
;; (hash-3 '(t r e e f r o g))  ==> 525319.0
;;
;; (hash-4 '(h e l l o))        ==> 426.0
;; (hash-4 '(m a y))            ==> 431.0
;; (hash-4 '(t r e e f r o g))  ==> 714.0

;; -----------------------------------------------------
;; SPELL CHECKER GENERATOR

(define gen-checker
  (lambda (hashfunctionlist dict)
     (define bitvector (createbv hashfunctionlist dict))
     (lambda (w)
      (spellcheck hashfunctionlist w bitvector))
))

;; -----------------------------------------------------
;; EXAMPLE SPELL CHECKERS

(define checker-1 (gen-checker hashfl-1 dictionary))
(define checker-2 (gen-checker hashfl-2 dictionary))
(define checker-3 (gen-checker hashfl-3 dictionary))

;; EXAMPLE APPLICATIONS OF A SPELL CHECKER
;;
;;  (checker-1 '(a r g g g g)) ==> #f
;;  (checker-2 '(h e l l o)) ==> #t
;;  (checker-2 '(a r g g g g)) ==> #f
