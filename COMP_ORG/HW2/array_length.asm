# Runs through an array and stores each character into another array
      
# VARIABLES  
        .data
input:  	.asciiz "hello I'm testing to see if this works or not"		# This will be what the user inputs.	
tabchar:	.asciiz " 5#6(4)4*3+3,4-3.4/3"					# Array to hold the values to compare to
output:		.space	20							# This becomes input. It will become the 
										# misc. numbers that we compare to though.
# CODE
        .text
main:

# $s1 is the input array's address, stored in a register.
# $s2 is the output array's address, stored in another register
# $s3 is the current character we are looking at.

        la      $s1, input     	# input is stored in $s1
        la	$s2, output	# output is stored in $2
        
test:
        lb      $s3, 0($s1)     # Grab the current character from the input array.
        
        # Save the char into output
        sb	$s3, 0($s2)	# store the char in output
        			# sb means store on byte.
        			# characters are one byte so this just stores one of them.
        
        # CHECK TO SEE IF WE HIT THE END OF THE ARRAY
        # beq is compare and see if equal. z means compare to 0.
        # ex: if(c == '\0') -> if false, ignore, if true go to done.
        beqz    $s3, done      
        			
        addi    $s1, $s1, 1     # Move the input array forward by one byte.
        addi	$s2, $s2, 1	# Move the output array forward by one byte.
        
        # Pass go and collect $200. Return to test.
        j       test		
        
done:
	# could have just gone to print, this spot is a place holder for future loops.
	j print

print:
	# Print out what the user typed in.
	la	$a0, output
	li	$v0, 4
	syscall
	
	# Exit the program. In the future, this will loop back to main or getline.
       	li $v0, 10
	syscall
