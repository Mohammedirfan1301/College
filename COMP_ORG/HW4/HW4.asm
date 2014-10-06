# Jason Downing
# 10/6/2014

                 .data
inArr:           .word     0:40
symTab:          .word     0:40
prompt:          .asciiz   "Enter new set of tokens and types: "
LOC:             .word     0

        .text
main:
	# Initialize variables.
        li      $t0, 0x0400
        sw      $t0, LOC	# LOC starts at 0x0400

# DOCUMENTATION ON THE VARIABLES USED IN THIS PROGRAM.
# $t0 -> index for inArr.
# $t9 -> DEFN

# $s0 -> inArr's value at the current position.
# $s1 -> Used for comparing individual characters, to space.

#
# Get a line of input from getTokens. Then detect the ":" operator.
#
inLoop:
        jal     getTokens

        li      $t9, 0      # DEFN
        li      $t0, 0      # index to inArr

        lb      $s0, inArr+12($t0)
        bne   	$s0, ':', operator	# If we find a ":", go to operator.

        jal     getLabel

#
# Found an operator.
#
operator:
        lb      $s0, ','
        lw     	$s1, inArr+20($t0)

#
# Check to see if we found a variable.
#
chkVar:
        bne     $s1, 0x32, noVar		# IF we find a space, don't continue! Go to noVar.
        # found a variable
        # save the var and LOC into symTab
        jal     getVar

#
# Did not find a variable, so get the next 12 characters. 
#
noVar:
        addi    $t0, $t0, 12
        lb      $s0, inArr($t0)

        bne     $s0, ',', noVar

        lw      $s1, inArr+20($t0)
        b       chkVar

        # more checks for '#' for the end of inArr should be included


	# Clear the array
    	li	$t0, 0		# index
    	li	$t1, 40		# max
    	la	$t2, inArr	# inArr

        jal     dumpSymTab
        jal     clearInArr

        b       inLoop



#
# Save from keyboard to inArr table
#
getTokens:
	# Print out prompt & take user input of a string. Store store in input array.
    	la  	$a0, prompt   	# Loads addr of prompt_input into $a0
    	li  	$v0, 4          # Code 4 means output string.
    	syscall

    	la  	$a0, inArr      # Loads the address of input into $a0
    	li  	$a1, 40         # Buffer is 40 bytes long.
    	li  	$v0, 8          # Code 8 means input a string.
    	syscall


#
# getLabel: Label is found, save it in symTab
#
getLabel:



#
# getVar: Variable is found, save it in symTab
#
getVar:



#
# dumpSymTab: Print the symTab array to the screen.
#
dumpSymTab:



#
# clearInArr
#
clearInArr:
	beq	$t0, $t1, main		# done clearing
	beq	$t1, $0, main		# Seems need to end early.

	sb 	$0, 0($t2)     		# Put a null throughout the array

	addi    $t0, $t0, 4     	# Move the output
        addi	$t2, $t2, 4
        b clearInArr
