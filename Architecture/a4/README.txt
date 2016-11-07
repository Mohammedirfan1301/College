********************************************************************************
*    Microcode Extension                                                       *
********************************************************************************

 Name: Jason Downing
Email: jason_downing@student.uml.edu
 Date: 3/9/2016

For this assignment we created three new microcode instructions for the MIC-1.

I first started off by running the rshift code from Prof. Moloney's a4
help directory, and started modifying the masm assembler code. I added new
cases in the .c file, and new cases in the flex file as well. I also added
new definitions for the cases in the header file. At this point I began to
write the multiplication code and that took several hours to get working.
I also started working on the division code as well. Division does not work at all,
although I'm not sure why because I think I had the right idea. It just endlessly
runs when I run the div example code. Rshift and Mult work fine though from what
I can tell by running the example files.

I believe I was 75% successful since was able to edit the .c files and
I got rshift and mult to work, but I couldn't quite get div working.

The output for compiling and running rshift and mult can be found in the
output.txt file. All of the masm code is in the masm subdirectory, and my microcode
can be found in the "rmd.mc" file.
