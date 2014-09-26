# Jason Downing
            	.data
prompt_input:   .asciiz     "\nEnter a line of input: " # Prompts
prompt_output:  .asciiz     "\nYou entered: "
input:          .space      80                          # User input.
output:		.space	    80				# Output array (codes) 
pound:          .word       '#'                         # Compare to this symbol
blank:          .asciiz     " "                         # Blank space to compare against.
newline:	.asciiz	    "\n"			

        	.text
main:
    	# Print out prompt & take user input of a string. Store store in input array.
    	la  	$a0, prompt_input   # Loads addr of prompt_input into $a0
    	li  	$v0, 4              # Code 4 means output string.
    	syscall             
    
    	la  	$a0, input          # Loads the address of input into $a0
    	li  	$a1, 80             # Buffer is 80 bytes long.
    	li  	$v0, 8              # Code 8 means input a string.
    	syscall             


#******************************************************************************
#	$s0 is the input array   	
#	$s1 is the output array
#   	$s2 is the Tabchar array
#   	$s3 is the current character we are looking at in the input array
#   	$s4 is the current character we are looking at in the Tabchar array
#   	$s5 is the pound symbol
#   	$s6 is the blank number
#	$s7	is the length of the output
#
#   	General layout of the branches
#   	Main -> Get input, store it, fall through to Test.
#   	Test -> Loop through the entire input array. Call compare on each character, one at a time.
#   	Compare -> Loop through the entire Tabchar array. Branch based on what we find.
#       	IF we find a MATCH, go to MATCH
#       	IF we find a POUND sign, go to DONE.
#   	Match -> IF there's a blank (code 5), print a space. Otherwise fall through to Continue. Then return to test.
#   	Print_Blank -> when called, print blank space, go to continue to increment the input array. Then return to test.
#   	Done -> When pound sign is found, print a "6" and then return to main to continue looping. 
#******************************************************************************

        la      $s0, input	   	 	# Store the address for input array and output arrays.
        la	$s1, output	
        la  	$s5, pound
        lb  	$s5, 0($s5)         		# Also load the pound symbol into $s5 and a space into $s6
        la  	$s6, blank
        lb  	$s6, 0($s6)	
        li	$s7, 0				# Reset output size counter

# This loops character by character through the input array.
test:
        la  	$s2, Tabchar	    	# Each round needs a clean start for Tabchar
        lb      $s3, 0($s0)         	# Grab the current character from the input array.
            
    	j 	compare         	# Go to the next section and compare the current char against all of the chars in Tabchar

# This loops character by character though the Tabchar array.
compare:
    	lb  	$s4, 0($s2)         	# Load current Tabchar character into $s4

    	beq 	$s3, $s5, done      	# if($s3 == $s5) go to done. $s3 is curr char, $s5 is the pound symbol.
    	beq 	$s3, $s4, match     	# if($s3 == $s4) go to match. $s3 is curr char, $s4 is Tabchar char
    
    	addi    $s2, $s2, 8         	# Move Tabchar forward by 8, since each word is 4 bytes and there's two of them per line
    	j   	compare
    
# This part activates when we find a match between a character and Tabchar.
match:
    	addi    $s2, $s2, 4        	# Move forward by 4 to get the code.
    	lw  	$s4, 0($s2)         	# Load current Tabchar character into $s4

    	beq 	$s3, $s6, print_blank   # See if we have a blank symbol. If so, store a space instead of a 5.
    
    	addi	$s4, $s4, 0x30
    	addi	$s7, $s7, 1		# Increase length of the output array
    	sb 		$s4, 0($s1)     # Store the character in the output array         

# Used to prevent blank space codes (5s) from being printed
continue:               
        addi    $s0, $s0, 1     	# Move the input & output arrays forward by one byte.
        addi	$s1, $s1, 1	
        j   test                	# Go back and test some more characters.

# Print a blank space instead of a 5.
print_blank:
    	li  	$a0, 0x20      		# Store a blank space instead of a 5.
    	#addi	$a0, $a0, 0x30
    	sb 	$a0, 0($s1)        
    	
    	j 	continue        	# Go back to continue to move the input array forward.

# WE ARE DONE!
done:                   
    	li  	$a0, 6          	# One last thing though - store the code for the pound symbol.
    	addi	$a0, $a0, 0x30
    	sb  	$a0, 0($s1)              

	# Print back the input and also the final output array.
	la	$a0, input
	li	$v0, 4
	syscall
	
	la	$a0, output
	li	$v0, 4
	syscall
    	
    	# Go back to main to loop.
    	j 		main

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
