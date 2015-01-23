CC		= g++

all:
	$(CC) -c main.cpp -Wall -Werror -ansi -pedantic
	$(CC) main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
# 	$(CC) -c example.cpp -Wall -Werror -ansi -pedantic
# 	$(CC) example.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm main.o
	rm sfml-app