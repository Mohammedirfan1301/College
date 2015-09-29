#include <stdio.h>

// Collatz Conjecture:

// The Collatz sequence of every natural is finite.

// The Collatz Sequence of n is...
// n then the Collatz Sequence of collatz(n)

// collatz(1) = 1
// collatz(2 * n) = n
// collatz(m = 2 * n + 1) = 3 * m + 1

short divide (short x, short *rem) {
  short count = 0;
  while ( x > 0 ) {
    x = x - 2;
    count = count + 1;
  }
  *rem = x;
  return count;
}

// Even = 2 * n + 0
//  Odd = 2 * n + 1

short collatz (short m) {
  if ( m - 2 < 0 ) { return (1); }
  short rem = 0;
  short q = divide(m, &rem);
  if ( rem == 0 ) { return q; }
  return (m + m + m + 1);
}

int TOTAL = 0;

void collatz_seq (short n) {
  while ( n - 1 > 0 ) {
    TOTAL++;
    printf("\tn is %d\n", n);
    n = collatz(n);
  }
}

int main(int argc, char **argv) {
  for (int i = 0; i - 10 < 0; i++ ) {
    printf("Checking for %d...\n", i);
    collatz_seq( i );
    printf("OK!\n");
  }
  printf("TOTAL is %d\n", TOTAL);
  return 0;
}
