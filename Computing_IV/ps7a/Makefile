# Makefile for ps7a
# Flags to save on typing all this out
CC = g++
CFLAGS = -g -Wall -Werror -std=c++0x -pedantic
SFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
Boost = -lboost_regex -lboost_date_time

# Make ps5a & a dummy tester
all:	ps7a

# PS6 executable
ps7a:	ps7a.o
	$(CC) ps7a.o -o ps7a $(Boost)

# Object files
ps7a.o: ps7a.cpp
	$(CC) -c ps7a.cpp $(CFLAGS)
# TextGenerator.o:TextGenerator.cpp MarkovModel.hpp
# 	$(CC) -c TextGenerator.cpp MarkovModel.hpp $(CFLAGS)
#
# MarkovModel.o:MarkovModel.cpp MarkovModel.hpp
# 	$(CC) -c MarkovModel.cpp  MarkovModel.hpp $(CFLAGS)
#
# mmtest.o:mmtest.cpp
# 	$(CC) -c mmtest.cpp $(Boost)

# Cleanup object files
clean:
	rm *.o
	#rm *.gch
	rm ps7a
