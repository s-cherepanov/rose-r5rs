(define (abs n)
  (if (< n 0)
      (- n)
      n))

(define (average a b)
  (/ (+ a b) 2))

(define (sqrt x)
  (define (good-enough? guess)
    (< (abs (- (* guess guess) x)) 2))
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-iter guess)
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))
  (sqrt-iter 1))

(display-line (sqrt 1000))
