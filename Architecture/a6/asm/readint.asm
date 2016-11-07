; Get input from the user.
getInput:   lodd on:                ; Receiver on
            stod 4093               ; Receiver Address
            call rbsywt:            ; Call transmitter
            lodd 4092               ; Get first digit from input buffer
            subd ascii:             ; Subtract 48 (ASCII value of 0)
            push                    ; Push to stack

; Get Digits loop
getDigit:   call rbsywt:            ; Call transmitter
            lodd 4092               ; get next digit from input buffer
            stod nextChar:          ; store it in next
            subd nl:                ; Subtract 10 to see if the NL char was entered.
            jzer lastNum:           ; NL char was entered, so done!
            mult 10                 ; multiply value on stack by 10.
            lodd nextChar:          ; Load ASCII for next digit
            subd ascii:             ; Subtract 48
            addl 0                  ; Add the multiplied value to the AC
            stol 0                  ; Store the sum on the stack
            jump getDigit:          ; Keep looping until we've got all the digits.

; We're done, so save the number.
lastNum:    pop                     ; Get the number
            stod binarynum:         ; Store it in the binary number var
            lodd 4092               ; Load the input buffer
            loco 0
            retn                    ; Done so return.
