all: masm

# -std=gnu99 removed a "implicit declaration"
masm: mic1symasm.o lex.yy.o
	cc -std=gnu99 -o masm mic1symasm.o lex.yy.o

mic1symasm.o:  mic1symasm.c
	cc -std=gnu99 -c -g mic1symasm.c

lex.yy.o:  lex.yy.c
	cc -std=gnu99 -c -g lex.yy.c

lex.yy.c: mic1symasm.ll
	flex mic1symasm.ll

clean:
	rm -f *.o masm lex.yy.c
