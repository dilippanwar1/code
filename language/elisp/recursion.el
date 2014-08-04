(defun print-elements-recursively (list)
  "Print element of list recursively."
  (if list
      (progn
        (print (car list))
        (print-elements-recursively (cdr list)))))

(setq animals '(gazelle giraffe lion tiger))
(print-elements-recursively animals)



;; Recursive Pattern: every
;; In the every recursive pattern, an action is performed on every element
;; of a list. The basic pattern is:
;;   • If a list be empty, return nil.
;;   • Else, act on the beginning of the list (the car of the list).
;;     − through a recursive call by the function on the rest (the cdr) of
;;       the list,
;;     − and, optionally, combine the acted-on element, using cons, with the
;;       results of acting on the rest.
(defun square-each (number-list)
  "Square each number of a list."
  (if number-list
      (cons
       (* (car number-list) (car number-list))
       (square-each (cdr number-list)))))

(square-each '(1 2 3 4 5))



;; Recursive Pattern: accumulate
;; Another recursive pattern is called the accumulate pattern. In the accumulate
;; recursive pattern, an action is performed on every element of a list and the
;; result of that action is accumulated with the results of performing the action
;; on the other elements.
;; This is very like the ‘every’ pattern using cons, except that cons is not used,
;; but some other combiner. The pattern is:
;;   • If a list be empty, return zero or some other constant.
;;   • Else, act on the beginning of the list (the car of the list),
;;     − and combine that acted-on element, using + or some other combining
;;       function, with
;;     − a recursive call by the function on the rest (the cdr) of the list.
(defun add-elements (number-list)
  "Add the elements of a number-list togeter."
  (if number-list
      (+ (car number-list)
         (add-elements (cdr number-list)))
    0))

(add-elements '(1 2 3 4 5))



;; Recursive Pattern: keep
;; A third recursive pattern is called the keep pattern. In the keep recursive
;; pattern, each element of a list is tested; the element is acted on and the
;; results are kept only if the element meets a criterion.
;; Again, this is very like the ‘every’ pattern, except the element is skipped
;; unless it meets a criterion.
(defun keep-three-letter-words (word-list)
  "Keep only three letter words for a given list."
  (cond
   ((not word-list) nil)
   ((eq 3 (length (symbol-name (car word-list))))
    (cons (car word-list) (keep-three-letter-words (cdr word-list))))
   (t (keep-three-letter-words (cdr word-list)))))

(keep-three-letter-words '(one two three four five six))



;; Recursion with deferment. If we pass 7 to the following function, then the
;; recursive call will end up with something like this:
;; (+ 7 (triangle-recursively 6))
;; (+ 7 6 (triangle-recursively 5))
;; (+ 7 6 5 (triangle-recursively 4))
;; ......
;; (+ 7 6 5 4 3 2 1)
(defun triangle-recursively (number)
  "Return the sum of the numbers 1 through NUMBER inclusive.
Uses recursion."
  (if (= number 1)                      ; do-again-test
      1                                 ; then-part
    (+ number                           ; else-part
       (triangle-recursively            ; recursive call
        (1- number)))))                 ; next-step-expression



;; Recursion without deferment.
(defun triangle-initialization (number)
  "Return the sum of the numbers 1 through NUMBER inclusive.
This is the ‘initialization’ component of a two function
duo that uses recursion."
  (triangle-recursive-helper 0 0 number))

(defun triangle-recursive-helper (sum counter number)
  "Return SUM, using COUNTER, through NUMBER inclusive.
This is the ‘helper’ component of a two function duo
that uses recursion."
  (if (> counter number)
      sum
    (triangle-recursive-helper (+ sum counter) ; sum
                               (1+ counter)    ; counter
                               number)))       ; number



