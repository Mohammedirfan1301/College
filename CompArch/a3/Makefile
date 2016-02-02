all:
	./masm < fib.asm > fib.obj
	./mic1 prom.dat fib.obj 0 1024 < test.in > actual.out || true
	diff -c actual.out test.out | cat -vet
