        ;Main function to calculate fibonacci numbers 3, 9, 18, 23 & 25.
main:   lodd count:     ; Get count.
        jneg done:      ; See if we are done yet.
        subd one:       ; remove 1 to keep counting to -1.
        stod count:     ; update count.
        lodd test:      ; Get the first fib number to test.
        pshi            ; push it onto the stack.
        addd one:       ; add 1 to the addr.
        stod test:      ; this will push us into the next spot in the array.
        lodd zero:      ; Load 0 into AC
        stod fn:        ; Make fn (current fib number)  start at 0.
        stod fn1:       ; Make fn-1 start at 0. (seed value 0)
        lodd one:       ; Load one into AC
        stod fn2:       ; Make fn-2 start at 1. (seed value 1)
        call fibn:      ; Calculate fib number.

        ;Function to calculate the fibonacci number for N, where N is fibnum.
fibn:   lodl 1          ; Load Fibonacci number to calculate.
        jzer nextn:     ; When fibnum equals 0 we can load up the next number.
        lodd fn1:       ; Add fn1 to AC
        addd fn2:       ; Add fn2 to AC
        stod fn:        ; Store fibonacci number (fn = fn-1 + fn-2)
        lodd fn1:       ; Load fn-1
        stod fn2:       ; Store fn-1 at fn-2 (fn-2 = fn-1)
        lodd fn:        ; Load fib number
        stod fn1:       ; Store Fib number at fn-1 (fn-1 = fn)
        lodl 1          ; Load the fibnum counter
        subd one:       ; Subtract 1 from AC (which is fibnum)
        push            ; update stack.
        call fibn:      ; CALL don't jump so we don't mess up the stack.

        ;This function decrements the count and pushes the fibonacci number onto the stack.
nextn:  lodd fn:       ; Load the Fibonacci number into AC
        push           ; Push fib # onto stack.
        lodd store:    ; Get store addr
        popi           ; Store Fib # in fibnums, starting at location 105.
        addd one:      ; increment store addr
        stod store:    ; update store addr
        jump main:     ; Return to main to keep looping.

done:   halt           ; We are done, so halt and don't catch fire.

        ;Variables start here
count:    5            ; Location for running count, counts down to 0.
fibnum:   0            ; Fib # to calculate.
test: testnums:        ; ptr to the input array
store: fibnums:        ; ptr to the fibonacci array
fn:       0            ; This is Fn in the formula: Fn = Fn-1 + Fn-2
fn1:      0            ; This is basically Fn-1 in the fibonacci formula
fn2:      1            ; This is basically Fn-2 in the fibonacci formula
zero:     0            ; Constant 0 - never changed, used for init. fn/fn1 vars.
one:      1            ; Constant 1 - never changed, used for init. fn2 and decr/incr

.LOC 200
testnums:  3           ; These are the test inputs to the Fibonacci function.
           9           ; Should appear at location 100 in memory.
          18
          23
          25
fibnums:   0           ; This is the location of final fib numbers.
           0           ; eg, for 3 the first spot should contain "2"
           0
           0
           0
