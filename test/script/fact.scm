(define (fact n)
  (display-line n)
  (if (< n 1)
    1
    (* n (fact (- n 1)))))

(display-line (fact 10))
