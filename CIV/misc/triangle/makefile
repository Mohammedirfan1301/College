CC		= g++

all:
	$(CC) -c main.cpp -Wall -Werror -ansi -pedantic
	$(CC) main.o -o triangle -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main.o
	rm triangle