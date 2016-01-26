/*
 *  Copyright 2016 Jason Downing
 *  All rights reserved.
 *  MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *  Union to use for the conversion.
 *
 *  I used Prof. Moloney's code from this file:
 *  http://www.cs.uml.edu/~bill/cs305/convert_float_to_bits_c.txt
 */
union float_32 {
  float   floating_value_in_32_bits;
  int     floating_value_as_int;
  struct  sign_exp_mantissa {
          unsigned  mantissa: 23;
          unsigned  exponent:  8;
          unsigned      sign:  1;
  } f_bits;
  struct single_bits {
    unsigned  b0 :1;
    unsigned  b1 :1;
    unsigned  b2 :1;
    unsigned  b3 :1;
    unsigned  b4 :1;
    unsigned  b5 :1;
    unsigned  b6 :1;
    unsigned  b7 :1;
    unsigned  b8 :1;
    unsigned  b9 :1;
    unsigned  b10:1;
    unsigned  b11:1;
    unsigned  b12:1;
    unsigned  b13:1;
    unsigned  b14:1;
    unsigned  b15:1;
    unsigned  b16:1;
    unsigned  b17:1;
    unsigned  b18:1;
    unsigned  b19:1;
    unsigned  b20:1;
    unsigned  b21:1;
    unsigned  b22:1;
    unsigned  b23:1;
    unsigned  b24:1;
    unsigned  b25:1;
    unsigned  b26:1;
    unsigned  b27:1;
    unsigned  b28:1;
    unsigned  b29:1;
    unsigned  b30:1;
    unsigned  b31:1;
  } bit;
} float_32;

char bit_string[43];  // Will contain the binary "bit string"

// Function to convert the input into readable output.
void print_output();

// Functions which output the mantissa / exponent in binary.
void print_mantissa();
void print_exponent();

int main() {
  for(int i = 0; i < 42; i++) {
      bit_string[i] = ' ';      // Set bit string to empty.
  }

  bit_string[42] = '\0';

  int valid = 1;

  // Get input until input stops.
  // scanf will return 1 if it gets a valid input, 0 if it gets invalid input and -1 on EOF.
  while (valid == 1) {
      printf("Please enter a floating point number and new-line: ");
      valid = scanf("%g", &float_32.floating_value_in_32_bits);

      // Make sure the user didn't enter invalid input.
      // scanf will return 0 if it gets invalid input and -1 on EOF.
      if (valid == 0 || valid == -1) {
          break;
      }

      // Output values to the screen.
      print_output();
  }

  return 0;
}

// Main output function
void print_output() {

  // This should be the "sign"
  bit_string[0] = float_32.bit.b31?'1':'0';

  // The gaps here will be "spaces", that is #1, #6, #11, #15, #20, #25, #30, #35.

  // The Mantissa should start here.
  bit_string[2] = float_32.bit.b30?'1':'0';
  bit_string[3] = float_32.bit.b29?'1':'0';
  bit_string[4] = float_32.bit.b28?'1':'0';
  bit_string[5] = float_32.bit.b27?'1':'0';

  bit_string[7] = float_32.bit.b26?'1':'0';
  bit_string[8] = float_32.bit.b25?'1':'0';
  bit_string[9] = float_32.bit.b24?'1':'0';
  bit_string[10] = float_32.bit.b23?'1':'0';

  bit_string[12] = float_32.bit.b22?'1':'0';
  bit_string[13] = float_32.bit.b21?'1':'0';
  bit_string[14] = float_32.bit.b20?'1':'0';

  bit_string[16] = float_32.bit.b19?'1':'0';
  bit_string[17] = float_32.bit.b18?'1':'0';
  bit_string[18] = float_32.bit.b17?'1':'0';
  bit_string[19] = float_32.bit.b16?'1':'0';

  bit_string[21] = float_32.bit.b15?'1':'0';
  bit_string[22] = float_32.bit.b14?'1':'0';
  bit_string[23] = float_32.bit.b13?'1':'0';
  bit_string[24] = float_32.bit.b12?'1':'0';

  bit_string[26] = float_32.bit.b11?'1':'0';
  bit_string[27] = float_32.bit.b10?'1':'0';
  bit_string[28] = float_32.bit.b9?'1':'0';
  bit_string[29] = float_32.bit.b8?'1':'0';   // This is the last bit of the Mantissa.

  // The Exponent should start here
  bit_string[31] = float_32.bit.b7?'1':'0';
  bit_string[32] = float_32.bit.b6?'1':'0';
  bit_string[33] = float_32.bit.b5?'1':'0';
  bit_string[34] = float_32.bit.b4?'1':'0';

  bit_string[36] = float_32.bit.b3?'1':'0';
  bit_string[37] = float_32.bit.b2?'1':'0';
  bit_string[38] = float_32.bit.b1?'1':'0';
  bit_string[39] = float_32.bit.b0?'1':'0';

  printf("\nthe floating value for %.1f is broken out as: \n", float_32.floating_value_in_32_bits);

  // Mantissa
  printf("   mantissa: 0x%-8x or: ", float_32.f_bits.mantissa);
  print_mantissa();

  // Exponent
  printf("   exponent: 0x%-8x or: ", float_32.f_bits.exponent);
  print_exponent();

  // Sign / Base 10
  // Note: the blank "" between the sign value is for moving the "or" over without typing
  // out 8 spaces manually.
  printf("       sign: %x %8s or: %x\n", float_32.f_bits.sign, "", float_32.f_bits.sign);
  printf(" in base 10: %1.6f or: %s\n\n", float_32.floating_value_in_32_bits, bit_string);
}


// Print out the Mantissa (23 bits)
void print_mantissa() {
  int a;

  // While it is "23 bits" the bit_string variable includes spaces by default!
  // Makes it trivial to output the Mantissa.
  for(a = 2; a < 30; a++) {
    printf("%c", bit_string[a]);
  }

  printf("\n"); // New line, easier to put it here.
}


// Print out the exponent (8 bits)
void print_exponent() {
  int a;

  // While it is "8 bits" the bit_string variable includes spaces.
  for(a = 31; a < 40; a++) {
    printf("%c", bit_string[a]);
  }

  printf("\n"); // New line, easier to put it here.
}