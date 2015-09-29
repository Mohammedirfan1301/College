main:
    LODD i:
    SUBD c100:
    JPOS done:
collatzUseqUentry:
    LODD i:
    STOD n:
collatzUseq:
    HALT
    SUBD c1:
    JZER zspot:
    JPOS collatzUseqUbody:
zspot:
    JUMP end:
collatzUseqUbody:
    LODD n:
    STOD m:
    SUBD c2:
    JNEG returnU1:
    LODD c0:
    STOD count:
divideUtop:
    LODD n:
    JZER returnUcount:
    JPOS divideUloopUbody:
zspot2:
    LODD m:
    ADDD m:
    ADDD m:
    ADDD c1:
    JUMP collatzUafterUcall:
divideUloopUbody:
    SUBD c2:     ; AC = n:
    STOD n:
    LODD count:
    ADDD c1:
    STOD count:
    JUMP divideUtop:
returnUcount:
    LODD count:
    JUMP collatzUafterUcall:
returnU1:
    LODD c1:
    JUMP collatzUafterUcall:
collatzUafterUcall:
    STOD n:
    JUMP collatzUseq:
end:
    LODD i:
    ADDD c1:
    STOD i:
    JUMP main:
done:
    HALT
    .LOC 1000
i:  0
m:  -1
n:      -1
count:  -1
c100:  25
c0:  0
c1:  1
c2:  2
