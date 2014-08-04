(setq animals '(gazelle giraffe lion tiger))
(while animals
  (print (car animals))
  (setq animals (cdr animals)))

(defun print-elements-of-list (list)
  "Print each element of a list."
  (while list
    (print (car list))
    (setq list (cdr list))))

(print-elements-of-list animals)

(defun triangle (number)
  "Return sums of 1 to `number`, inclusive."
  (let ((count 0))
    (while (> number 0)
      (setq count (+ number count))
      (setq number (1- number)))
    count))

(triangle 10)



;; dolist works like a while loop that ‘cdrs down a list’: dolist automatically
;; shortens the list each time it loops—takes the cdr of the list—and binds the
;; car of each shorter version of the list to the first of its arguments.
;;
;; dotimes loops a specific number of times: you specify the number.
(defun reverse-list-with-while (list)
  "Using while, reverse the order of a list."
  (let ((result))
    (while list
      (setq result (cons (car list) result))
      (setq list (cdr list)))
    result))

(setq animals '(gazelle giraffe lion tiger))
(reverse-list-with-while animals)
animals

(defun reverse-list-with-dolist (list)
  "Using dolist, reverse the order of a list."
  (let ((result))
    (dolist (item list result)
      (setq result (cons item result)))))

(setq animals '(gazelle giraffe lion tiger))
(reverse-list-with-dolist animals)
animals

(defun triangle-using-dotimes (number-of-rows)
  "Using dotimes, add up the number of pebbles in a triangle."
  (let ((total 0)) ; otherwise a total is a void variable
    (dotimes (number number-of-rows total)
      (setq total (+ total (1+ number))))))

(triangle-using-dotimes 4)

(let (value)
  (dotimes (number 3 value)
    (setq value (cons number value))))



;; while with break;  Note the break symbol is arbitray
(setq x 0 total 0)
(catch 'break
  (while t
    (incf total x)
    (if (> (incf x) 10)
        (throw 'break total))))

;; while with continue;  Note the continue symbol is arbitray
(setq x 0 total 0)
(while (< x 100)
  (catch 'continue
    (incf x)
    (if (zerop (% x 5))
        (throw 'continue nil))
    (incf total x)))
total





;; Pretty much all iteration in Emacs Lisp is easiest using the loop macro from
;; the Common Lisp package. Just do this to enable loop:
;;   (require 'cl)  ; get lots of Common Lisp goodies
;; The loop macro is a powerful minilanguage with lots of features, and it's
;; worth reading up on. I'll use it in this primer to show you how to do basic
;; looping constructs from other languages.
(setq x 0)
(loop do
      (setq x (1+ x))
      while
      (< x 10))
x

;; // JavaScript
;; var result = [];
;; for (var i = 10, j = 0; j <= 10; i--, j += 2) {
;;   result.push(i+j);
;; }
(loop with result = '()                 ; one-time initialization
      for i downfrom 10                 ; count i down from 10
      for j from 0 by 2                 ; count j up from 0 by 2
      while (< j 10)                    ; stop when j >= 10
      do
      (push (+ i j) result)             ; fast-accumulate i+j
      finally
      return (nreverse result))         ; reverse and return result


;; some other loop examples.
(setq square (loop for i in '(1 2 3 4 5 6)
                   collect (* i i)))
square
