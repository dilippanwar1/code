;; A list is kept using a series of pairs of pointers. In the series, the first
;; pointer in each pair points to an atom or to another list, and the second
;; pointer in each pair points to the next pair, or to the symbol nil, which
;; marks the end of the list. A pointer itself is quite simply the electronic
;; address of what is pointed to. Hence, a list is kept as a series of electronic
;; addresses.


;; When a variable is set to a list with a function such as setq, it stores the
;; address of the first box in the variable.
;;
;;   (setq bouquet '(rose violet buttercup))
;;
;; Symbols consist of more than pairs of addresses, but the structure of a symbol
;; is made up of addresses. Indeed, the symbol bouquet consists of a group of
;; address-boxes, one of which is the address of the printed word ‘bouquet’, a
;; second of which is the address of a function definition attached to the symbol,
;; if any, a third of which is the address of the first pair of address-boxes for
;; the list (rose violet buttercup), and so on.
;;
;; A pair of address-boxes is called a cons cell or dotted pair.


;; Baisc set, cdr, cons.
(setq bouquet '(rose violet buttercup))
(setq flowers (cdr bouquet))
bouquet
flowers
(setq bouquet (cons 'lily bouquet))
bouquet
flowers

;; List equal.
(eq (cdr (cdr bouquet)) flowers)

;; Reverse (nreverse) list.
(setq bouquet '(rose violet buttercup))
(reverse bouquet)
bouquet
(nreverse bouquet)
bouquet

;; Add to to list.
(append '(1 2 3) '(4 5 6) '(7 8 9))     ; (1 2 3 4 5 6 7 8 9)
(add-to-list 'jasmine bouquet)

;; Remove from list.
(setq bouquet '(rose violet buttercup))
;; 'remq' will remove element from list, return a new list (do not modify
;; original list.
(remq 'rose bouquet)
bouquet
