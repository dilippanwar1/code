;; The car of a list is, quite simply, the first item in the list. Thus the car
;; of the list (rose violet daisy buttercup) is rose.  car does not remove the
;; first item from the list; it only reports what it is.  In short, car returns
;; the symbol rose.
(car '(rose violet daisy buttercup))

(car '((lion tiger cheetah)
       (gazelle antelope zebra)
       (whale dolphin seal)))


;; The cdr of a list is the rest of the list, that is, the cdr function returns
;; the part of the list that follows the first item. Thus, while the car of the
;; list '(rose violet daisy buttercup) is rose, the rest of the list, the value
;; returned by the cdr function, is (violet daisy buttercup).
(cdr '(rose violet daisy buttercup))

(cdr '((lion tiger cheetah)
       (gazelle antelope zebra)
       (whale dolphin seal)))


;; The cons function constructs lists; it is the inverse of car and cdr. For
;; example, cons can be used to make a four element list from the three element
;; list, (fir oak maple):
;;   (cons 'pine '(fir oak maple))
;;
;; After evaluating this list, you will see (pine fir oak maple) appear in the
;; echo area. cons causes the creation of a new list in which the element is
;; followed by the elements of the original list.
;;
;; We often say that "cons puts a new element at the beginning of a list; it
;; attaches or pushes elements onto the list", but this phrasing can be misleading,
;; since cons does not change an existing list, but creates a new one. Like car
;; and cdr, cons is non-destructive.
(cons 'pine '(fir oak maple))
(cons '(pine pipi) '(fir oak maple))    ; ((pine pipi) fir oak maple)


;; You can find out how many elements there are in a list by using the Lisp
;; function length.
(length '(buttercup))
(length '(daisy buttercup))


;; The nthcdr function does the same as repeating the call to cdr. In the
;; following example, the argument 2 is passed to the function nthcdr, along
;; with the list, and the value returned is the list without its first two
;; items, which is exactly the same as repeating cdr twice on the list:
(nthcdr 2 '(pine fir oak maple))


;; The nthcdr function takes the cdr of a list repeatedly. The nth function
;; takes the car of the result returned by nthcdr. It returns the Nth element
;; of the list. It is worth mentioning that nth, like nthcdr and cdr, does not
;; change the original list—the function is non-destructive. This is in sharp
;; contrast to the setcar and setcdr functions.
(nth 1 '("one" "two" "three"))


(setq animals '(antelope giraffe lion tiger))
(setq domesticated-animals '(horse cow sheep goat))
;; animals => (hippopotamus giraffe lion tiger)
(setcar animals 'hippopotamus)
;; domesticated-animals => (horse cat dog)
(setcdr domesticated-animals '(cat dog))
animals
domesticated-animals



