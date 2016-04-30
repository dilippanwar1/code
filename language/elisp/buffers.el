(buffer-name)
(buffer-file-name)
(current-buffer)
(other-buffer)
(switch-to-buffer (other-buffer))

;; In Emacs, the current position of the cursor is called point. The expression
;; (point) returns a number that tells you where the cursor is located as a
;; count of the number of characters from the beginning of the buffer up to point.
(point)

;; The function point-min is somewhat similar to point, but it returns the value
;; of the minimum permissible value of point in the current buffer. This is the
;; number 1 unless narrowing is in effect. Likewise, the function point-max
;; returns the value of the maximum permissible value of point in the current
;; buffer.
(point-min)
(point-max)
(buffer-size)
