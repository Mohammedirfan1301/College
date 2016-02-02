/* Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.    */
#include <stdio.h>

int find_fibonacci(int n) {
    int Fn = 0, Fn1 = 0, Fn2 = 1;

    while (n >= 0) {        // While N is not negative
        Fn = Fn1 + Fn2;
        Fn2 = Fn1;          // Fibonacci formula:
        Fn1 = Fn;           // Fn = Fn-1 + Fn-2
        n--;
    }

    return Fn;              // Fibonacci number for int n
}

int main() {
    int count = 24;         // We count down from 25 to 0, MIC1 supports this.
    int N = 0;              // N is the given Fibonacci number.

    printf("First 25 Fibonacci numbers: \n\n");

    while(count >= 0) {
        printf("Fib #%d = %d\n", N, find_fibonacci(N));
        count--;
        N++;
    }

    return 0;
}
