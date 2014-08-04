;; message, concat, substring
(message "He saw %d %s"
         (- fill-column 32)
         (concat "red "
                 (substring
                  "The quick brown foxes jumped." 16 21)
                 " leaping."))


;; To create a ‘TAGS’ file in a specific directory, switch to that directory
;; in Emacs using M-x cd command, or list the directory with C-x d (dired).
;; Then run the compile command, with etags *.el as the command to execute:
;; M-x compile RET etags *.el RET



(append-to-buffer "*scratch*" 1 20)
(list 1 2 3 4)
