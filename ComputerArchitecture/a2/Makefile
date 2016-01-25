CC = gcc
CFLAGS = -o -Werror -Wextra -Wall

all:
	# Compile using GCC and the flags listed above.
	$(CC) $(CFLAGS) a2.c -o a2

	# Run the program using the test.in file, and redirect to a file named output
	./a2 < test.in > output

	# Compare the output of my program (output) against the expected output (test.out)
	# Piping (|) through cat with -vet to get whitespace / newlines to show up.
	diff -c output test.out | cat -vet

clean:
	# Remove the executable / standard output file.
	rm a2 output
