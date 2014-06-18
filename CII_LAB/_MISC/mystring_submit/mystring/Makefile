DEBUG	= -g
CFLAGS	= -Wall --std=c99 $(DEBUG)

OBJS	= mystring.o

tester:	tester.o tests.o $(OBJS)
	$(CC) -o tester $(DEBUG) tester.o tests.o $(OBJS)

clean :
	rm -f *.o tester
