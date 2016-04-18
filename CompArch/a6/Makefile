# Standard flags for compiling C programs.
# Using std=c99 for easy for loops and stuff.
CC = gcc
CFLAGS	= -std=c99 -o -Werror -Wextra -Wall

all: linker

linker: linker.c
	$(CC) $(CFLAGS) linker.c -o linker

clean:
	rm linker
