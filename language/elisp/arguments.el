;; (+ 2 'hello)
;;
;; When you do this you will generate an error message. What has happened is
;; that + has tried to add the 2 to the value returned by 'hello, but the value
;; returned by 'hello is the symbol hello, not a number. Only numbers can be
;; added. So + could not carry out its addition.
;;
;; You will create and enter a '*Backtrace*' buffer that says:
;; ---------- Buffer: *Backtrace* ----------
;; Debugger entered--Lisp error:
;; (wrong-type-argument number-or-marker-p hello)
;; +(2 hello)
;; eval((+ 2 (quote hello)))
;; eval-last-sexp-1(nil)
;; eval-last-sexp(nil)
;; call-interactively(eval-last-sexp)
;; ---------- Buffer: *Backtrace* ----------
;;
;; As usual, the error message tries to be helpful and makes sense after you
;; learn how to read it.
;;
;; The first part of the error message is straightforward; it says 'wrong type
;; argument'. Next comes the mysterious jargon word 'number-or-marker-p'. This
;; word is trying to tell you what kind of argument the + expected.
;;
;; The symbol number-or-marker-p says that the Lisp interpreter is trying to
;; determine whether the information presented it (the value of the argument)
;; is a number or a marker (a special object representing a buffer position).
;; What it does is test to see whether the + is being given numbers to add. It
;; also tests to see whether the argument is something called a marker, which
;; is a specific feature of Emacs Lisp. (In Emacs, locations in a buffer are
;; recorded as markers. When the mark is set with the C-@ or C-SPC command, its
;; position is kept as a marker. The mark can be considered a number - the number
;; of characters the location is from the beginning of the buffer.) In Emacs
;; Lisp, + can be used to add the numeric value of marker positions as numbers.
;;
;; The 'p' of number-or-marker-p is the embodiment of a practice started in the
;; early days of Lisp programming. The 'p' stands for 'predicate'. In the jargon
;; used by the early Lisp researchers, a predicate refers to a function to
;; determine whether some property is true or false. So the 'p' tells us that
;; number-or-marker-p is the name of a function that determines whether it is
;; true or false that the argument supplied is a number or a marker. Other Lisp
;; symbols that end in 'p' include zerop, a function that tests whether its
;; argument has the value of zero, and listp, a function that tests whether its
;; argument is a list.
;;
;; Finally, the last part of the error message is the symbol hello. This is the
;; value of the argument that was passed to +. If the addition had been passed
;; the correct type of object, the value passed would have been a number, such
;; as 37, rather than a symbol like hello. But then you would not have got the
;; error message.
