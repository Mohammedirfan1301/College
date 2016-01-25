/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*
    Union to use for the conversion.
    This post pointed me in the right direction:
    https://stackoverflow.com/questions/
    15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number

    Also, the "convert_float_to_bits.c" file gave me some ideas as well:
    https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/convert_float_to_bits.c
*/
typedef union float_32 {
    float float_value;
    struct {
        unsigned int mantissa: 23;
        unsigned int exponent:  8;
        unsigned int     sign:  1;
    } part;
    struct single_bits {
      unsigned  b0 :1;             // Mantissa
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
      unsigned  b23:1;              // Exponent
      unsigned  b24:1;
      unsigned  b25:1;
      unsigned  b26:1;
      unsigned  b27:1;
      unsigned  b28:1;
      unsigned  b29:1;
      unsigned  b30:1;
      unsigned  b31:1;              // Sign
    } bit;
} float_32;

void print_output(float output, int num);
void output_binary(int integer_input, int bits);
float add_floating_point(float_32 first_int, float_32 second_int);

int main() {
    float float1, float2, hardware, emulated;
    float_32 float_1, float_2;
    int valid = 1;

    do {
        valid = scanf("%f", &float1);

        // scanf will return 0 if it gets invalid input and -1 on EOF.
        if (valid == 0 || valid == -1) {
            break;
        }

        print_output(float1, 1);

        valid = scanf("%f", &float2);

        if (valid == 0 || valid == -1) {
            break;
        }

        print_output(float2, 2);

        hardware = float1 + float2;
        print_output(hardware, 3);

        float_1.float_value = float1;
        float_2.float_value = float2;

        emulated = add_floating_point(float_1, float_2);
        print_output(emulated, 4);

    } while (valid == 1);     // scanf will return 1 if it gets a valid input

    return 0;
}

// Function to output floating point values as binary output
void print_output(float output, int num) {
    // Use the union to print out the mantissa / exponent / sign.
    float_32 output_float;
    output_float.float_value = output;

    // Float 1 / Float 2 output
    if(num == 1 || num == 2) {
        printf(" Float %d: %.6f\n", num, output);
        printf("          bits: ");

        printf("%x ", output_float.part.sign);
        output_binary(output_float.part.exponent, 8);
        output_binary(output_float.part.mantissa, 23);
        printf("\n");
    }
    // Hardware output section
    else if(num == 3) {
        printf("Hardware: %.6f\n", output);
        printf("          bits: ");

        printf("%x ", output_float.part.sign);
        output_binary(output_float.part.exponent, 8);
        output_binary(output_float.part.mantissa, 23);
        printf("\n");
    }
    // Emulated output section
    else if(num == 4) {
        printf("Emulated: %.6f\n", output);
        printf("          bits: ");

        printf("%x ", output_float.part.sign);
        output_binary(output_float.part.exponent, 8);
        output_binary(output_float.part.mantissa, 23);
        printf("\n\n");
    }
}

// This function prints out a binary number given an integer.
void output_binary(int integer_input, int bits) {
    int bit_array[32];
    int x, y, count = 1;

    // Initalize everything to zero.
    for (x = 0; x < 32; x++) {
        bit_array[x] = 0;
    }

    // Convert to binary
    for (x = 0; integer_input > 0; x++) {
        bit_array[x] = integer_input % 2;      // Get the reminder into bit_array
        integer_input = integer_input / 2;     // Divide by 2 until divide equals zero.
    }

    // Exponent stuff
    if (bits == 8) {
        for (y = 7; y >= 0; y--) {
            printf("%d", bit_array[y]);

            if(count == 4) {             // Catch groups of 4 by counting to 4.
                printf(" ");
                count = 0;              // Equal to 0 since count
            }                           // will be incremented right after.

            count++;
        }
    }

    // Mantissa stuff
    if (bits == 23) {
        count = 2;                      // fix the first group of 4 being wrong.

        for (y = 22; y >= 0; y--) {
            if(y > 19) {                // Output the group of 3
                printf("%d", bit_array[y]);
            }
            else if (y == 19) {         // Separate the group of 3 by a space.
                printf(" %d", bit_array[y]);
            }
            else {              // This part is either the rest of the mantissa.
                printf("%d", bit_array[y]);

                // Prevent trailing whitespace by catching when y == 0
                // This messed up my diff command.
                if( (count == 4) &&  (y != 0) ) {
                    printf(" ");        // Catch groups of 4 by counting to 4.
                    count = 0;
                }

                count++;
            }
        }
    }
}

// Function to add two floating point numbers using integer addition.
float add_floating_point(float_32 first_int, float_32 second_int) {
    int counter = 0;          // Shift counter
    float_32 float_sum;

    // The exponents are the same, so increment them,
    // and then add the mantissa's together.
    if (first_int.part.exponent == second_int.part.exponent) {

        // Increment the exponents to fix exponent
        first_int.part.exponent++;
        second_int.part.exponent++;

        // Just use the first exponent.
        float_sum.part.exponent = first_int.part.exponent;

        // Add the two mantissas together.
        float_sum.part.mantissa = first_int.part.mantissa + second_int.part.mantissa;
        float_sum.part.mantissa >>= 1;    // Right shift once to fix 1.0 + 1.2
    }

    // Adjust the 1st mantissa since it is smaller. The 2nd exponent will be used.
    else if (first_int.part.exponent < second_int.part.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = second_int.part.exponent - first_int.part.exponent;

        // Right shift once, then put the hidden bit in that spot.
        first_int.part.mantissa  >>= 1;       // Short hand for val = val >> 1

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
            first_int.part.mantissa  >>= counter - 1;

            // Catch rounding errors - don't drop the last 1. Add it back in.
            if (first_int.bit.b0 == 1) {
                first_int.part.mantissa >>= 1;
                first_int.part.mantissa += 1;     // Add the dropped 1 back in.
            }
            // If the last bit is a 0 though who cares, just shift it once.
            else {
                first_int.part.mantissa  >>= 1;
            }
        }

        // Second exponent was larger so use this one.
        float_sum.part.exponent = second_int.part.exponent;

        float_sum.part.mantissa = first_int.part.mantissa + second_int.part.mantissa;
    }

    // Adjust the 2nd mantissa since it is smaller. The 1st exponent will be used.
    else if (first_int.part.exponent > second_int.part.exponent) {

        // Get the amount to shift by. Only shift to the right.
        counter = first_int.part.exponent - second_int.part.exponent;

        // Right shift once, then put the hidden bit in that spot.
        second_int.part.mantissa  >>= 1;       // Short hand for val = val >> 1

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
            second_int.part.mantissa  >>= counter - 1;

            // Catch rounding errors - don't drop the last bit if it equals 1.
            if (second_int.bit.b0 == 1) {
                second_int.part.mantissa >>= 1;
                second_int.part.mantissa += 1;     // Add the dropped 1 back in.
            }
            // If the last bit is a 0 though who cares, just shift it once.
            else {
                second_int.part.mantissa >>= 1;
            }
        }

        // first exponent was larger so use this one.
        float_sum.part.exponent = first_int.part.exponent;

        float_sum.part.mantissa = first_int.part.mantissa + second_int.part.mantissa;
    }

    // Detect infinity
    if (first_int.part.exponent == 254 || second_int.part.exponent == 254) {
        float_sum.part.exponent = 255;
        float_sum.part.mantissa = 0;
    }

    return float_sum.float_value;
}
