		.data
prompt_input:	.asciiz		"Enter a line of input: "
prompt_output:	.asciiz		"You entered: "
prompt:		.asciiz		"YAY"
input:		.space		80		# 80 character array to hold the user's input
output:		.space		80		# 
saveReg:	.word		0
tabchar:	.word		'#'

		.text
main:		

getline:	
		# Print out "Enter a line of inptut: "
		la 	$a0, prompt_input
		li	$v0, 4
		syscall
		
		# Take user input, store the entry in input.
		la 	$a0, input
		li 	$a1, 80
		li	$v0, 8
		syscall
		
		# Going to try to just print each character out line by line.
		# Then I can just send each character to another function to compare it.
		# and continue doing so forever until I find a magic "#"
		
		jal	setup
		jal 	printchar
		
		
		# Call two functions - printline to output what the user entered
		# and inspect to see what types of characters were entered.
		#jal	printline
		#jal	
		#jal	inspect
		
		# Exit the program successfully, by calling code 10.
		li	$v0, 10		
		syscall
	
printline:	
		# Print out "You Entered: "
		la 	$a0, prompt_output
		li	$v0, 4
		syscall

		# Print out what the user typed in.
		la	$a0, output
		li	$v0, 4
		syscall
		
		jal	getline
		
# Below this point is messed up. Doesn't really work.

# $s0 will hold the current character
# Ss1 will someday hold the output type
# $s2 will hold the pound sign (#)

setup:		# Sets up the printchar loop
		la $s0, input
		lb $a0, ($s0)
		la $s2, tabchar
		syscall
		jal printchar

printchar:	# See if we've hit the end of the array (#)
		beq  	$s0, $s2, done
		# Printing out each indivual character. YAY!
		lb $a0, ($t0)
		li $v0, 11
		syscall
		
		# move forward 1 char in the array
		addi $t0, $t0, 8
		
		# keep looping
		#j printchar
		j printline
		
done:		# DEBUG
		la $a0, prompt
		li $v0, 4
		jal printline

# This part is the "array of codes"	
	
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
