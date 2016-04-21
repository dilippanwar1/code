;; Since Emacs Lisp is large, it is customary to name symbols in a way that
;; identifies the part of Emacs to which the function belongs. Thus, all the
;; names for functions that deal with Texinfo start with 'texinfo-' and those
;; for functions that deal with reading mail start with 'rmail-'.



;; A symbol can have any value attached to it or, to use the jargon, we can
;; bind the variable to a value: to a number, such as 72; to a string,
;; "such as this"; to a list, such as (spruce pine oak); we can even bind a
;; variable to a function definition.



;; When we evaluated 'fill-column' to find its value as a variable, we did not
;; place parentheses around the word. This is because we did not intend to use
;; it as a function name.  If 'fill-column' were the first or only element of
;; a list, the Lisp interpreter would attempt to find the function definition
;; attached to it. But fill-column has no function definition.
;; (fill-column) => Symbol's function definition is void



;; If you attempt to evaluate a symbol that does not have a value bound to it,
;; you will receive an error message.
;; +  => Symbol's value as variable is void



;; When we evaluate the variable animals, we see that it is bound to the list
;; (antelope giraffe lion tiger): animals => (antelope giraffe lion tiger)
;; Put another way, the variable animals points to the list (antelope giraffe
;; lion tiger).



;; In an earlier section, I suggested that you might imagine a symbol as being
;; a chest of drawers. The function definition is put in one drawer, the value
;; in another, and so on. What is put in the drawer holding the value can be
;; changed without affecting the contents of the drawer holding the function
;; definition, and vice-verse. Actually, what is put in each drawer is the
;; address of the value or function definition. It is as if you found an old
;; chest in the attic, and in one of its drawers you found a map giving you
;; directions to where the buried treasure lies. (In addition to its name,
;; symbol definition, and variable value, a symbol has a 'drawer' for a property
;; list which can be used to record other information.)



