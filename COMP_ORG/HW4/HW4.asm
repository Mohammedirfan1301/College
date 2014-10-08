# Jason Downing
# 10/7/2014

                .data
inArr:          .word     0:40
symTab:         .word     0:40
prompt:         .asciiz   "Enter new set of tokens and types: "
dump_prompt:	.asciiz	  "\nDumping symTab: \n\n"
exit_prompt:	.asciiz	  "\n\nExiting the program..."

        .text
main:
	# Initialize variables.
        li      $t0, 0      	# index to inArr
        li	$t1, 0		# index for symTab
        li      $t2, 0 		# DEFN
        li	$t3, 0		# LOC
        li	$t6, 0		# TEMP index for looping, clearing, dumping, etc.

# $s0 -> the value of the current input.
# $s1 -> Used for comparing individual characters against

# NOTES
# Input should be a label
# THEN enter.
# Followed by a number 2 - 6

# Need to store the following in symTab:
# The TOKEN (two words / 8 characters)
# The value (one word / 1 integer / 4 bytes)
# The status (one word / 1 integer / 4 bytes)

#
# Get one label, followed by a number.
#
inLoop:
        jal     getTokens			# Get one label and one number.

#
# Check to see what we found.
#
chkVar:
        beq     $t6, 2, label		# 0x32 = decimal #2, which is a label.
        beq	$t6, 4, control		# 0x34 = decimal #4, which is a colon or comma.
        beq	$t6, 5, money		# 0x35 = decimal #5, which is the money sign.
        beq	$t6, 6, pound		# 0x36 = decimal #6, which is the pound sign.

        # If we get here, the user entered something strange so just quit!
        b exit

#
# Save one label and its type to the inArr array.
#
getTokens:
	# Print out prompt
    	la  	$a0, prompt   	# Loads addr of prompt_input into $a0
    	li  	$v0, 4          # Code 4 means output string.
    	syscall

	# Press enter between the label and the number.

	# Input the label.
    	la  	$a0, inArr($t0)      	# Loads the address of input into $a0
    	li  	$a1, 8         		# Buffer is 8 bytes long for 8 characters.
    	li  	$v0, 8          	# Code 8 means input a string.
    	syscall
    	
    	#  Move forward by 8, to be able to save the integer.
    	addi	$t0, $t0, 8
    	
    	# Input the number.
	li	$v0, 5			# Code 5 means input an integer.
	syscall
	
	# Save the number to inArray
	sw 	$v0, inArr($t0)

	# Save the current inArray value to $s1
	lw	$t6, inArr($t0)

	# Move the array forward by 4. Since we stored a 4 byte integer.
	addi	$t0, $t0, 4

	b	chkVar			# Go to chkVar

# 
# We found a label, so save the label & it's value into symTab. Also DEFN = 1.
#
label:
	# Save the two words
	subi 	$t7, $t0, 12		# Go back 12 spaces.
	lw	$v0, inArr($t7)		# Load the first word into $v0
	sw	$v0, symTab($t3)	# Save that word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Get the next word
	sw	$v0, symTab($t3)	# Save this word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the type (integer)
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Save the int into $v0
	sw	$v0, symTab($t3)	# Save the int into the symTab array
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the DEFN (integer)
	li	$v0, 1			# Save 1 into $v0
	sw	$v0, symTab($t3)	# Save DEFN into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	b inLoop # Once we've added the label, value & DEFN into symTab, return to inLoop

#
# Found a colon or a comma, so save that + it's value into symTab. Also DEFN = 0.
#
control:
	# Save the comma or colon
	subi 	$t7, $t0, 12		# Go back 12 spaces.
	lw	$v0, inArr($t7)		# Load the first word into $v0
	sw	$v0, symTab($t3)	# Save that word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Get the next word
	sw	$v0, symTab($t3)	# Save this word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the type (integer)
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Save the int into $v0
	sw	$v0, symTab($t3)	# Save the int into the symTab array
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the DEFN (integer)
	li	$v0, 0			# Save 1 into $v0
	sw	$v0, symTab($t3)	# Save DEFN into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4
	
	b inLoop # Once we've added it to symTab, return to inLoop

#
# Found a money sign, so save a "$", its value (5) and DEFN = 0 into symTab.
#
money:
	# Save the money sign
	subi 	$t7, $t0, 12		# Go back 12 spaces.
	lw	$v0, inArr($t7)		# Load the first word into $v0
	sw	$v0, symTab($t3)	# Save that word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Get the next word
	sw	$v0, symTab($t3)	# Save this word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the type (integer)
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Save the int into $v0
	sw	$v0, symTab($t3)	# Save the int into the symTab array
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the DEFN (integer)
	li	$v0, 0			# Save 1 into $v0
	sw	$v0, symTab($t3)	# Save DEFN into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	b inLoop # Once we've added it to symTab, return to inLoop

#
# Found the pound sign, so we're done! Save the sign, its value (6) and DEFN = 0.
#
pound:
	# Save the pound sign
	subi 	$t7, $t0, 12		# Go back 12 spaces.
	lw	$v0, inArr($t7)		# Load the first word into $v0
	sw	$v0, symTab($t3)	# Save that word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Get the next word
	sw	$v0, symTab($t3)	# Save this word into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the type (integer)
	addi	$t7, $t7, 4		# Go ahead 4 bytes to get the next word.	
	lw	$v0, inArr($t7)		# Save the int into $v0
	sw	$v0, symTab($t3)	# Save the int into the symTab array
	addi	$t3, $t3, 4		# Move LOC forward by 4.
	
	# Save the DEFN (integer)
	li	$v0, 0			# Save 0 into $v0
	sw	$v0, symTab($t3)	# Save DEFN into symTab
	addi	$t3, $t3, 4		# Move LOC forward by 4.


	# FIRST: Print symTab.
	# SECOND: Clear inArr
	# FINALLY: exit.
	
	# DUMPING SYMBTAB.
    	la  	$a0, dump_prompt   	# Loads address of prompt_input into $a0
    	li  	$v0, 4          	# Sys Call Code 4 means output string.
    	syscall

    	# Load up the symTab array.
    	li	$t1, 0			# index for symTab. LOC ($t3) will be our max number to loop through.

	# Get the address of symTab into $a1
	la 	$a1, symTab		# Loads address of symTab into $a1.	
        
        jal     dumpSymTab
        

#
# dumpSymTab: Print the symTab array to the screen.
#
dumpSymTab:
	beq	$t1, $t3, setUpClear		# Go nuke the array once we're done here.
	
	# Output the first word in the symbTab Array.
    	#lw  	$a0, symTab($t1)   		# Loads the word from symTab into $a0
    	
    	li	$t6, 0				# Start at 0, go to 3.
    	jal 	printWord			# Go print the next four bytes of $a0.
    	
    	addi	$a1, $a1, 4			# move forward one word.
    	addi	$t1, $t1, 4			# move forward one word.
    	
    	# Output the second word in the symbTab Array.
    	#lw  	$a0, symTab($t1)   		# Loads the word from symTab into $a0
	
	
    	#la 	$a1, symTab			# Load address of symTab into $a1.
	li	$t6, 0				# Start at 0, go to 3.
    	jal 	printWord			# Go print the next four bytes of $a0.
    	
    	addi	$a1, $a1, 4			# move forward one word.
    	addi	$t1, $t1, 4			# move forward one word.
    	
    	# Then output the value of the label/variable.
    	lw  	$a0, symTab($t1)   		# Loads addr of prompt_input into $a0
    	li  	$v0, 1          		# Code 1 means output integer.
    	syscall
    	
    	addi	$a1, $a1, 4			# move forward one word.
    	addi	$t1, $t1, 4			# move forward one word.
    	
    	# Finally, output DEFN (0 or 1)
    	lw  	$a0, symTab($t1)   		# Loads addr of prompt_input into $a0
    	li  	$v0, 1          		# Code 1 means output integer.
    	syscall
    	
    	addi	$a1, $a1, 4			# move forward one word.
    	addi	$t1, $t1, 4			# move forward one word.
    	
	b	dumpSymTab
	
	
#
# This function will print out 4 bytes - AKA a word.
#
printWord:
	
	# Next thing to do. Print out 4 bytes.
	# Something like
	beq	$t6, 4, returnToFunction	# Once we print out the 4 characters, go back to dumbSymTab
	
	
	# TRY THIS
	#la $t0, string
	#lb $a0, ($t0)
	#li $v0, 11
	#syscall	
	
	# Print out one character.
	lb	$a0, ($a1)
	li 	$v0, 11
	syscall
	
	# Increase the index by 1.
	addi	$a1, $a1, 1
	
	# Increase the counter by 1.
	addi	$t6, $t6, 1
	
	b 	printWord
	
returnToFunction:
	jr	$ra	# Go back to where the jal call is from.


#
# Sets up the clearing inArr
#
setUpClear:
	# Clear the array
	li 	$t6, 0	# Index to use for clearing the array.     	

        jal     clearInArr


#
# clearInArr: wipes the inArry array.
#
clearInArr:
	beq	$t0, $t6, exit		# done clearing if $t6 is equal to the max number of bytes in inArr

	sb 	$0, inArr($t6)     	# Put a null throughout the array

        addi	$t6, $t6, 1		# Move the index forward by 1.

        b clearInArr			# Keep looping
        
        
#
# Exiting the program at this point.
#
exit:
	# Print out prompt
    	la  	$a0, exit_prompt   	# Loads addr of prompt_input into $a0
    	li  	$v0, 4          	# Sys Call Code 4 means output string.
    	syscall

	# Exit the program.
	li	$v0, 10			# Sys call code 10 = exit the program.
	syscall	
