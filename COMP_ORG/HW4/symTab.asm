

                        .data
inArr:              .word     0:40
symTab:         .word     0:40
prompt:         .asciiz     "Enter new set of tokens and types"
LOC:              .word      0


        .text
main:
        li         $t0,0x0400
        sw      $t0, LOC

inLoop:
        jal     getTokens

        li      $t9, 0      # DEFN
        li      $t0, 0      # index to inArr

        lb      $s0, inArr+12($t0)
        bne   $s0, ':', operator

        jal     getLabel

operator:
        lb      $s0, ','
        lw     $s1, inArr+20($t0)

chkVar:
        bne     $s1, 0x32, noVar
        # found a variable
        # save the var and LOC into symTab
        jal     getVar


noVar:
        addi      $t0, $t0, 12
        lb          $s0, inArr($t0)

        bne       $s0, ',', noVar

        lw          $s1, inArr+20($t0)
        b           chkVar

        # more checks for '#' for the end of inArr should be included


        jal     dumpSymTab
        jal     clearInArr

        b       inLoop



#
# Save from keyboard to inArr table
#
getTokens:



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

