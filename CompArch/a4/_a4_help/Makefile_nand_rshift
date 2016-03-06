masm_nr: mic1symasm_nand_rshift.o lex.yy.o
	gcc -o masm_nr mic1symasm_nand_rshift.o lex.yy.o
mic1symasm_nand_rshift.o:  mic1symasm_nand_rshift.c
	gcc -c -g mic1symasm_nand_rshift.c
lex.yy.o:  lex.yy.c
	gcc -c -g lex.yy.c
lex.yy.c: mic1symasm_nand_rshift.ll
	flex mic1symasm_nand_rshift.ll
clean:
	rm lex.yy.o lex.yy.c mic1symasm_nand_rshift.o masm_nr
