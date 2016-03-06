// assembly parser for mic1 assembly code that
// has been extended to include the RSHIFT and
// NAND 10 bit opcodes (HALT also moved to 10 bit)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// same defines as in the flex scanner file
// should put these in an include file and
// include them in both flex file and here

#define         LODD       1
#define         STOD       2
#define         ADDD       3
#define         SUBD       4
#define         JPOS       5
#define         JZER       6
#define         JUMP       7
#define         LOCO       8
#define         LODL       9
#define         STOL      10
#define         ADDL      11
#define         SUBL      12
#define         JNEG      13
#define         JNZE      14
#define         CALL      15
#define         PSHI      16
#define         POPI      17
#define         PUSH      18
#define         POP       19
#define         RETN      20
#define         SWAP      21
#define         INSP      22
#define         DESP      23
#define         HALT      24
#define         INTEG     25
#define         JUNK      26
#define         LABEL     27
#define         LOC       28
#define         STR       29
#define         NAND	  30
#define         RSHIFT	  31

// global strings used with the similarly named 
// functions below (i.e. cstr_6 is set by str_6()
// such that str_6("27") would load the cstr_6
// array with the string "011011").  These are 
// global so they can be used by several functions

char cstr_6[7];
char cstr_8[9];
char cstr_12[13];
char cstr_16[17];
char binstr_16[17];

int  label_pc = -1;

void  str_6(char *);
void  str_8(char *);
void  str_12(char *);
void  str_16(char *);
void  bstr_16(unsigned short);
void  generate_code(int);
void  update_sym_table(char *);
void  search_sym_table(char *);
void  dump_table(void);

unsigned short pc = 0;
FILE  *p1;

struct nament{
	char   name[26];
	int    addr;
	struct nament *next;
};

// head of our symbol table
struct nament *symtab = NULL;

// imported from the lex.yy.c code
extern int yylex(void);
extern char * yytext;

int  main(int argc, char *argv[])
{
        int tok, i, dump_tab=0, linum=0;
	unsigned short temp;

// if -s is included on masm command, set up to
// dump the symbol table after the binary code
       if(argc > 1 && (strcmp(argv[1], "-s") == 0)) dump_tab = linum = 1;

	p1 = fopen("/tmp/passone", "w+");
	unlink("/tmp/passone");
        while(tok=yylex()){
        switch(tok){
          case LODD:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0000%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0000000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after LODD is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case STOD:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0001%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0001000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after STOD is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case ADDD:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0010%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0010000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after ADDD is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case SUBD:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0011%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0011000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after SUBD is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case JPOS:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0100%s\n",  pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0100000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after JPOS is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case JZER:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0101%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0101000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after JZER is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case JUMP:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  0110%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0110000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after JUMP is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case LOCO:  switch(tok=yylex()){
		    case INTEG: 
		     if(yytext[0] == '-'){
		       fprintf(stderr,"Negative operand after LOCO is %s on line %d, must be positive !\n",yytext, pc);
                     exit(1);
		     }
		     str_12(yytext);
                     fprintf(p1,"%d  0111%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U0111000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after LOCO is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;


          case LODL:  if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after LODL is %s\n",yytext);
                       exit(1);
                   }
		   str_12(yytext);
                   fprintf(p1,"%d  1000%s\n", pc, cstr_12);
                   break;

          case STOL:  if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after STOL is %s\n",yytext);
                       exit(1);
                   }
		   str_12(yytext);
                   fprintf(p1,"%d  1001%s\n", pc, cstr_12);
                   break;

          case ADDL:  if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after ADDL is %s\n",yytext);
                       exit(1);
                   }
		   str_12(yytext);
                   fprintf(p1,"%d  1010%s\n",  pc, cstr_12);
                   break;

          case SUBL:  if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after SUBL is %s\n",yytext);
                       exit(1);
                   }
		   str_12(yytext);
                   fprintf(p1,"%d  1011%s\n", pc, cstr_12);
                   break;

          case JNEG: switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  1100%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U1100000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after JNEG is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

           case JNZE: switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  1101%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U1101000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after JNZE is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case CALL:  switch(tok=yylex()){
		    case INTEG: 
		     str_12(yytext);
                     fprintf(p1,"%d  1110%s\n", pc, cstr_12);
                     break;
		    case LABEL:
		     fprintf(p1,"%d  U1110000000000000    %s\n", pc, yytext);
                     break;
		    default:
                     fprintf(stderr,"Bad operand after CALL is %s on line %d\n",yytext, pc);
                     exit(1);
		   }
		   break;

          case PSHI: fprintf(p1,"%d  1111000000000000\n",pc);
                   break;

          case POPI: fprintf(p1,"%d  1111001000000000\n",pc);
                   break;

          case PUSH: fprintf(p1,"%d  1111010000000000\n",pc);
                   break;

          case POP: fprintf(p1,"%d  1111011000000000\n",pc);
                   break;

          case RETN: fprintf(p1,"%d  1111100000000000\n",pc);
                   break;

          case SWAP: fprintf(p1,"%d  1111101000000000\n",pc);
                   break;

          case INSP: if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after INSP is %s\n",yytext);
                       exit(1);
                   }
		   str_8(yytext);
                   fprintf(p1,"%d  11111100%s\n", pc, cstr_8);
                   break;

          case DESP: if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after DESP is %s\n",yytext);
                       exit(1);
                   }
		   str_8(yytext);
                   fprintf(p1,"%d  11111110%s\n",  pc, cstr_8);
                   break;

          case HALT: fprintf(p1,"%d  1111111111000000\n",pc);
                   break;

          case NAND: fprintf(p1,"%d  1111111100000000\n",pc);
                   break;

          case RSHIFT: if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after RSHIFT is %s\n",yytext);
                       exit(1);
                   }
                   str_6(yytext);
                   fprintf(p1,"%d  1111111101%s\n",  pc, cstr_6);
                   break;
                   break;




          case INTEG:  str_16(yytext);
		    fprintf(p1,"%d  %s\n", pc, cstr_16);
                    break;

	  case LABEL:  if (label_pc == pc){	/* for < lbx: lby: >   */
			fprintf(p1,"%d  U0000000000000000    %s\n", pc, yytext);
		        break;
		    }
		    search_sym_table(yytext);
		    update_sym_table(yytext);
		    label_pc = pc;
		    pc--;
		    break;


	  case LOC:  if((tok=yylex()) != INTEG){
                       fprintf(stderr,"Bad operand after .LOC is %s\n",yytext);
                       exit(1);
                   }
		    if((temp = ((unsigned short)atoi(yytext) )) < pc){
		       fprintf(stderr,"Bad operand after .LOC is %s, TOO SMALL !\n",yytext);
                       exit(1);
                   }

		   pc = temp - 1;
                   break;

	  case STR:  i=1;
		    do{
			if(*(yytext+i) == '\"'){
			  bstr_16(0);
			  fprintf(p1,"%d  %s\n", pc, binstr_16);
			  break;
			}
			temp = (unsigned short)*(yytext+i++);
			if(*(yytext+i) != '\"'){
			temp = (temp | ((unsigned short)*(yytext+i) << 8));
			}
		        bstr_16(temp);
                        fprintf(p1,"%d  %s\n", pc, binstr_16);
		    }while(*(yytext+i++) != '\"' && ++pc);
		    break;


          case JUNK:  fprintf(stderr,"Unrecognized token is %s\n",yytext);
                    exit(26);

          default:  fprintf(stderr,"Default case, unrecoverable error\n");
                    exit(26); 
         } // end while
         pc++;
        } // end switch
   
        generate_code(linum);

        if(dump_tab)dump_table();

	return;

} // end main


// dump symbol table for -s masm command line option
void dump_table(void){
	FILE *fd;
	struct nament *list;
	fd = popen("sort +0 -1 -f", "w");
	printf("***********************************************\n");
        for(list = symtab; list != (struct nament *)0; list = list->next){
		fprintf(fd,"%-25s %4d\n",list->name, list->addr);
	}
	fclose(fd);
	wait(NULL);
	printf("***********************************************\n");
}

// return symbol value to complete an instruction
int get_sym_val(char *symbol)
{
	int i,j;
	struct nament *element, *list;

	for(list = symtab; list != (struct nament *)0; list = list->next){
		if(strcmp(list->name, symbol) == 0){
		   return(list->addr);
		}
	}
	return(-1);
}

// rewind the temporary file and complete each unresolved
// instruction ... send binary to stdout

void generate_code(int linum){

	char linbuf[10];
	char instruction[18];
	int  line_number;
	int  pc, mask, sym_val,i, j, old_pc, diff;
	char symbol[26];

	line_number = old_pc = 0;
	rewind(p1);

	sprintf(linbuf,"%5d:  ", line_number);

	while(fscanf(p1,"%d %s", &pc, instruction) != EOF){
	if((diff = pc - old_pc ) > 1){
	  for(j=1; j<diff; j++){
		sprintf(linbuf,"%5d:  ", line_number++);
		printf("%s1111111111111111\n",(linum ? linbuf: "\0"));
	  }
	}
	sprintf(linbuf,"%5d:  ", line_number++);
	old_pc = pc;

	 if(instruction[0] == 'U'){
	   fscanf(p1, "%s", symbol);
	   if((sym_val = get_sym_val(symbol)) == -1){
		fprintf(stderr, "no symbol in symbol table: %s\n", symbol);
		exit(27);
	   }
	   	
           for(i=0; i<12; i++){
	     cstr_12[i] = '0';
	   }
	   cstr_12[12] = '\0';
         
	   mask = 2048;
           for(i=0; i<12; i++){
	      if(sym_val & mask)
		  cstr_12[i] = '1';
	      mask >>= 1;
	   }
	   for(i=0; i<12; i++){
		instruction[i+5] = cstr_12[i];
	   }
	   printf("%s%s\n",(linum ? linbuf: "\0"),&instruction[1]);
	 }else
	   printf("%s%s\n",(linum ? linbuf: "\0"),instruction);
	}
	fclose(p1);
}

		
	
// enter the value of a symbol into the symbol table
// entry for that symbol when the value is discovered

void update_sym_table(char *symbol)
{
	int i,j;
	struct nament *element, *list;

	for(list = symtab; list; list = list->next){
		if((strcmp(list->name, symbol)) == 0){
		    list->addr = pc;
		    return;
		}
	}
	fprintf(stderr, "error from symbol table on line %d\n", pc);
	exit(27);
}

// search the symbol table for a symbol
// if found just return, if not, add the 
// symbol into the table at the head of the
// symbol table linked list

void search_sym_table(char *symbol)
{
	int i,j;
	struct nament *element, *list;

	for(list = symtab; list; list = list->next){
		if(strcmp(list->name, symbol) == 0)return;
	}
	element = malloc(sizeof (struct nament));
	strcpy(element->name, symbol);
	element->next = symtab;
	symtab = element;
}

// following functions take a string form of a 
// decimal number and convert it into a string of
// corresponding 1 or 0 bits ... for example, if
// str_6("23") was called, this function would take
// the string value "23" and convert it into the
// string value in 6 bits of "0010111" ... this string
// of 7 characters would be left in the global array
// char cstr_6[7];  seen at the beginning of this file.
// There is a similar function and corresponding global
// array for all of the bit strings we need t complete an
// instruction, including the 6 bit string shown here to
// complete an RSHIFT instruction
// 

void    str_6(char *cstr)
{
	unsigned short str_val;
	int i,j,k,mask;

	str_val = (unsigned short)atoi(cstr);
	
        for(i=0; i<6; i++){
	   cstr_6[i] = '0';
	}
	cstr_6[6] = '\0';
         
	j=0;
	mask = 32;
        for(i=0; i<6; i++){
	   if(str_val & mask)
		cstr_6[i] = '1';
	   mask >>= 1;
	}

}

// for 8 bit INSP and DESP instructions

void    str_8(char *cstr)
{
	unsigned short str_val;
	int i,j,k,mask;

	str_val = (unsigned short)atoi(cstr);
	
        for(i=0; i<8; i++){
	   cstr_8[i] = '0';
	}
	cstr_8[8] = '\0';
         
	j=0;
	mask = 128;
        for(i=0; i<8; i++){
	   if(str_val & mask)
		cstr_8[i] = '1';
	   mask >>= 1;
	}

}

// for 12 bit address and constant instructions like
// LODD and LOCO

void    str_12(char *cstr)
{
	unsigned short str_val;
	int i,j,k,mask;

	str_val = (unsigned short)atoi(cstr);
	
        for(i=0; i<12; i++){
	   cstr_12[i] = '0';
	}
	cstr_12[12] = '\0';
         
	j=0;
	mask = 2048;
        for(i=0; i<12; i++){
	   if(str_val & mask)
		cstr_12[i] = '1';
	   mask >>= 1;
	}

}

// for full 16 bit strings representing 2s complement
// integer values in memory

void    str_16(char *cstr)
{
	short str_val;
	int i,j,k,mask;

	str_val = (short)atoi(cstr);
	
        for(i=0; i<16; i++){
	   cstr_16[i] = '0';
	}
	cstr_16[16] = '\0';
         
	mask = (1024 * 32);
        for(i=0; i<16; i++){
	   if(str_val & mask)
		cstr_16[i] = '1';
	   mask >>= 1;
	}

}

// to take an actual short integer (in C binary)
// and convert it into a string of 16 bits of
// 1 and 0 characters with a NULL byte in position
// 17 of the array ... above we're converting decimal
// strings to binary strings, but here we're converting
// a real C short to a corresponding 16 bit binary string

void	bstr_16(unsigned short bin_num)
{
        short str_val;
        int i,j,k,mask;

        str_val = bin_num;

        for(i=0; i<16; i++){
           binstr_16[i] = '0';
        }
        binstr_16[16] = '\0';

        mask = (1024 * 32);
        for(i=0; i<16; i++){
           if(str_val & mask)
                binstr_16[i] = '1';
           mask >>= 1;
        }

}

