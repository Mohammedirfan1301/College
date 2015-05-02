# Makefile for PS0 - Hello World
CC = g++

all:
	$(CC) -c main.cpp -Wall -Werror -ansi -pedantic
	$(CC) main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm main.o
	rm sfml-app