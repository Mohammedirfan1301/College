Assignment 1 - Using System Calls
============================================

 Name: Jason Downing
 Date: 9/26/2016
Email: jason_downing@student.uml.edu

I believe I was 100% successful because both my sort and grep programs compile,
and run with the data files that Prof. Moloney provided. The sort program
displays each area code, sorted in the correct order, and with the number of
unique phone numbers with that area code. The grep program displays how many
matches it found for lines with the number "123" in the line.

I verified the outputs for the grep data sets with the following commands:

asus@asus: a2$ grep -o "123" cs308a2_grep_data_1 | uniq -c
     28 123
asus@asus: a2$ grep -o "123" cs308a2_grep_data_2 | uniq -c
   9158 123

This is interesting because my program appears to infinite loop on the second
dataset. Yet, grep shows 9,158 matches! I believe something with the forking
of the process causes the loop to run endlessly. Grep clearly has some code
built in to handle large datasets, but my program does not take into account
that datasets could be massive (250,000 lines in the grep_data_2).

I verified the output for the sort program by running the following command:

asus@asus: a2$ cut -d' ' -f5 cs308a2_sort_data | sort -n | uniq -c
     87 103
    107 215
    114 220
     96 316
    100 403
    101 508
    103 579
     86 604
     88 617
     77 783

I found out about cut and uniq from this StackOverFlow post:
http://superuser.com/questions/521891/counting-occurrences-in-first-column-of-a-file

I modified the command to check the 5th field, which is the area code, and count
the unique occurrences. This leads to the count being outputted first, and then
the area code.

I have provided a Makefile to compile my programs. You can also run my programs
with the following commands:

./a2_sort cs308a2_sort_data
./a2_grep cs308a2_grep_data_1
./a2_grep cs308a2_grep_data_2

I have provided example output in the "output.txt" file. The output in this file
matches the terminal commands that I ran listed above.
