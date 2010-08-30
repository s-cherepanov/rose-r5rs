(define (length lst)
  (if (pair? lst)
    (+ 1 (length (cdr lst)))
    0))

(length '())
(length '(1))
(length '(1 2))
(length '(1 2 3))
(length '(1 2 3 4))