#STACK	= -DHAS_STACK_OPERATIONS
DEBUG	= -g

CFLAGS	= -Wall --std=c99 $(STACK) $(DEBUG)

OBJS	= mystring.o

tester:	tester.o tests.o $(OBJS)
	$(CC) -o tester $(DEBUG) tester.o tests.o $(OBJS)

derrell-tester:	tester.o derrell-tests.o $(OBJS)
	$(CC) -o derrell-tester $(DEBUG) tester.o derrell-tests.o $(OBJS)

derrell-tests.o:

clean :
	rm -f *.o tester derrell-tester
