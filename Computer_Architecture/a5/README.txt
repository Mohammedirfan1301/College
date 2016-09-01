 Name: Jason Downing
Email: jason_downing@student.uml.edu
 Date: 3/29/2016

I believe I was 95% successful. My program works as expected for the five inputs,
and seems to correctly detect overflow. I am able to add two numbers, output them
to the screen and correctly add them and output the sum. However, I do not seem
to be able to continue adding numbers after the first run, as I randomly get
OVERFLOW errors when trying to do that. The program works fine though if you run
the provided Makefile and hit "q" to quit and then rerun the program again to add
more numbers.

To run my assignment 5, type "make". I included a Makefile with the following
commands:

./masm < a5.asm > a5.obj
./mic1 prom_mrd.dat a5.obj 0 1024

The first command just compiles the object file, and the second command runs
the mic1 emulator with Prof. Moloney's updated dat file and my object file.
If all you want to do is run my program then only the second command is needed.
