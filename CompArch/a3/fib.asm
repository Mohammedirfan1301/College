        ;Main function to calculate fibonacci numbers 3, 9, 18, 23 & 25.
main:   lodd count:     ; Get count.
        jneg done:      ; See if we are done yet.
        subd one:       ; remove 1 to keep counting to -1.
        stod count:     ; update count.
        lodd test:      ; Get the first fib number to test.
        pshi            ; push it to the stack.
        stod fibnum:    ; save it to the fibnum var.
        addd one:       ; add 1 to the ptr.
        stod test:      ; this will push us to the next spot in the array.
        call fibn:      ; go to Fibn.

        ;Function to calculate the fibonacci number for N, where N is fibnum.
fibn:   lodd fibnum:   ; Load Fibonacci number to calculate.
        jzer nextn:    ; When fibnum equals 0 we can load up the next number.
        lodd fn1:      ; Add fn1 to AC
        addd fn2:      ; Add fn2 to AC
        stod fn:       ; Store fibonacci number   (fn = fn-1 + fn-2)
        lodd fn1:      ; Load fn-1
        stod fn2:      ; Store fn-1 at fn-2 (fn-2 = fn-1)
        lodd fn:       ; Load fib number
        stod fn1:      ; Store Fib number at fn-1 (fn-1 = fn)
        lodd fibnum:   ; Load the fibnum counter
        subd one:      ; Subtract 1 from AC (which is fibnum)
        stod fibnum:   ; Store AC (fibnum) into var fibnum.
        jump fibn:     ; Jump to top of fibonacci loop (keep jumping til fibnum == 0)

        ;This function decrements the count and pushes the fibonacci number onto the stack.
nextn:  lodd fn:       ; Load the Fibonacci number into AC
        push           ; Push onto stack. This should start at mem location 1023.
        jump main:     ; Return to main to keep looping.

        ;We are done at this point.
done:   halt           ; We are done, so halt and don't catch fire.

        ;Variables start here
count:    5            ; Location for running count, counts down to 0.
fibnum:   0            ; The Fibonacci number we want to calculate. (decrements down to 0)

.LOC 200
testnums:  3           ; These are the test inputs to the Fibonacci function.
           9           ; Should appear at location 200.
          18
          23
          25
fibnums:   0           ; This is the location of final fib numbers.
           0           ; eg, for 3 the first spot should contain "2"
           0
           0
           0
test: testnums:        ; ptr to the input array
store: fibnums:        ; ptr to the fibonacci array
fn:       0            ; This is Fn in the formula: Fn = Fn-1 + Fn-2
fn1:      0            ; This is basically Fn-1 in the fibonacci formula
fn2:      1            ; This is basically Fn-2 in the fibonacci formula
zero:     0            ; Constant 0 - never changed, used for init. fn/fn1 vars.
one:      1            ; Constant 1 - never changed, used for init. fn2 and decr/incr
