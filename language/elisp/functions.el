;; All functions are defined in terms of other functions, except for a few
;; primitive functions that are written in the C programming language. When
;; you write functions' definitions, you will write them in Emacs Lisp and
;; use other functions as your building blocks. Some of the functions you will
;; use will themselves be written in Emacs Lisp (perhaps by you) and some will
;; be primitives written in C.


;; A function definition has up to five parts following the word defun:
;; 1. The name of the symbol to which the function definition should be attached.
;; 2. A list of the arguments that will be passed to the function. If no
;;    arguments will be passed to the function, this is an empty list, ().
;; 3. Documentation describing the function. (Technically optional, but strongly
;;    recommended.)
;; 4. Optionally, an expression to make the function interactive so you can use
;;    it by typing M-x and then the name of the function; or by typing an
;;    appropriate key or keychord
;; 5. The code that instructs the computer what to do: the body of the function
;;    definition.
(defun multiply-by-seven (number)
  "Multiply number by 7."
  (* 7 number))

(multiply-by-seven 2)


;; Interestingly, when you call an interactive function interactively, the value
;; returned is not automatically displayed in the echo area. This is because you
;; often call an interactive function for its side effects, such as moving
;; forward by a word or line, and not for the value returned. If the returned
;; value were displayed in the echo area each time you typed a key, it would be
;; very distracting.
;;
;; You can install this code by placing your cursor after it and typing C-x C-e.
;; The name of the function will appear in your echo area. Then, you can use
;; this code by typing C-u and a number and then typing M-x multiply-by-seven
;; and pressing RET. The phrase ‘The result is ...’ followed by the product will
;; appear in the echo area.
;;
;; Speaking more generally, you invoke a function like this in either of two ways:
;; 1. By typing a prefix argument that contains the number to be passed, and
;;    then typing M-x and the name of the function, as with C-u 3 M-x
;;    forward-sentence; or,
;; 2. By typing whatever key or keychord the function is bound to, as with C-u 3
;;    M-e.
;;
;; A prefix argument is passed to an interactive function by typing the META key
;; followed by a number.
;;
;; In this function, the expression, (interactive "p"), is a list of two elements.
;; The "p" tells Emacs to pass the prefix argument to the function and use its
;; value for the argument of the function.
;;
;; Emacs has more than twenty characters predefined for use with interactive. In
;; almost every case, one of these options will enable you to pass the right
;; information interactively to a function.
(defun multiply-by-seven (number)       ; Interactive version.
  "Multiply NUMBER by seven."
  (interactive "p")
  (message "The result is %d" (* 7 number)))


;; Binds a and b to the first two actual arguments, which are required. If one
;; or two more arguments are provided, c and d are bound to them respectively;
;; any arguments after the first four are collected into a list and e is bound
;; to that list. If there are only two arguments, c is nil; if two or three
;; arguments, d is nil; if four arguments or fewer, e is nil.
;; There is no way to have required arguments following optional ones — it would
;; not make sense.
(a b &optional c d &rest e)


;; Dynamic scoping in elisp.
(defun foo ()
  (let ((x 6)) ; define a local (i.e., stack) variable x initialized to 6
    (bar)      ; call bar
    x))        ; return x

(defun bar ()
  (setq x 7)) ; finds and modifies x in the caller's stack frame, e.g. x in foo

(foo)
