Assignment 1 - Floating Point Representation
============================================

 Name: Jason Downing
 Date: 1/27/2016
Email: jason_downing@student.uml.edu

I believe I was successful in completing this assignment. I verified my output
looks reasonable against an online IEEE 754 converter - see this URL:
(http://www.h-schmidt.net/FloatConverter/IEEE754.html).
As a result, I believe I was 95% successful. The only thing I am uncertain of
is whether my output lines up as shown on Prof. Moloney's site, but I believe
I matched it reasonably.

The approach I took was to take Prof. Moloney's sample code and extend it by
adding three functions. The three functions were print_output(), which is called
every time the user enters a floating point number on the keyboard, along with two
other functions which handled outputting the mantissa and the exponent. Those two
functions were simple for loops as I was able to pass in the bit_string variable
to them. For the exponent, I just outputted the first 8 bits, along with the spaces
that are stored in the bit_string variable. I did a similar thing for the mantissa,
although I outputted 23 bits for the mantissa instead.

Prof. Moloney's code was found at this URL:
http://www.cs.uml.edu/~bill/cs305/convert_float_to_bits_c.txt
