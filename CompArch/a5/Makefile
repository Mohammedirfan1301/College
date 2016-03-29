# Run the whole Makefile
all: build test

# Build the A5 assignment object.
build:
	./masm < a5.asm > a5.obj

# Run the A5 program, everything outputs to terminal
test:
	./mic1 prom_mrd.dat a5.obj 0 1024

# Clean up all the files.
clean:
	rm *.obj
