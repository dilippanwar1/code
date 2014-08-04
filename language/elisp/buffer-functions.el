(defun simplified-beginning-of-buffer ()
  "A simplified version of beginning-of-buffer, move cursor to the
beginning of buffer, but leave mark at previous position."
  (interactive)
  (push-mark)       ; current postion of mark is pushed into mark ring
  (goto-char (point-min)))
