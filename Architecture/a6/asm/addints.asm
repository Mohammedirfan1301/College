; SB falls through to the loop1 loop.
sb:         loco 8                  ; SB function

loop1:      jzer finish:            ; Loop until finished
            subd one:
            stod count:
            lodl 1
            jneg add1:
            addl 1
            stol 1
            lodd count:
            jump loop1:

add1:       addl 1
            addd one:
            stol 1
            lodd count:
            jump loop1:
