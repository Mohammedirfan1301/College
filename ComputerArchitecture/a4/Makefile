# Makefile to build MASM, modified rmd.prom file, and test objects.
# Also tests the programs against .in / .out files
DIR := masm

# Run the whole Makefile
all: assembler prom build test

# cd into the masm directory and call the Makefile for masm
assembler:
	cd $(DIR) && $(MAKE)

# Make the updated rmd.prom file
prom: rmd.mc
	./mcc < rmd.mc > rmd.prom

# Build the test objects
build:
	./masm/masm < a4_rshift_test.asm > rshift.obj
	./masm/masm < a4_mult_test.asm > mult.obj
	./masm/masm < a4_div_test.asm > div.obj

# Test the input files (.ins) against the output files (.outs)
# This is from the assignment 3 Makefile
test:
	./mic1 rmd.prom div.obj 0 1024 < div.in > actual.out || true
	diff -c actual.out div.out | cat -vet

	./mic1 rmd.prom mult.obj 0 1024 < mult.in > actual.out || true
	diff -c actual.out mult.out | cat -vet

	./mic1 rmd.prom rshift.obj 0 1024 < rshift.in > actual.out || true
	diff -c actual.out rshift.out | cat -vet

# Clean up all the files.
clean:
	rm rmd.prom *.obj
	cd $(DIR) && make clean