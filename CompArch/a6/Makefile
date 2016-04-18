# Standard flags for compiling C programs.
# Using std=c99 for easy for loops and stuff.
CC = gcc
CFLAGS	= -std=c99 -o -Werror -Wextra -Wall

all: linker test_linker

linker: linker.c
	$(CC) $(CFLAGS) linker.c -o linker

test_linker:
	./masm -o < linker_help/main1.asm > main1.obj
	./masm -o < linker_help/myadd.asm > myadd.obj
	./linker main1.obj myadd.obj > test.out
	./mic1 prom_mrd.dat test.out 0 2000

clean:
	rm linker
