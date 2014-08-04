;; To set the value of the symbol flowers to the list '(rose violet daisy
;; buttercup), evaluate the following expression
;;   (set 'flowers '(rose violet daisy buttercup))
;;
;; The list (rose violet daisy buttercup) will appear in the echo area. This is
;; what is returned by the set function. As a side effect, the symbol flowers
;; is bound to the list; that is, the symbol flowers, which can be viewed as a
;; variable, is given the list as its value. After evaluating the set expression,
;; you can evaluate the symbol flowers and it will return the value you just set.
;; Incidentally, if you evaluate ’flowers, the variable with a quote in front of
;; it, what you will see in the echo area is the symbol itself, flowers.
;;
;; Note also, that when you use set, you need to quote both arguments to set,
;; unless you want them evaluated.



;; Although I have been using the term 'assign', there is another way of thinking
;; about the workings of set and setq; and that is to say that set and setq make
;; the symbol point to the list.



;; Note that this line uses setq-default rather than the setq command that we
;; have seen before. The setq-default command sets values only in buffers that
;; do not have their own local values for the variable.

