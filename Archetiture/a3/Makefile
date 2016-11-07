CC = gcc
CFLAGS = -o -Werror -Wextra -Wall

all:
	./masm < fib.asm > fib.obj
	./mic1 prom.dat fib.obj 0 1024 < test.in > output.txt || true
	$(CC) $(CFLAGS) fib.c -o fib

clean:
	rm fib
