;; In Emacs Lisp programs used for editing, the save-excursion function is very
;; common. It saves the location of point and mark, executes the body of the
;; function, and then restores point and mark to their previous positions if
;; their locations were changed. Its primary purpose is to keep the user from
;; being surprised and disturbed by unexpected movement of point or mark.
;;
;; Point is the current location of the cursor. The mark is another position
;; in the buffer; its value can be set with a command such as C-SPC
;; (set-mark-command). If a mark has been set, you can use the command C-x C-x
;; (exchange-point-and-mark) to cause the cursor to jump to themark and set
;; the mark to be the previous position of point. In addition, if you set
;; another mark, the position of the previous mark is saved in the mark ring.
;; Many mark positions can be saved this way. You can jump the cursor to a
;; saved mark by typing C-u C-SPC one or more times.


(save-excursion
  first-expression-in-body
  second-expression-in-body
  third-expression-in-body
  ...
  last-expression-in-body )
