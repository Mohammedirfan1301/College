AddInput:             ; Main loop.
  lodd start:         ; Starting value
  stod 4095           ; load and start UART
  call xbsywt:        ; Receiver function call.
  loco rangeStr:      ; Load "Enter an int" string
  call reader:        ; Print out string
  call input:         ; Get input
  lodd bin:           ; ???
  stod sum:           ; Save the sum
  loco rangeStr:      ; Load "Enter an int" string
  call reader:        ; Print out string
  call input:         ; Get input
  lodd bin:           ; ???
  addd sum:           ; Add the sum.
  stod sum:           ; Store it
  stod data:          ; ???
  jneg overflow:      ; Overflow error.
  loco sumStr:        ; Load summary string
  call reader:        ; Print summary string
  call encode:        ; ???
  lodd zero:          ; returns 0
  halt

overflow:             ; Output overflow string.
  loco errorStr:
  call reader:
  lodd negone:        ; returns -1
  halt

reader:               ; Outputs a string that has been loaded.
  pshi
  addd one:
  stod str:
  pop
  jzer crnl:          ; carriage return / newline function
  stod 4094
  push
  subd c255:
  jneg crnl:          ; carriage return / newline function
  call sb:            ; does something important.
  insp 1
  push
  call xbsywt:
  pop
  stod 4094
  call xbsywt:
  lodd str:
  jump reader:

crnl:                 ; This function outputs a carriage return and newline.
  lodd cr:            ; carriage return
  stod 4094           ; 4094 is where the CR is written
  call xbsywt:        ; output carriage return
  lodd nl:            ; newline
  stod 4094           ; 4094 is where the NR is written
  call xbsywt:        ; output newline
  retn

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

sb:                   ; this appears to be important.
  loco 8

case:                 ; Check to see if we're done.
  jzer finish:
  subd one:
  stod count:
  lodl 1
  jneg increase:
  addl 1
  stol 1
  lodd count:
  jump case:

increase:             ; increase counters.
  addl 1
  addd one:
  stol 1
  lodd count:
  jump case:

finish:               ; DONE FINALLY.
  lodl 1
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

xbsywt:               ; Transmitter (output loop)
  lodd 4095
  subd mask:
  jneg xbsywt:
  retn

rbsywt:               ; Receiver (input loop)
  lodd 4093
  subd mask:
  jneg rbsywt:
  retn

done:      retn       ; Return function

; Variables down here.
next:        0
bin:         0
sum:         0
data:        0
count:       0
str:         0
mask:       10
start:       8
nl:         10        ;; Newline
cr:         13        ;; Carriage Return
negone:     -1        ;; constant -1
zero:        0        ;; constant  0
one:         1        ;; constant  1
numset:     48
c255:      255
rangeStr:  "Enter an integer between 1 and 32767: "
sumStr:    "The sum of these numbers is:"
errorStr:  "Overflow, no sum possible!"
