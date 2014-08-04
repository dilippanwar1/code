;; A '~/.emacs' file contains Emacs Lisp code. You can write this code yourself;
;; or you can use Emacs's customize feature to write the code for you. You can
;; combine your own expressions and auto-written Customize expressions in your
;; '.emacs' file.
;;
;; You can specify variables using defcustom so that you and others can then use
;; Emacs’s customize feature to set their values. (You cannot use customize to
;; write function definitions; but you can write defuns in your '.emacs' file.)
;;
;; The customize feature depends on the defcustom special form. Although you can
;; use defvar or setq for variables that users set, the defcustom special form is
;; designed for the job.
;;
;; The first argument to defcustom is the name of the variable. The second
;; argument is the variable's initial value, if any; and this value is set only
;; if the value has not already been set. The third argument is the documentation.
;; The fourth and subsequent arguments to defcustom specify types and options;
;; these are not featured in defvar. (These arguments are optional.) Each of
;; these arguments consists of a keyword followed by a value. Each keyword starts
;; with the colon character ‘:’.
;;
;; For example, the customizable user option variable text-mode-hook looks like
;; this:
(defcustom text-mode-hook nil
  "Normal hook run when entering Text mode and many related modes."
  :type 'hook
  :options '(turn-on-auto-fill flyspell-mode)
  :group 'wp)
;; The name of the variable is text-mode-hook; it has no default value; and
;; its documentation string tells you what it does.  The :type keyword tells
;; Emacs the kind of data to which text-mode-hook should be set and how to
;; display the value in a Customization buffer.  The :options keyword specifies
;; a suggested list of values for the variable. Usually, :options applies to
;; a hook. The list is only a suggestion; it is not exclusive; a person who sets
;; the variable may set it to other values; the list shown following the :options
;; keyword is intended to offer convenient choices to a user.  Finally, the
;; :group keyword tells the Emacs Customization command in which group the
;; variable is located. This tells where to find it.
;;
;; There are two ways to customize this variable. You can use the customization
;; command or write the appropriate expressions yourself.



;; The custom-set-variables function works somewhat differently than a setq.
;; While I have never learned the differences, I modify the custom-set-variables
;; expressions in my ‘.emacs’ file by hand: I make the changes in what appears
;; to me to be a reasonable manner and have not had any problems. Others prefer
;; to use the Customization command and let Emacs do the work for them. Another
;; custom-set-... function is custom-set-faces. This function sets the  various
;; font faces. Over time, I have set a considerable number of faces. Some of the
;; time, I re-set them using customize; other times, I simply edit the
;; custom-set-faces expression in my ‘.emacs’ file itself.
