OBJ1 = exercise2-57
OBJ2 = exercise2-58
OBJ3 = exercises

all:
	@echo "Racket has an interpreter. Nothing to build. Perhaps you want, 'make test'?"

test:
	perl test.t

pdf:
	enscript -C --margins=50:50:50:50 -p $(OBJ1).rkt.ps $(OBJ1).rkt
	ps2pdf $(OBJ1).rkt.ps
	enscript -C --margins=50:50:50:50 -p $(OBJ2).rkt.ps $(OBJ2).rkt
	ps2pdf $(OBJ2).rkt.ps
	enscript -C --margins=50:50:50:50 -p $(OBJ3).rkt.ps $(OBJ3).rkt
	ps2pdf $(OBJ3).rkt.ps


clean:
	rm -f *~ 

