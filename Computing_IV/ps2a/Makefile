# Makefile for ps2a
# Flags to save on typing all this out
CC= g++
CFLAGS= -Wall -Werror -ansi -pedantic
Boost= -lboost_unit_test_framework

# Make both projects
all:	main.out ps2a

# Boost unit tests
ps2a:	test.o LFSR.o
	$(CC) test.o LFSR.o -o ps2a $(Boost)

test.o:	test.cpp LFSR.hpp
	$(CC) -c test.cpp LFSR.hpp $(CFLAGS)

# Main tester
main.out:	main.o LFSR.o
	$(CC) main.o LFSR.o -o main.out

main.o:		main.cpp LFSR.hpp
	$(CC) -c main.cpp $(CFLAGS)

LFSR.o:		LFSR.cpp LFSR.hpp
	$(CC) -c LFSR.cpp $(CFLAGS)

# Cleanup
clean:
	rm *.o
	rm *.out
	rm ps2a