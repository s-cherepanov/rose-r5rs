(define (fact n)
  (display-line n)
  (if (< n 1)
    1
    (* n (fact (- n 1)))))

(define result (fact 10))
(display-line result)
result
