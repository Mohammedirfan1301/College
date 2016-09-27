# Standard flags for compiling C programs.
CC = gcc
FLAGS = -O -Werror -Wall -Wextra -Wundef -Winit-self

all: sort grep

sort:	a2_sort.c
	$(CC) a2_sort.c $(FLAGS) -o a2_sort

grep: a2_grep.c
	$(CC) a2_grep.c $(FLAGS) -o a2_grep

clean:
	# Remove the executable / output file.
	rm a2_sort a2_grep sorted_data
