# NOT MY PROGRAM BUT ONE I FOUND TO TEST WITH
# THIS SHOULD JUST LOOP THROUGH AN ARRAY AND FIND ITS LENGTH.
        
        .data
str:    .asciiz "abcde"

tabchar:.asciiz " 5#6(4)4*3+3,4-3.4/3"

output:	.space	20

        .text
main:
        li      $s0, 0          # len = 1
        la      $s1, str        # s = str
        
test:
        lb      $s2, 0($s1)     # c = *s
        
        # Save c into output
        sb	$s2, output
        
        beqz    $s2, done       # if c = '\0', branch to "done"
        addi    $s0, $s0, 1     # len = len + 1
        addi    $s1, $s1, 1     # s = s + 1
        j       test
        
done:
	j print

print:
	# Print out what the user typed in.
	la	$a0, output
	li	$v0, 4
	syscall
	
	# Exit the program.
       	li $v0, 10
	syscall