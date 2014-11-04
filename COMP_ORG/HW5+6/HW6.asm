# Jason Downing™ ©2014
# 11/3/2014

                .data
inArr:          .word     0:40
symTab:         .word     0:40
prompt:         .asciiz   "Enter a new token: "
prompt2:        .asciiz   "Enter a new  type: "
dump_prompt:	.asciiz	  "\nDumping symTab: \n\n"
exit_prompt:	.asciiz	  "\n\nExiting the program..."
error_prompt:	.asciiz	  "\n****** ERROR: DOUBLE DEFINITION!****** \n\n"

        .text
main:
	# Initialize variables.
        li      $t0, 0      	# index to inArr    ( ALSO the MAX number to compare against )
        li	$t1, 0		# index for symTab  ( ALSO the MAX number to compare against )
        li      $t2, 0 		# DEFN
        li	$t3, 0		# LOC
        li	$t6, 0		# TEMP index for looping, clearing, dumping, etc.
	li	$t7, 0		# This will hold the return address for the VARIABLE function.


# NOTES
# Input should be a label
# THEN enter.
# Followed by a number 2 - 6

# Need to store the following in symTab:
# The TOKEN (two words / 8 characters)
# The value (one word / 1 integer / 4 bytes)
# The status (one word / 1 integer / 4 bytes)


# Save one label and its type to the inArr array.
getTokens:
	# Print out prompt
    	la  	$a0, prompt   		# Loads addr of prompt_input into $a0
    	li  	$v0, 4          	# Code 4 means output string.
    	syscall

	# Press enter between the label and the number.

	# Input the label.
    	la  	$a0, inArr($t0)      	# Loads the address of input into $a0
    	li  	$a1, 10         	# Buffer is 8 bytes long for 8 characters.
    	li  	$v0, 8          	# Code 8 means input a string.
    	syscall
    	
    	#  Move forward by 8, to be able to save the integer.
    	addi	$t0, $t0, 8
    	    	
	# Print out prompt
    	la  	$a0, prompt2   		# Loads addr of prompt_input into $a0
    	li  	$v0, 4         	 	# Code 4 means output string.
    	syscall

    	# Input the number.
	li	$v0, 5			# Code 5 means input an integer.
	syscall
	
	# Save the number to inArray
	sw 	$v0, inArr($t0)

	# Save the current inArray value to $s1
	lw	$t6, inArr($t0)

	# Move the array forward by 4. Since we stored a 4 byte integer.
	addi	$t0, $t0, 4
	
	
# Check to see what we found.
chkVar:
        beq     $t6, 2, label		# 0x32 = decimal #2, which is a label.
        beq	$t6, 4, control		# 0x34 = decimal #4, which is a colon or comma.
        beq	$t6, 5, money		# 0x35 = decimal #5, which is the money sign.
        beq	$t6, 6, pound		# 0x36 = decimal #6, which is the pound sign.

        # If we get here, the user entered something strange so just quit!
        b exit


# We found a label, so save the label & it's value into symTab. Also DEFN = 1.
label:

	# Sounds like for HW6 we need to check each variable and see if it has been defined before?
	# And I guess if it has been defined, return something?
	# I'm not quite sure on this part.
	
	# So... Let's call VARIABLE and check this TOKEN, VALUE, STATUS.
	jal variable			# Return address stored in $ra

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
	
	b getTokens 			# Once we've added the label, value & DEFN into symTab, return to getTokens


# Found a colon or a comma, so save that + it's value into symTab. Also DEFN = 0.
control:

	# Same as label, call VARIABLE.
	jal variable			# Return address stored in $ra

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
	
	b getTokens 			# Once we've added the label, value & DEFN into symTab, return to getTokens


# Found a money sign, so save a "$", its value (5) and DEFN = 0 into symTab.
money:

	# Same as label, call VARIABLE.
	jal variable			# Return address stored in $ra

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
	
	b getTokens 			# Once we've added the label, value & DEFN into symTab, return to getTokens


# This is the new function for HW6, which will check the token/value/status and see if it has already been defined yet.
# It appears we always return FFFFx for no reason, so instead I'll do the following:
# IF the TOKEN is already defined, then print out an error.
# IF the TOKEN is not already defined, simply return because that's A OK.
variable:
	
	# Let's loop through the inArr and see if we can find the current label. If we can, let's print out:
	# “ERROR: DOUBLE DEFINITION!”
	# If we don't find it, just return like normal.
	
	# Let's start by saving the return address to where we came from. Otherwise we might lose it and that would be bad.
	move	$t7, $ra

	# Setup $t6 as the index to inArr. Note that $t0 is the highest index to go to.
	la	$t6, inArr

	# Now let's loop through inArr and see if we find any dups.
	b loopdeloop
	

# This loop just loops through inArr, searching for the current label.
loopdeloop:
	beq	$t0, $t6, loopdone	# done looping once we get here.
	
	# Let's compare and see if we found a match!

	# Need to compare against 8 bits, then jump 8 bits ahead and keep comparing.
	# This is because the inArr array is setup as following:
	#
	# [][][][] [][][][]  [][][][]  [][][][]
	# ----- TOKEN -----  --TYPE--  --DEFN--
	# We only care about TOKEN. TYPE and DEFN doesn't matter.
	
	# Therefore we need to continuosly loop through 8 bit words and see if we
	# find a complete match for 8 whole bits.
	
	# Let's use another function to compare against each individual word. This function will serve as the master
	# function that keeps looping through all the words.
	li	$t7, 0		# $t7 will index through each word.
	jal compare_word
	
	# Increase $t6 by 8 to make it to the next word.
	add	$t6, $t6, 8
	
	b loopdeloop			# Just keep looping, just keep looping...

compare_word:
	# 

# When we're done looping through inArr, let's just return to where ever we came from.
loopdone:
	jr	$t7			# Return to where we came from, prob Label/Control/Money sub labels

# This gets called when we detect a duplicate in the inArr table.
double_error:
	
	# Print out error prompt, since we found a double input.
    	la  	$a0, error_prompt   	# Loads addr of prompt_input into $a0
    	li  	$v0, 4          	# Sys Call Code 4 means output string.
    	syscall
    	
    	jr	$t7			# Return to where we came from, prob Label/Control/Money sub labels

# Found the pound sign, so we're done! Save the sign, its value (6) and DEFN = 0.
pound:

	# Since we're done if we find the pound sign, we do not need to call VARIABLE.

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
	
    	la  	$a0, dump_prompt   	# Loads address of prompt_input into $a0
    	li  	$v0, 4          	# Sys Call Code 4 means output string.
    	syscall

    	# We'll need an index variable and the address of symTab.
    	li	$t1, 0			# index for symTab. LOC ($t3) will be our max number to loop through.
	la 	$a1, symTab		# Loads address of symTab into $a1.	
        
        jal     dumpSymTab		# Go dump the symTab array
        

# dumpSymTab: Print the symTab array to the screen.
dumpSymTab:
	beq	$t1, $t3, setUpClear		# Go nuke the array once we're done here.
	
	# Output the first two words in the symbTab Array.
    	li	$t6, 0				# Start at 0, go to 3.
    	jal 	printWords			# Go print the next eight bytes of $a0.
    	
    	addi	$t1, $t1, 8			# move forward two words.
    	
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
	
	
# This function will print out the first two words (8 bytes),
printWords:
	beq	$t6, 8, returnToFunction	# Once we print out the 4 characters, go back to dumbSymTab
	
	# Print out one character.
	lb	$a0, ($a1)
	li 	$v0, 11
	syscall

	addi	$a1, $a1, 1		# Increase the index by 1.
	addi	$t6, $t6, 1		# Increase the counter by 1.
	
	b 	printWords


returnToFunction:
	jr	$ra			# Go back to where the jal call is from.


# Sets up the clearing inArr
setUpClear:
	li 	$t6, 0			# Index to use for clearing the array.     	


# clearInArr: wipes the inArry array.
clearInArr:
	beq	$t0, $t6, exit		# done clearing if $t6 is equal to the max number of bytes in inArr

	sb 	$0, inArr($t6)     	# Put a null throughout the array

        addi	$t6, $t6, 1		# Move the index forward by 1.

        b clearInArr			# Keep looping
        

# Exiting the program at this point.
exit:
	# Print out prompt
    	la  	$a0, exit_prompt   	# Loads addr of prompt_input into $a0
    	li  	$v0, 4          	# Sys Call Code 4 means output string.
    	syscall

	# Exit the program.
	li	$v0, 10			# Sys call code 10 = exit the program.
	syscall	
