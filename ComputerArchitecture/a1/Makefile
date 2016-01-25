CC = gcc
CFLAGS	= -o -Werror -Wextra -Wall

all:
	# Compile the program.
	$(CC) $(CFLAGS) a1.c -o a1

	# Run the program using the test.in file, and redirect to a file named standard_output.out
	./a1 < test.in > standard_output.out

clean:
	# Remove the executable / standard output file.
	rm a1 standard_output.out
