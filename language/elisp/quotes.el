;; The single apostrophe, ', that I put in front of some of the example lists in
;; preceding sections is called a quote; when it precedes a list, it tells Lisp
;; to do nothing with the list, other than take it as it is written. But if there
;; is no quote preceding a list, the first item of the list is special: it is a
;; command for the computer to obey. E.g.
;; (+ 2 2)  => 4
;; '(+ 2 2) => (+ 2 2)
;; (this is a list)  => Symbol's function definition is void: this
;; '(this is a list) => (this is a list)



;; The same applies to symbols.  The first expression will try to evaluate hello,
;; but hello is not defined.  The second expression bypass evaluation, just
;; return the symbol hello.
;; hello  => Symbol's value as variable is void: hello
;; 'hello => hello (Note: hello here is a symbol, not string)



;; (type-of 'hello) => Symbol
;; (setq hello 3)
;; (message "Value %s" 'hello) => Value hello
;; (message "Value %s" hello)  => Value 3



;; • When you evaluate a symbol by itself, its value is returned.
;; • When you evaluate a list, the Lisp interpreter looks at the first symbol in
;;   the list and then at the function definition bound to that symbol. Then the
;;   instructions in the function definition are carried out.
;; • A single quotation mark, ' , tells the Lisp interpreter that it should
;;   return the following expression as written, and not evaluate it as it would
;;   if the quote were not there.
