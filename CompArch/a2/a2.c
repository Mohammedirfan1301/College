/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *  Union to use for the conversion.
 *
 *  This post pointed me in the right direction:
 *  https://stackoverflow.com/questions/
 *  15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number
 *
 *  I used Prof. Moloney's code from this file:
 *  http://www.cs.uml.edu/~bill/cs305/convert_float_to_bits_c.txt
 */
typedef union float_32 {
    float float_value;
    struct {
        unsigned int mantissa: 23;
        unsigned int exponent:  8;
        unsigned int     sign:  1;
    } f_bits;
    struct single_bits {
      // Mantissa, b0 to b22.
      unsigned  b0 :1;      unsigned  b1 :1;
      unsigned  b2 :1;      unsigned  b3 :1;
      unsigned  b4 :1;      unsigned  b5 :1;
      unsigned  b6 :1;      unsigned  b7 :1;
      unsigned  b8 :1;      unsigned  b9 :1;
      unsigned  b10:1;      unsigned  b11:1;
      unsigned  b12:1;      unsigned  b13:1;
      unsigned  b14:1;      unsigned  b15:1;
      unsigned  b16:1;      unsigned  b17:1;
      unsigned  b18:1;      unsigned  b19:1;
      unsigned  b20:1;      unsigned  b21:1;
      unsigned  b22:1;

      // Exponent, b23 to b30.
      unsigned  b23:1;      unsigned  b24:1;
      unsigned  b25:1;      unsigned  b26:1;
      unsigned  b27:1;      unsigned  b28:1;
      unsigned  b29:1;      unsigned  b30:1;

      // Sign, b31.
      unsigned  b31:1;
    } bit;
} float_32;

// Print functions
void print_output(float_32 output, int num);
void print_binary(float_32 output);

// Add two floating point numbers.
float add_floating_point(float_32 first_int, float_32 second_int);

int main() {
    float float1, float2, hardware, emulated;
    float_32 float_1, float_2, hardware_32, emulated_32;
    int valid = 1;

    do {
        printf("Please enter two positive floating point values each with:\n");
        printf("\t- no more than 6 significant digits\n");
        printf("\t- a value between + 10**37 and 10**-37\n");

        printf("Enter Float 1: ");
        valid = scanf("%f", &float1);

        printf("Enter Float 2: ");
        valid = scanf("%f", &float2);

        printf("\n");          // pretty output.

        // Get float values into the unions.
        float_1.float_value = float1;
        float_2.float_value = float2;

        // scanf will return 0 if it gets invalid input and -1 on EOF.
        if (valid == 0 || valid == -1) {
            break;
        }

        // Print output calls
        print_output(float_1, 1);      // Float 1 & 2
        print_output(float_2, 2);

        hardware = float1 + float2;            // Hardware output
        hardware_32.float_value = hardware;    // Add to float_32 container.
        print_output(hardware_32, 3);

        emulated = add_floating_point(float_1, float_2);    // Emulated calculation
        emulated_32.float_value = emulated;     // Add to float_32 container.
        print_output(emulated_32, 4);           // Emulated output

        printf("\n");         // pretty output.

    } while (valid == 1);     // scanf will return 1 if it gets a valid input

    return 0;
}

// Function to output floating point values as binary output
void print_output(float_32 output, int num) {
    if(num == 1 || num == 2) {      // Float 1 / Float 2 output
        printf("Float %d: %.6f\n", num, output.float_value);
    }
    else if(num == 3) {       // Hardware output section
        printf("Hardware: %.6f\n", output.float_value);
    }
    else if(num == 4) {       // Emulated output section
        printf("Emulated: %.6f\n", output.float_value);
    }

    printf("          bits: ");     // Print out the bits.
    print_binary(output);
}

/*
 *  This function prints out a binary number given an integer.
 *  This is basically straight from a1.c, modified to work with a float_32
 *  variable called "output"
 */
void print_binary(float_32 output) {
  char bit_string[43];  // Will contain the binary "bit string"

  for(int i = 0; i < 42; i++) {
      bit_string[i] = ' ';      // Set bit string to empty.
  }

  bit_string[42] = '\0';        // Null terminated C style string.

  // This should be the "sign"
  bit_string[0] = output.bit.b31?'1':'0';

  // The gaps here will be "spaces", that is #1, #6, #11, #15, #20, #25, #30, #35.

  // The Exponent should start here
  bit_string[2] = output.bit.b30?'1':'0';  bit_string[3] = output.bit.b29?'1':'0';
  bit_string[4] = output.bit.b28?'1':'0';  bit_string[5] = output.bit.b27?'1':'0';

  bit_string[7] = output.bit.b26?'1':'0';  bit_string[8] = output.bit.b25?'1':'0';
  bit_string[9] = output.bit.b24?'1':'0';  bit_string[10] = output.bit.b23?'1':'0';
  // Last bit of the exponent. (10)

  // The Mantissa should start here.
  bit_string[12] = output.bit.b22?'1':'0';
  bit_string[13] = output.bit.b21?'1':'0';  bit_string[14] = output.bit.b20?'1':'0';

  bit_string[16] = output.bit.b19?'1':'0';  bit_string[17] = output.bit.b18?'1':'0';
  bit_string[18] = output.bit.b17?'1':'0';  bit_string[19] = output.bit.b16?'1':'0';

  bit_string[21] = output.bit.b15?'1':'0';  bit_string[22] = output.bit.b14?'1':'0';
  bit_string[23] = output.bit.b13?'1':'0';  bit_string[24] = output.bit.b12?'1':'0';

  bit_string[26] = output.bit.b11?'1':'0';  bit_string[27] = output.bit.b10?'1':'0';
  bit_string[28] = output.bit.b9?'1':'0';   bit_string[29] = output.bit.b8?'1':'0';

  bit_string[31] = output.bit.b7?'1':'0';   bit_string[32] = output.bit.b6?'1':'0';
  bit_string[33] = output.bit.b5?'1':'0';   bit_string[34] = output.bit.b4?'1':'0';

  bit_string[36] = output.bit.b3?'1':'0';   bit_string[37] = output.bit.b2?'1':'0';
  bit_string[38] = output.bit.b1?'1':'0';   bit_string[39] = output.bit.b0?'1':'0';
  // This is the last bit of the Mantissa. (39)

  printf("%s\n", bit_string);     // Print out the bit string.
}

// Function to add two floating point numbers using integer addition.
float add_floating_point(float_32 first_int, float_32 second_int) {
    int counter = 0;          // Shift counter
    float_32 float_sum;

    // The exponents are the same, so increment them,
    // and then add the mantissa's together.
    if (first_int.f_bits.exponent == second_int.f_bits.exponent) {

        // Increment the exponents to fix exponent
        first_int.f_bits.exponent++;
        second_int.f_bits.exponent++;

        // Just use the first exponent.
        float_sum.f_bits.exponent = first_int.f_bits.exponent;

        // Add the two mantissas together.
        float_sum.f_bits.mantissa = first_int.f_bits.mantissa + second_int.f_bits.mantissa;
        float_sum.f_bits.mantissa >>= 1;    // Right shift once to fix 1.0 + 1.2
    }

    // Adjust the 1st mantissa since it is smaller. The 2nd exponent will be used.
    else if (first_int.f_bits.exponent < second_int.f_bits.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = second_int.f_bits.exponent - first_int.f_bits.exponent;

        // Right shift once, then put the hidden bit in that spot.
        first_int.f_bits.mantissa  >>= 1;       // Short hand for val = val >> 1

        // Put the hidden bit in place of the zero we just shifted in.
        first_int.bit.b22 = 1;

        // Need to decrement the shift counter now if it isn't equal to zero.
        if (counter > 0) {
            counter--;
        }

        // Don't overshift - max should be 24.
        if (counter > 24) {
            counter = 24;
        }

        // Shift right by the shift amount.
        if (counter > 0) {

            // Shift one less then necessary so we can catch rounding errors.
            first_int.f_bits.mantissa  >>= counter - 1;

            // Catch rounding errors - don't drop the last 1. Add it back in.
            if (first_int.bit.b0 == 1) {
                first_int.f_bits.mantissa >>= 1;
                first_int.f_bits.mantissa += 1;     // Add the dropped 1 back in.
            }
            // If the last bit is a 0 though who cares, just shift it once.
            else {
                first_int.f_bits.mantissa  >>= 1;
            }
        }

        // Second exponent was larger so use this one.
        float_sum.f_bits.exponent = second_int.f_bits.exponent;

        float_sum.f_bits.mantissa = first_int.f_bits.mantissa + second_int.f_bits.mantissa;
    }

    // Adjust the 2nd mantissa since it is smaller. The 1st exponent will be used.
    else if (first_int.f_bits.exponent > second_int.f_bits.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = first_int.f_bits.exponent - second_int.f_bits.exponent;

        // Right shift once, then put the hidden bit in that spot.
        second_int.f_bits.mantissa  >>= 1;       // Short hand for val = val >> 1

        // Put the hidden bit in place of the zero we just shifted in.
        second_int.bit.b22 = 1;

        // Need to decrement the shift counter now if it isn't equal to zero.
        if (counter > 0) {
            counter--;
        }

        // Don't overshift - max should be 24.
        if (counter > 24) {
            counter = 24;
        }

        // Shift right by the shift amount.
        if (counter > 0) {

            // Shift one less than necessary so we can catch rounding errors.
            second_int.f_bits.mantissa  >>= counter - 1;

            // Catch rounding errors - don't drop the last bit if it equals 1.
            if (second_int.bit.b0 == 1) {
                second_int.f_bits.mantissa >>= 1;
                second_int.f_bits.mantissa += 1;     // Add the dropped 1 back in.
            }
            // If the last bit is a 0 though who cares, just shift it once.
            else {
                second_int.f_bits.mantissa >>= 1;
            }
        }

        // first exponent was larger so use this one.
        float_sum.f_bits.exponent = first_int.f_bits.exponent;

        float_sum.f_bits.mantissa = first_int.f_bits.mantissa + second_int.f_bits.mantissa;
    }

    // Detect infinity
    if (first_int.f_bits.exponent == 254 || second_int.f_bits.exponent == 254) {
        float_sum.f_bits.exponent = 255;
        float_sum.f_bits.mantissa = 0;
    }

    return float_sum.float_value;
}
