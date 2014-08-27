(if true-or-false-test
    action-to-carry-out-if-the-test-returns-true
  action-to-carry-out-if-the-test-returns-false )

(defun type-of-animal (characteristic)
  "Print message in echo area depending on CHARACTERISTIC.
If the CHARACTERISTIC is the symbol 'fierce',
then warn of a tiger."
  (if (equal characteristic 'fierce)
      (message "It's a tiger!")
    (message "It's not fierce!")))

(type-of-animal 'fierce)
(type-of-animal 'zebra)



;; In fact, ‘false’ is just our old friend nil. Anything else—anything at
;; all—is ‘true’.  Note, nil is a Symbol.  As far as the Lisp interpreter
;; is concerned, () and nil are the same. Humans, however, tend to use nil
;; for false and () for the empty list.

(if 4
    'true
  'false)

(if nil
    'true
  'false)



;; (cond
;;  (first-true-or-false-test first-consequent )
;;  (second-true-or-false-test second-consequent )
;;  (third-true-or-false-test third-consequent )
;;  ...)
;; When the Lisp interpreter evaluates the cond expression, it evaluates the
;; first element (the car or true-or-false-test) of the first expression in
;; a series of expressions within the body of the cond.
;;
;; If the true-or-false-test returns nil the rest of that expression, the
;; consequent, is skipped and the true-or-false-test of the next expression
;; is evaluated. When an expression is found whose true-or-false-test returns
;; a value that is not nil, the consequent of that expression is evaluated.
;; The consequent can be one or more expressions. If the consequent consists
;; of more than one expression, the expressions are evaluated in sequence and
;; the value of the last one is returned. If the expression does not have a
;; consequent, the value of the true-or-false-test is returned. If none of
;; the true-or-false-tests test true, the cond expression returns nil.
(setq number 5)
(cond ((> number 3)
       8
       4
       5
       6)
      ((< number 3) 1))
