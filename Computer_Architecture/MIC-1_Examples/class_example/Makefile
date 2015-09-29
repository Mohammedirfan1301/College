all: test.actual

ex: ex.c
	cc -std=c99 $^ -o $@

c.test: ex
	./ex

ex.o: ex.asm
	./masm < ex.asm > ex.o

test.actual: ex.o test.in
	./mic1 prom.dat ex.o 0 4000 < test.in > test.actual || true
	grep Accumulator test.actual

clean:
	rm -f ex.o test.actual
