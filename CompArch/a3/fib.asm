        ;Main function to calculate fibonacci numbers 0 to 24.
main:   lodd count:    ;Load AC with value at count (counting down to -1 from 24)
        stod fibnum:   ;Store fibonacci number we want to calculate.
        jneg done:     ;If count is less than 0 (-1) then we are done. (only calc 0 to 24)
        lodd zero:     ;Load 0 into AC
        stod fn:       ;Make fn (current fib number)  start at 0.
        stod fn1:      ;Make fn-1 start at 0. (seed value 0)
        lodd one:      ;Load one into AC
        stod fn2:      ;Make fn-2 start at 1. (seed value 1)

        ;Function to calculate the fibonacci number for N, where N is fibnum.
fibn:   lodd fibnum:   ;Load Fibonacci number to calculate.
        jzer nextn:    ;When fibnum equals 0 we can load up the next number.
        lodd fn1:      ;Add fn1 to AC
        addd fn2:      ;Add fn2 to AC
        stod fn:       ;Store fibonacci number   (fn = fn-1 + fn-2)
        lodd fn1:      ;Load fn-1
        stod fn2:      ;Store fn-1 at fn-2 (fn-2 = fn-1)
        lodd fn:       ;Load fib number
        stod fn1:      ;Store Fib number at fn-1 (fn-1 = fn)
        lodd fibnum:   ;Load the fibnum counter
        subd one:      ;Subtract 1 from AC (which is fibnum)
        stod fibnum:   ;Store AC (fibnum) into var fibnum.
        jump fibn:     ;Jump to top of fibonacci loop (keep jumping til fibnum == 0)

        ;This function decrements the count and pushes the fibonacci number onto the stack.
nextn:  lodd count:    ;Load count into AC
        subd one:      ;Subtract 1 from count.
        stod count:    ;Store count
        lodd fn:       ;Load the Fibonacci number into AC
        push           ;Push onto stack. This should start at mem location 1023.
        jump main:     ;Jump back to main, to get the next fibonacci number.

        ;We are done at this point.
done:   halt           ;We are done, so halt and don't catch fire.

        ;Variables start here
count:   24            ;Location for running count, counts down to 0.
fibnum:   0            ;The Fibonacci number we want to calculate. (decrements down to 0)
fn:       0            ;This is Fn in the formula: Fn = Fn-1 + Fn-2
fn1:      0            ;This is basically Fn-1 in the fibonacci formula
fn2:      1            ;This is basically Fn-2 in the fibonacci formula
zero:     0            ;Constant 0 - never changed, used for init. fn/fn1 vars.
one:      1            ;Constant 1 - never changed, used for init. fn2 and decr/incr
