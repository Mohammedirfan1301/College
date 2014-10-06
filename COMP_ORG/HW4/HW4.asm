# 
# 

                 .data
inArr:           .word     0:40
symTab:          .word     0:40
prompt:          .asciiz   "Enter new set of tokens and types: "
LOC:             .word     0

        .text
main:
        li      $t0,0x0400
        sw      $t0, LOC

inLoop:
        jal     getTokens

        li      $t9, 0      # DEFN
        li      $t0, 0      # index to inArr

        lb      $s0, inArr+12($t0)
        bne   	$s0, ':', operator

        jal     getLabel

operator:
        lb      $s0, ','
        lw     	$s1, inArr+20($t0)

chkVar:
        bne     $s1, 0x32, noVar
        # found a variable
        # save the var and LOC into symTab
        jal     getVar


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
# getVar:
#
getVar:



#
# dumpSymTab
#
dumpSymTab:



#
# clearInArr
#
clearInArr:
	beq	$t0, $t1, main		# done clearing

	sb 	$0, 0($t2)     		# Put a null throughout the array

	addi    $t0, $t0, 4     	# Move the output
        addi	$t2, $t2, 4
        b clearInArr