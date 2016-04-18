; Jason Downing
; Assignment 5
; Used Moloney's /~bill/cs305/ directory for help.

;  Main loop
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
            jzer printAns:          ; When done, print the answer.
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

; Print answer function.
printAns:   pop                     ; Get result into AC
            jneg done:              ; if negative we're done!
            stod 4094               ; store AC into output buffer
            call xbsywt:            ; print result
            jump printAns:          ; print the next result.

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

rangeStr:  "Enter an integer between 1 and 32767: "   ;; Output strings
sumStr:    "The sum of these numbers is:"
errorStr:  "Overflow, no sum possible!"
neg1:       -1        ;; constant -1
zero:        0        ;; constant  0
one:         1        ;; constant  1
ascii:      48        ;; constant 48 (ASCII value for 0)
c255:      255        ;; constant 255
nextChar:    0        ;; next char
binarynum:   0        ;; binary number
sum:         0        ;; Sum variable
count:       0        ;; Counter
str:         0        ;; String ptr
on:          8        ;; Start transmitter
mask:       10        ;; Mask
nl:         10        ;; ASCII value of Newline (nl)
cr:         13        ;; ASCII value of Carriage Return (cr)
