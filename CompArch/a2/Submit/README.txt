********************************************************************************
*   Floating Point Addition
********************************************************************************

 Name: Jason Downing
Email: jason_downing@student.uml.edu
 Date: 2/4/2016

This assignment required us to manually add two floating point numbers using
only integer operations in C such as adding, left shifting, etc.

For my approach I reused parts of assignment 1 so that I could easily print out
the bit strings for the floating point numbers and the hardware / emulated results.
I then created an add_floating_point function to carry out the actual addition of
two floating point numbers in C using integer operations. I created a few test cases,
such as if the exponents are equal or if one is greater then the other, and I also
accounted for infinity.

I believe I was reasonably accurate as the six test inputs that Prof. Moloney asked
us to run were correct - the hardware matched the emulated result. There is the chance
that I did not account for some edge case though so I would put my level of success
at 95%.
