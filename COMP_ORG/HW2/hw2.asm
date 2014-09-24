# Jason Downing

# VARIABLES  
        	.data
prompt_input:	.asciiz		"\nEnter a line of input: "	# Prompts
prompt_output:	.asciiz		"You entered: "
input:  	.space 80			# This will be what the user inputs.	
pound:		.word  '#'			# Compare to this symbol
pound_num:	.asciiz	"6"			# For the pound symbol's code.
blank:		.asciiz " "			# Blank space to compare against.

# CODE
        .text
main:
	la 	$a0, prompt_input	# Loads prompt_input into $a0
	li	$v0, 4			# Code 4 means output string.
	syscall				
	
	la 	$a0, input		# Loads the address of input into $a0
	li 	$a1, 80			# Buffer is 80 bytes long.
	li	$v0, 8			# Code 8 means input a string.
	syscall				

# $s1 is the input array's address
# $s2 is the Tabchar array's address
# $s3 is the current character we are looking at in the input array.
# $s4 is the current character we are looking at in the Tabchar array.
# $s5 is the pound symbol.
# $s6 is the blank number

        la      $s1, input	# Store the address for input array.
        la	$s5, pound
        lb	$s5, 0($s5)	# Also load the pound symbol into $s5 
        la	$s6, blank
        lb	$s6, 0($s6)	# and a space into $s6

# This loops character by character through the input array.
test:
        la	$s2, Tabchar	# Each round needs a clean start for Tabchar
        lb      $s3, 0($s1)    	# Grab the current character from the input array.
        
	# Go to the next section and compare the current char against all of the chars in Tabchar
	j compare

# This loops character by character though the Tabchar array.
compare:
	lb	$s4, 0($s2)		# Load current Tabchar character into $s4
	
	beq	$s3, $s5, print		# See if we hit the delimitor -> if($s3 == $s5) go to print.
	beq	$s3, $s4, match		# Compare each character to see if we have a match. -> if($s3 == $s4) go to match.
	
	# Move Tabchar forward by 8, since each word is 4 bytes and there's two of them per line
	addi	$s2, $s2, 8
	j	compare
	
# This part activates when we find a match between a character and Tabchar.
match:
	addi	$s2, $s2, 4	# Move forward by 4 to get the code.
	lw	$s4, 0($s2)	# Load current Tabchar character into $s4

	# See if we have a blank symbol. If so, skip the printing of the number code.
	beq	$s3, $s6, print_blank

	# Print out the current character code.
	li	$v0, 1		# Load system code into $v0 (int needs code 1)
	move	$a0, $s4	# Move $s4's int value into $a0 to be printed.
	syscall

# Used to prevent blank space codes (5s) from being printed
continue:
        addi    $s1, $s1, 1	      	# Move the input array forward by one byte.
        j	test			# Go back and test some more characters.

# Print a blank space instead of a 5.
print_blank:
	la	$a0, blank
	li	$v0, 4
	syscall
	
	j continue

# This prints out the final array and returns to main for more fun.
print:
	la	$a0, pound_num		# One last thing - print out the code for the pound symbol!
	li	$v0, 4
	syscall
	
	j main				# Return to main for more fun!

# Array to compare each character against and to get the code to print out.
	.data
Tabchar: 	
	.word ' ', 5
 	.word '#', 6 
	.word '(', 4 
	.word ')', 4 
	.word '*', 3 
	.word '+', 3 
	.word ',', 4 
	.word '-', 3 
	.word '.', 4 
	.word '/', 3 
	.word '0', 1
	.word '1', 1 
	.word '2', 1 
	.word '3', 1 
	.word '4', 1 
	.word '5', 1 
	.word '6', 1 
	.word '7', 1 
	.word '8', 1 
	.word '9', 1 
	.word ':', 4 
	.word 'A', 2
	.word 'B', 2 
	.word 'C', 2 
	.word 'D', 2 
	.word 'E', 2 
	.word 'F', 2 
	.word 'G', 2 
	.word 'H', 2 
	.word 'I', 2 
	.word 'J', 2 
	.word 'K', 2
	.word 'L', 2 
	.word 'M', 2 
	.word 'N', 2 
	.word 'O', 2 
	.word 'P', 2 
	.word 'Q', 2 
	.word 'R', 2 
	.word 'S', 2 
	.word 'T', 2 
	.word 'U', 2
	.word 'V', 2 
	.word 'W', 2 
	.word 'X', 2 
	.word 'Y', 2
	.word 'Z', 2
	.word 'a', 2 
	.word 'b', 2 
	.word 'c', 2 
	.word 'd', 2 
	.word 'e', 2 
	.word 'f', 2 
	.word 'g', 2 
	.word 'h', 2 
	.word 'i', 2 
	.word 'j', 2 
	.word 'k', 2
	.word 'l', 2 
	.word 'm', 2 
	.word 'n', 2 
	.word 'o', 2 
	.word 'p', 2 
	.word 'q', 2 
	.word 'r', 2 
	.word 's', 2 
	.word 't', 2 
	.word 'u', 2
	.word 'v', 2 
	.word 'w', 2 
	.word 'x', 2 
	.word 'y', 2
	.word 'z', 2
