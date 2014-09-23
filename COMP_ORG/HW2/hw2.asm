# VARIABLES  
        	.data
prompt_input:	.asciiz		"Enter a line of input: "
prompt_output:	.asciiz		"You entered: "
input:  	.space 80	# This will be what the user inputs.	
output:		.space 80	# This is where the output codes are storeds.

# CODE
        .text
main:
	# Print out "Enter a line of inptut: "
	la 	$a0, prompt_input	# Loads prompt_input into $a0
	li	$v0, 4			# Code 4 means output string.
	syscall
	
	# Take user input, store the entry in input.
	la 	$a0, input		# Loads the address of input into $a0
	li 	$a1, 80			# Buffer is 80 bytes long.
	li	$v0, 8			# Code 8 means input a string.
	syscall

# $s1 is the input array's address
# $s2 is the output array's address
# $s3 is the current character we are looking at in the input array.
# $s4 is the Tabchar array
# $s5 is the current character we are looking at in the Tabchar array.

	# Store the address for input/output/Tabchar arrays
        la      $s1, input     	
        la	$s2, output
        la	$s4, Tabchar

# This loops character by character through the input array.
test:
        lb      $s3, 0($s1)     # Grab the current character from the input array.
        
	# Right here is where we will jump to another loop.
	# That loop will compare this character with the entire Tabchar array to find 
	# the code that corresponds with that type of character.
	j compare
        
        # CHECK TO SEE IF WE HIT THE END OF THE ARRAY
        # beq is compare and see if equal. z means compare to 0.
        # ex: if(c == '\0') -> if false, ignore, if true go to done.
        beqz    $s3, print      
        			
        # Move each array forward by one byte.
        addi    $s1, $s1, 1     
        addi	$s2, $s2, 1	
        
        # Pass go and collect $200. Return to test.
        j       test		

# This loops character by character though the Tabchar array.
compare:
	lb	$s5, 0($s4)
	
	# Compare each character to see if we have a match.
	# When we find a match, go to the match part.
	beq	$s3, $s5, match
	
	# Move Tabchar forward by 8, since each word is 4 bytes and 
	# there's two of them per line
	addi	$s5, $s5, 8
	j	compare
	
# This part activates when we find a match between a character and Tabchar.
match:
	# Save the code into output
	addi	$s5, $s5, 4	# Move forward by 4 to get the cocde.
        sb	$s3, 0($s2)	# store the code in output.
        
        j	test

# This prints out the final array and returns to main for more fun.
print:
	# Print out what the user typed in. See main for additional comments.
	la	$a0, output
	li	$v0, 4
	syscall
	
	# Exit the program. In the future, this will loop back to main or getline.
       	li $v0, 10
	syscall
	
	# Return to main for more looping fun! (THIS NEVER EVER ENDS >:D)
	#j main


# Array to compare to	
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
