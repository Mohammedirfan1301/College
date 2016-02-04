# Standard flags for compiling C programs.
# Using std=c99 for easy for loops and stuff.
CC = gcc
CFLAGS	= -std=c99 -o -Werror -Wextra -Wall

all:
	# Compile using GCC and the flags listed above.
	$(CC) $(CFLAGS) a2.c -o a2

	# Run the program using the test.in file, and redirect to a file named output
	./a2 < test.in > output

clean:
	# Remove the executable / standard output file.
	rm a2 output
