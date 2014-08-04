;; The command is global-set-key. It is followed by the keybinding. In a
;; ‘.emacs’ file, the keybinding is written as shown: \C-c stands for
;; ‘control-c’, which means ‘press the control key and the C key at the
;; same time’. The w means ‘press the W key’. The keybinding is surrounded
;; by double quotation marks. In documentation, you would write this as
;; C-c w. (If you were binding a META key, such as M-c, rather than a CTRL
;; key, you would write \M-c in your ‘.emacs’ file.



;; Emacs uses keymaps to record which keys call which commands. When you use
;; global-set-key to set the keybinding for a single command in all parts of
;; Emacs, you are specifying the keybinding in current-global-map. Specific
;; modes, such as C mode or Text mode, have their own keymaps; the mode-specific
;; keymaps override the global map that is shared by all buffers.
;;
;; Mode-specific keymaps are bound using the define-key function, which takes
;; a specific keymap as an argument, as well as the key and the command. For
;; example, my ‘.emacs’ file contains the following expression to bind the
;; texinfo-insert-@group command to C-c C-c g:
;; (define-key texinfo-mode-map "\C-c\C-cg" ’texinfo-insert-@group)



;; Nowadays, function keys as well as mouse button events and non-ascii
;; characters are written within square brackets, without quotation marks.
;; I bind line-to-top-of-window to my F6 function key like this:
;; (global-set-key [f6] ’line-to-top-of-window)


