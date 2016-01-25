Assignment 1 - Floating Point Representation
===========================

Assignment 1 for Computer Architecture.

This programs reads any number of floating point numbers from standard input, and outputs the following information:

* mantissa
* exponent
* sign
* base 10 equivalent

Approach
========
I used a union to get the mantissa, exponent and sign, as I included a struct with several unsigned integers inside of the union.
This works as the union stores things in the same memory space, so getting the mantissa / exponent / sign were relatively
easy with this approach. The tricky part was getting the output looking correct and converting the mantissa / exponent to
binary. Since C doesn't have a standard int / float to binary function I created two functions to handle the output and binary
conversion.

void print_output(float output);
------------------------------------------

This function made it easier to output the mantissa / exponent / sign / base 10 equivalent. It also contains the alignment
code which makes all the values line up nicely, either left aligned or right aligned depending on the column.

void output_binary(int integer_input, int bits);
--------------------------------------------------

I made an int to binary conversion function since C doesn't have one built in. A stackoverflow post gave me
the idea for the function, since [itoa](http://www.cplusplus.com/reference/cstdlib/itoa/) isn't valid ANSI-C. Although I ended up
just doing a standard binary conversion: divide by 2 and check the remainder until you hit 0. I also added the "int bits" part
in order to print out the mantissa and the exponent correctly. It is a bit of a hack but it works and I couldn't figure out how
to just figure out whether its the mantissa or the exponent in the function without passing an extra int showing how many
bits to print out.

The main issue I ran into was that leading zeros would not print out and if the number had all 1's it also
would randomly break the output. However, I was able to fix this by passing in the extra integer "bits" as I noted above.

Testing
-----------------
The makefile I created tests against test.out. It runs a diff command against standard_output.out, which will show any
differences between them. I used the following two calculators to generate my test.out:

[Main calculator used](http://www.h-schmidt.net/FloatConverter/IEEE754.html)

[This one was a good alternate to check against](http://babbage.cs.qc.edu/courses/cs341/IEEE-754.html)

# NOTE
For some reason my program outputs the last test twice, so to get the diff command to not complain I entered it twice
in the test.out. I believe this is because of something to do with determining the end of file / last valid input.

You can also manually test by running the following command:
```
./a1 < test.in
```

To get the program's output into a file, run this command:
```
./a1 < test.in > standard_output.out
```

# Makefile link
The following was a useful link on Makefiles and was helpful for figuring out how to use the diff command.

[Creating makefiles and using diff to test output](http://www.cs.toronto.edu/~penny/teaching/csc444-05f/maketutorial.html)


Final Thoughts
=========
Overall I think I accomplished the main goal of the assignment, which was to output the various parts of a floating point
number, including the mantissa / exponent / sign and such. I ran into some issues along the way which I noted above. I feel
like there are still a few bugs with the program that should be worked out, and as a result as is this program is likely
somewhere in the B range.