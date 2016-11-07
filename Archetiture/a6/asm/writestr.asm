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
