DEBUG	=	-g
CFLAGS	=	-Wall --std=c99 $(DEBUG)

EXE	=	demo tests

all : $(EXE)

demo : intarray.o demo.o
	$(CC) $(DEBUG) intarray.o demo.o -o demo

tests : intarray.o tests.o
	$(CC) $(DEBUG) intarray.o tests.o -o tests

clean :
	rm -f *.o *~ $(EXE)
