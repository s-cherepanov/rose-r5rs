(define (fact n)
  (display n)
  (if (< n 1)
    1
    (* n (fact (- n 1)))))

(fact 10)