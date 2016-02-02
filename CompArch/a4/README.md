3.5 MIC-1 Microcode Extension
==============================
For this assignment we created three new microcode instructions for the MIC-1.

I first started off by running the rshift code from Prof. Moloney's a4 help directory,
and started modifying the masm assembler code. I added new cases in the .c file,
and new cases in the flex file as well. I also added new definitions for the cases
in the header file. At this point I began to write the multiplication code and that
took several hours to get working. I also started working on the division code as well.
Division currently does not work for all cases. I believe it works for the 0 case
and probably for dividing two positive numbers. I don't have anything that deals
with negative numbers whether its both negative or just negative divisor / dividend.

The rshift I used came from Prof. Moloney's help directory:
http://www.cs.uml.edu/~bill/cs305/assignment_4_help_dir/promfile_nand_rshift.txt

I also used the help directory in general to figure out how to modify the assembler:
http://www.cs.uml.edu/~bill/cs305/assignment_4_help_dir/

Prof. Moloney talked about this file in his Oct. 1st, 2015 lecture.
https://echoess.uml.edu:8443/ess/echo/presentation/58a0fe58-d2fc-4109-801f-09641f21de43?ec=true

Multiplication was difficult to figure out. Division was even more difficult,
with many cases to account for compared to multiplication. I did not finish division
and I ran out of time figuring out all the cases.

I learned a lot about the MIC-1's underlying architecture with this assignment.
I understand more about the registers, how to read / write to the stack, etc.
I also was able to figure out how to do basic multiplication and division using
just addition and subtraction.

Considering all this, I believe I deserve a .7 considering I got 2/3 instructions
running and working, and I invested hours of time into this assignment. I was also
able to modify the assembler, and I made input files that test the instructions.
