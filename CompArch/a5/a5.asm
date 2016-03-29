; Jason Downing
; Assignment 5
; Used http://www.cs.uml.edu/~bill/cs305/IO_str_and_echo.asm for help.

AddInput:             ; Main loop.
  lodd start:         ; Starting value
  stod 4095           ; Start transmitter
  call xbsywt:        ; Receiver function call.
  loco rangeStr:      ; Load "Enter an int" string
  call nextw:         ; Print out string
  call input:         ; Get input
  lodd bin:           ; Load binary number
  stod sum:           ; Save the sum
  loco rangeStr:      ; Load "Enter an int" string
  call nextw:         ; Print out string
  call input:         ; Get input
  lodd bin:           ; Load binary number
  addd sum:           ; Add the sum.
  stod sum:           ; Store
  stod data:          ; Store
  jneg overflow:      ; Overflow error.
  loco sumStr:        ; Load summary string
  call nextw:         ; Print summary string
  call encode:        ; ???
  lodd zero:          ; returns 0
  halt

overflow:             ; overflow function
  loco errorStr:      ; load overflow error string.
  call nextw:         ; output to the screen
  lodd negone:        ; put -1 into the AC
  halt

input:                ; Get input?
  lodd start:
  stod 4093
  call rbsywt:
  lodd 4092
  subd numset:
  push

loop:                 ; Loop?
  call rbsywt:
  lodd 4092
  stod next:
  subd nl:
  jzer endnum:
  mult 10
  lodd next:
  subd numset:
  addl 0
  stol 0
  jump loop:

endnum:               ; Last number?
  pop
  stod bin:
  lodd 4092
  loco 0
  retn

encode:               ; encode and loop for all chars
  lodd start:
  stod 4095
  lodd negone:
  push
  lodd mask:
  push

loop2:                ; Second loop.
  lodd data:
  jzer output:
  lodd mask:
  push
  lodd data:
  push
  div                 ; divide.
  pop
  stod data:
  pop
  insp 2
  addd numset:
  push
  jump loop2:

output:               ; Output a number.
  pop
  jneg done:          ; returns, done = retn
  stod 4094
  call xbsywt:
  jump output:

; *******************************************************
; This code is from the help file location here:
; http://www.cs.uml.edu/~bill/cs305/IO_str_and_echo.asm
; *******************************************************
nextw:      pshi                ; Outputs a string that has been loaded.
            addd one:
            stod str:
            pop
            jzer crnl:          ; carriage return / newline function
            stod 4094
            push
            subd c255:
            jneg crnl:          ; carriage return / newline function
            call sb:            ; calls the sb function to loco 8
            insp 1
            push
            call xbsywt:
            pop
            stod 4094
            call xbsywt:
            lodd str:
            jump nextw:

; This function outputs a carriage return and newline.
crnl:       lodd cr:            ; carriage return
            stod 4094           ; 4094 is where the CR is written
            call xbsywt:        ; output carriage return
            lodd nl:            ; newline
            stod 4094           ; 4094 is where the NR is written
            call xbsywt:        ; output newline
            retn

xbsywt:     lodd 4095           ; Transmitter (output loop)
            subd mask:
            jneg xbsywt:
            retn

rbsywt:     lodd 4093           ; Receiver (input loop)
            subd mask:
            jneg rbsywt:
            retn

sb:         loco 8              ; SB function

loop1:      jzer finish:        ; Check to see if we're done.
            subd one:
            stod count:
            lodl 1
            jneg add1:
            addl 1
            stol 1
            lodd count:
            jump loop1:

add1:       addl 1              ; Add 1 to counters
            addd one:
            stol 1
            lodd count:
            jump loop1:

finish:     lodl 1              ; finished so return.
            retn

; Not sure if this is needed.
done:       retn        ; Return function

; Variables down here.
next:        0
bin:         0        ;; Binary number
sum:         0        ;; Sum variable
data:        0
count:       0
str:         0
mask:       10        ;; Mask
start:       8        ;; Start transmitter
nl:         10        ;; Newline
cr:         13        ;; Carriage Return
negone:     -1        ;; constant -1
zero:        0        ;; constant  0
one:         1        ;; constant  1
numset:     48        ;; constant 48
c255:      255        ;; constant 255
rangeStr:  "Enter an integer between 1 and 32767: "
sumStr:    "The sum of these numbers is:"
errorStr:  "Overflow, no sum possible!"
