; Jason Downing
; Assignment 5
; Used Moloney's /~bill/cs305/ directory for help.

AddInput:   lodd on:                ; Starting value of 8.
            stod 4095               ; Transmitter address
            call xbsywt:            ; Receiver function call.

            loco rangeStr:          ; Load "Enter an int" string
            call nextw:             ; Print out string
            call getInput:          ; Get input from the user
            lodd binarynum:         ; Load binary number
            stod sum:               ; Save the sum

            loco rangeStr:          ; Load "Enter an int" string
            call nextw:             ; Print out string
            call getInput:          ; Get input

            lodd binarynum:         ; Load binary number
            addd sum:               ; Add the sum.
            stod sum:               ; Store sum
            stod data:              ; Store sum into data as well.

            jneg OverFlow:          ; Overflow error.

            loco sumStr:            ; Load summary string
            call nextw:             ; Print summary string
            call convert:           ; Convert answer
            lodd zero:              ; returns 0, no error.

            halt                    ; HALT DON'T CATCH FIRE

; Overflow function
OverFlow:   loco errorStr:          ; load overflow error string.
            call nextw:             ; output to the screen
            lodd negone:            ; put -1 into the AC
            halt                    ; HALT DON'T CATCH FIRE

; Get input from the user.
getInput:   lodd on:                ; Transmitter on
            stod 4093               ; Address
            call rbsywt:            ; Call transmitter
            lodd 4092               ; Get first digit
            subd numset:            ; Subtract 48
            push                    ; Push to stack

; Get Digits loop
getDigit:   call rbsywt:            ; Call transmitter
            lodd 4092               ; get next digit
            stod next:              ; store it in next
            subd nl:                ; Subtract 10 to see if the NL char was entered.
            jzer endnum:            ; NL char was entered, so done!
            mult 10                 ; multiply value on stack by 10.
            lodd next:              ; Load ASCII for next digit
            subd numset:            ; Subtract 48
            addl 0                  ; Add the multiplied value to the AC
            stol 0                  ; Store the sum on the stack
            jump getDigit:          ; Keep looping til we've got all the digits.

; We're done, so save the number.
endnum:     pop                     ; Get the number
            stod binarynum:         ; Store it in the binary number var
            lodd 4092               ; Load the receiver
            loco 0
            retn                    ; Done so return.

; Convert function
convert:    lodd on:                ; Start transmitter
            stod 4095               ; Transmitter address
            lodd negone:            ; load -1 into AC
            push                    ; push -1 onto stack
            lodd mask:              ; load mask into AC
            push                    ; push mask onto stack

; Loop for getting the answer
answer:     lodd data:              ; Load answer into AC
            jzer output:            ; When done, print the answer.
            lodd mask:              ; Load mask
            push                    ; Push mask onto stack
            lodd data:              ; Load answer into AC
            push                    ; Push answer onto stack
            div                     ; Divide the answer by the mask
            pop                     ; Get result into AC
            stod data:              ; Store new value into answer
            pop                     ; Pop stack
            insp 2                  ; Clean up the stack
            addd numset:            ; Convert to character.
            push                    ; Push the AC onto stack
            jump answer:            ; Keep looping

; Output result function.
output:     pop                     ; Get result into AC
            jneg done:              ; if -1 we're done!
            stod 4094               ; store AC into register
            call xbsywt:            ; print result
            jump output:            ; print the next result.

; *******************************************************
; This code is from the help file location here:
; http://www.cs.uml.edu/~bill/cs305/IO_str_and_echo.asm
; *******************************************************
nextw:      pshi                    ; Outputs a string that has been loaded.
            addd one:
            stod str:
            pop
            jzer crnl:              ; carriage return / newline function
            stod 4094
            push
            subd c255:
            jneg crnl:              ; carriage return / newline function
            call sb:                ; calls the sb function to loco 8
            insp 1
            push
            call xbsywt:
            pop
            stod 4094
            call xbsywt:
            lodd str:
            jump nextw:

; This function outputs a carriage return and newline.
crnl:       lodd cr:                ; carriage return
            stod 4094               ; 4094 is where the CR is written
            call xbsywt:            ; output carriage return
            lodd nl:                ; newline
            stod 4094               ; 4094 is where the NR is written
            call xbsywt:            ; output newline
            retn

xbsywt:     lodd 4095               ; Transmitter (output loop)
            subd mask:
            jneg xbsywt:
            retn

rbsywt:     lodd 4093               ; Receiver (input loop)
            subd mask:
            jneg rbsywt:
            retn

sb:         loco 8                  ; SB function

loop1:      jzer finish:            ; Check to see if we're done.
            subd one:
            stod count:
            lodl 1
            jneg add1:
            addl 1
            stol 1
            lodd count:
            jump loop1:

add1:       addl 1                  ; Add 1 to counters
            addd one:
            stol 1
            lodd count:
            jump loop1:

finish:     lodl 1                  ; finished so return.
            retn

done:       retn                    ; Return function

; Variables down here.
next:        0        ;; next char
binarynum:   0        ;; binary number
sum:         0        ;; Sum variable
data:        0        ;; Data variable
count:       0        ;; Counter
str:         0        ;; String ptr
mask:       10        ;; Mask
on:          8        ;; Start transmitter
nl:         10        ;; Newline
cr:         13        ;; Carriage Return
negone:     -1        ;; constant -1
zero:        0        ;; constant  0
one:         1        ;; constant  1
numset:     48        ;; constant 48
c255:      255        ;; constant 255
rangeStr:  "Enter an integer between 1 and 32767: "   ;; Output strings
sumStr:    "The sum of these numbers is:"
errorStr:  "Overflow, no sum possible!"
