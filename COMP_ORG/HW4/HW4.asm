# Jason Downing
# 10/6/2014

                .data
inArr:          .word     0:40
symTab:         .word     0:40
prompt:         .asciiz   "Enter new set of tokens and types: "
exit_prompt:	.asciiz	  "Exiting the program..."

        .text
main:
	# Initialize variables.
        li      $t0, 0      	# index to inArr
        li	$t1, 0		# index for symTab
        li      $t2, 0 		# DEFN
        li	$t3, 0		# LOC
        la	$t4, inArr	# addr of inArr.
        la	$t5, symTab	# addr of symTab.
        

# DOCUMENTATION ON THE VARIABLES USED IN THIS PROGRAM.
# $t0 -> index for inArr.
# $t1 -> index for symTab
# $t2 -> DEFN
# $t3 -> LOC
# $t4 -> addr of inArr
# $t5 -> addr of symbTab
# $t6 -> Current value.

# $s0 -> the value of the current input.
# $s1 -> Used for comparing individual characters against

# NOTES
# Input should be a label
# THEN enter.
# Followed by a number 2 - 6

# Need to store:
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
	
	b inLoop # Once we've added it to symTab, return to inLoop

#
# Found a colon or a comma, so save that + it's value into symTab. Also DEFN = 0.
#
control:
	
	b inLoop # Once we've added it to symTab, return to inLoop

#
# Found a money sign, so save a "$", its value (5) and DEFN = 0 into symTab.
#
money:
	
	b inLoop # Once we've added it to symTab, return to inLoop

#
# Found the pound sign, so we're done! Save the sign, its value (6) and DEFN = 0.
#
pound:
	# Found the pound, so save it in symTab! Along with its value!
        lb      $s0, inArr($t0)


	# Clear the array
    	li	$t0, 0		# index
    	li	$t1, 40		# max
    	la	$t2, inArr	# inArr
    	
    	# Load up the symTab array.
    	li	$t3, 0		# index
    	la 	$t4, symTab	# symbTab index.
    	li	$t3, 40		# "max number to loop through".

        jal     dumpSymTab
        jal     clearInArr

        b       exit

#
# dumpSymTab: Print the symTab array to the screen.
#
dumpSymTab:
	beq	$t3, $t5, clearInArr		# Go nuke the array once we're done here.
	
	# First output the label?
    	la  	$a0, symTab($t0)   		# Loads addr of prompt_input into $a0
    	li  	$v0, 4          		# Code 4 means output string.
    	syscall
    	
    	addi	$t3, $t3, 4			# move forward one word.
    	
    	# Then output the Value (2, 4, 5, 6)
    	
    	
    	# Finally, output DEFN (0 or 1)
    	
    	
	b	dumpSymTab


#
# clearInArr: wipes the inArry array.
#
clearInArr:
	beq	$t0, $t1, exit		# done clearing
	beq	$t1, $0,  exit		# Seems we needed to end early if we hit this.

	sb 	$0, 0($t2)     		# Put a null throughout the array

	addi    $t0, $t0, 4     	# Move the output
        addi	$t2, $t2, 4
        b clearInArr
        
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
