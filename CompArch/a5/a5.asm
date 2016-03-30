; Jason Downing
; Assignment 5
; Used Moloney's /~bill/cs305/ directory for help.

; *******************************************************
;  Main loop and functions
; *******************************************************

AddInput:   lodd on:                ; Starting value of 8.
            stod 4095               ; Transmitter address
            call xbsywt:            ; Receiver function call.

            ; First number input
            loco rangeStr:          ; Load "Enter an int" string
            call nextw:             ; Print out string
            call getInput:          ; Get input from the user
            lodd binarynum:         ; Load binary number
            stod sum:               ; Save the sum

            ; Second number input
            loco rangeStr:          ; Load "Enter an int" string
            call nextw:             ; Print out string
            call getInput:          ; Get input
            lodd binarynum:         ; Load binary number
            addd sum:               ; Add the sum.
            stod sum:               ; Store the sum

            ; If sum went negative, we've overflowed.
            jneg OverFlow:          ; Overflow error.

            ; Output sum string / sum number
            loco sumStr:            ; Load summary string
            call nextw:             ; Print summary string
            call convert:           ; Convert / output answer
            lodd zero:              ; returns 0, no error.

            halt                    ; HALT DON'T CATCH FIRE

; Get input from the user.
getInput:   lodd on:                ; Transmitter on
            stod 4093               ; Address
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

; Overflow function
OverFlow:   loco errorStr:          ; load overflow error string.
            call nextw:             ; output to the screen
            lodd neg1:              ; put -1 into the AC
            halt                    ; HALT DON'T CATCH FIRE

; Convert function
convert:    lodd on:                ; Start transmitter
            stod 4095               ; Transmitter address
            lodd neg1:              ; load -1 into AC
            push                    ; push -1 onto stack
            lodd mask:              ; load mask into AC
            push                    ; push mask onto stack
            jump answer:            ; Jump to answer

; Loop for getting the answer
answer:     lodd sum:               ; Load answer into AC
            jzer output:            ; When done, print the answer.
            lodd mask:              ; Load mask
            push                    ; Push mask onto stack
            lodd sum:               ; Load answer into AC
            push                    ; Push answer onto stack
            div                     ; Divide the answer by the mask
            pop                     ; Get result into AC
            stod sum:               ; Store new value into answer
            pop                     ; Pop stack
            insp 2                  ; Clean up the stack
            addd ascii:             ; Convert to character by adding ASCII value of 0.
            push                    ; Push the AC onto stack
            jump answer:            ; Keep looping

; Output result function.
output:     pop                     ; Get result into AC
            jneg done:              ; if -1 we're done!
            stod 4094               ; store AC into output buffer
            call xbsywt:            ; print result
            jump output:            ; print the next result.

; *******************************************************
;  This code is from the help file location here:
;  http://www.cs.uml.edu/~bill/cs305/IO_str_and_echo.asm
; *******************************************************
nextw:      pshi                    ; Outputs a string that has been loaded.
            addd one:
            stod str:
            pop
            jzer crnl:              ; carriage return / newline function
            stod 4094               ; output buffer
            push
            subd c255:
            jneg crnl:              ; carriage return / newline function
            call sb:                ; calls the sb function to loco 8 and loop1.
            insp 1
            push
            call xbsywt:
            pop
            stod 4094               ; output buffer
            call xbsywt:
            lodd str:
            jump nextw:

; This function outputs a carriage return and newline.
crnl:       lodd cr:                ; carriage return
            stod 4094               ; write CR to output buffer
            call xbsywt:            ; output carriage return
            lodd nl:                ; newline
            stod 4094               ; write NL to output buffer
            call xbsywt:            ; output newline
            retn

; These are the transmitter / receiver functions for I/O
xbsywt:     lodd 4095               ; Transmitter address (output loop)
            subd mask:
            jneg xbsywt:
            retn

rbsywt:     lodd 4093               ; Receiver address (input loop)
            subd mask:
            jneg rbsywt:
            retn

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

finish:     lodl 1                  ; finished so return.
            retn

done:       retn                    ; Return function

; *******************************************************
;   Variables
; *******************************************************

; NOTE:
; 4092 = input buffer
; 4093 = receiver address
; 4094 = output buffer
; 4095 = transmitter address

nextChar:    0        ;; next char
binarynum:   0        ;; binary number
sum:         0        ;; Sum variable
count:       0        ;; Counter
str:         0        ;; String ptr
mask:       10        ;; Mask
on:          8        ;; Start transmitter
nl:         10        ;; ASCII value of Newline (nl)
cr:         13        ;; ASCII value of Carriage Return (cr)
neg1:       -1        ;; constant -1
zero:        0        ;; constant  0
one:         1        ;; constant  1
ascii:      48        ;; constant 48 (ASCII value for 0)
c255:      255        ;; constant 255
rangeStr:  "Enter an integer between 1 and 32767: "   ;; Output strings
sumStr:    "The sum of these numbers is:"
errorStr:  "Overflow, no sum possible!"
