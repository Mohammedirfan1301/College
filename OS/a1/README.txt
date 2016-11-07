Assignment 1 - Using System Calls
============================================

 Name: Jason Downing
 Date: 9/14/2016
Email: jason_downing@student.uml.edu

I believe I was 90% successful in completing this program. I followed the
outline that Prof. Moloney provided in the assignment doc and went through
the assign1.c file as well as the assign1_help.pdf file. I am able to create
a pipe, and then fork the program into a child process and parent process. I output
the required credentials during the parent and child processes.

I have the child process setup a sig handler, and then signal to the parent process
that it is entering an endless loop. The parent process waits on the read
command - as soon as the child writes, the parent will pick this up and then
send a SIGTERM (#15) to the child, causing it to die. This will in term trigger
the child's sig handler, which I created at the top of my a1.c file. This function
will call execl to run Prof. Moloney's program. I took Moloney's program and
compiled it myself - I left it in the submission directory and it is named
"assign1". My program is named "a1" as required.

Once Prof. Moloney's program is called, it outputs some information about itself and
then waits for the user to kill it. I then killed the Professor's program by issuing
a kill command from another terminal. This in turn causes the professor's program to
die and the rest of my program begins to run. At this point I print out whether
the child terminated with an exit or signal code, and whether it created a core
dump or not. I then return 0 to end my program.

Overall I think I was quite successful and my program runs fine without any major
issues. The output appears to match what Prof. Moloney has required.

I have a Makefile, two C files (assign.c is Prof. Moloney's code, a1.c is my code),
two executables (my program is a1, and Prof. Moloney's program is assign1), and
this README file as required by Prof. Moloney.
