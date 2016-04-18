; We're done, so save the number.
lastNum:    pop                     ; Get the number
            stod binarynum:         ; Store it in the binary number var
            lodd 4092               ; Load the input buffer
            loco 0
            retn                    ; Done so return.
