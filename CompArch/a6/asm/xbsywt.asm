; These are the transmitter / receiver functions for I/O
xbsywt:     lodd 4095               ; Transmitter address (output loop)
            subd mask:
            jneg xbsywt:
            retn