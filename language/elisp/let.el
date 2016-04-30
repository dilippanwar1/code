;; A template for a let expression looks like this:
;;   (let varlist body ...)
;;
;; The symbols in the varlist are the variables that are given initial values
;; by the let special form. Symbols by themselves are given the initial value
;; of nil; and each symbol that is the first element of a two-element list is
;; bound to the value that is returned when the Lisp interpreter evaluates the
;; second element. Thus, a varlist might look like this: (thread (needles 3)).
;; In this case, in a let expression, Emacs binds the symbol thread to an
;; initial value of nil, and binds the symbol needles to an initial value of 3.


;; In the varlist, Emacs binds the variable zebra to the value stripes, and
;; binds the variable tiger to the value fierce. In this example, both values
;; are symbols preceded by a quote. The values could just as well have been
;; another list or a string.
(let ((zebra 'stripes)
      (tiger 'fierce))
  (message "One kind of animal has %s and another is %s."
           zebra tiger))


;; Default varlist value is nil.
(let ((birch 3)
      pine
      fir
      (oak 'some))
  (message
   "Here are %d variables with %s, %s, and %s value."
   birch pine fir oak))
