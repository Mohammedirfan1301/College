CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
LFLAGS= -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) -c main.cpp sierpinski.cpp $(CFLAGS)
	$(CC) main.o sierpinski.o -o sierpinski $(LFLAGS)

clean:
	rm main.o
	rm sierpinski.o
	rm sierpinski