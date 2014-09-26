# Author: 	Jason Downing
#   Date:	9/14/2014

	.data					# Data portion of the program (variables, constants, etc)
prompt:	.asciiz "Enter the first integer: " 	# Load the first prompt into memory
prompt2:.asciiz	"Enter the second integer: "  	# Load the second prompt into memory
prompt3:.asciiz	"The result is: "		# Load the final result msg into memory

	.text		
main:	
	# Code 1 = print int. Code 4 = print string. Code 5 = get int. Code 10 = exit.

	# FIRST PROMPT
	la	$a0, prompt	# Get the address of the first message.
	li	$v0, 4		# Print the first prompt out. (Code 4)
	syscall			# Tell the OS to perform the above operation.
	
	# GET FIRST INT
	li 	$v0, 5		# Read the first int into $v0. (Code 5)
	syscall			# Tell the OS to perform the above operation.
	add	$t0, $v0, $0	# Add the first int that was entered into the $t0 register
	
	# SECOND PROMPT
	la	$a0, prompt2	# Get the addr of the 2nd message.
	li	$v0, 4		# Print the second prompt. (Code  4)
	syscall			# Tell the OS to perform the above operation.
	
	# GET SECOND INT
	li 	$v0, 5		# Read the second int into $t1. (Code 5)
	syscall			# Tell the OS to perform the above operation.
	add	$t1, $v0, $0	# Add the second int that was entered into the $t1 register
	
	# MULTIPLY THE TWO INTS
	mult 	$t0, $t1	# Multiply the two numbers.
	mfhi	$t2		# Store part of the result of the multiplication to the $t2 register.
	mflo	$t3		# Store the other part of the result into the $t3 register
	add	$t4, $t2, $t3	# Add the two parts into the $t4 register.
	
	# FINAL RESULT MESSAGE
	la 	$a0, prompt3	# Get the addr of the final prompt.
	li	$v0, 4		# Print the final prompt. (Code 4)
	syscall			# Tell the OS to perform the above operation.
	
	# PRINT PRODUCT
	li	$v0, 1		# Load the system code into $v0
	move	$a0, $t4	# Move the product into the $a0 to be printed.
	syscall			# Tell the OS to perform the above operation.
	
	# EXIT THE PROGRAM.
	li	$v0, 10		# Exit properly. (Code 10)
	syscall			# Tell the OS to perform the above operation.