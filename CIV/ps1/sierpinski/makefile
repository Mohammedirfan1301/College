CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic

all:
	$(CC) -c main.cpp sierpinski.cpp $(CFLAGS)
	$(CC) main.o sierpinski.o -o sierpinski -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main.o
	rm sierpinski