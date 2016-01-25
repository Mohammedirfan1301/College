0:mar := pc; rd;                                    { main loop }
1:pc := 1 + pc; rd;                                 { increment pc }
2:ir := mbr; if n then goto 28;                     { save, decode mbr }
3:tir := lshift(ir + ir); if n then goto 19;
4:tir := lshift(tir); if n then goto 11;            { 000x or 001x? }
5:alu := tir; if n then goto 9;                     { 0000 or 0001? }
6:mar := ir; rd;                                    { 0000 = LODD }
7:rd;
8:ac := mbr; goto 0;
9:mar := ir; mbr := ac; wr;                         { 0001 = STOD }
10:wr; goto 0;
11:alu := tir; if n then goto 15;                   { 0010 or 0011? }
12:mar := ir; rd;                                   { 0010 = ADDD }
13:rd;
14:ac := ac + mbr; goto 0;
15:mar := ir; rd;                                   { 0011 = SUBD }
16:ac := 1 + ac; rd;                                { Note: x - y = x + 1 + not y }
17:a := inv(mbr);
18:ac := a + ac; goto 0;
19:tir := lshift(tir); if n then goto 25;           { 010x or 011x? }
20:alu := tir; if n then goto 23;                   { 0100 or 0101? }
21:alu := ac; if n then goto 0;                     { 0100 = JPOS }
22:pc := band(ir, amask); goto 0;                   { perform the jump }
23:alu := ac; if z then goto 22;                    { 0101 = JZER }
24:goto 0;                                          { jump failed }
25:alu := tir; if n then goto 27;                   { 0110 or 0111? }
26:pc := band(ir, amask); goto 0;                   { 0110 = JUMP }
27:ac := band(ir, amask); goto 0;                   { 0111 = LOCO }
28:tir := lshift(ir + ir); if n then goto 40;       { 10xx or 11xx? }
29:tir := lshift(tir); if n then goto 35;           { 100x or 101x? }
30:alu := tir; if n then goto 33;                   { 1000 or 1001? }
31:a := sp + ir;                                    { 1000 = LODL }
32:mar := a; rd; goto 7;
33:a := sp + ir;                                    { 1001 = STOL }
34:mar := a; mbr := ac; wr; goto 10;
35:alu := tir; if n then goto 38;                   { 1010 or 1011? }
36:a := sp + ir;                                    { 1010 = ADDL }
37:mar := a; rd; goto 13;
38:a := sp + ir;                                    { 1011 = SUBL }
39:mar := a; rd; goto 16;
40:tir := lshift(tir); if n then goto 46;           { 110x or 111x? }
41:alu := tir; if n then goto 44;                   { 1100 or 1101? }
42:alu := ac; if n then goto 22;                    { 1100 = JNEG }
43:goto 0;
44:alu := ac; if z then goto 0;                     { 1101 = JNZE }
45:pc := band(ir, amask); goto 0;
46:tir := lshift(tir); if n then goto 50;
47:sp := sp + (-1);                                 { 1110 = CALL }
48:mar := sp; mbr := pc; wr;
49:pc := band(ir, amask); wr; goto 0;
50:tir := lshift(tir); if n then goto 65;           { 1111, examine addr }
51:tir := lshift(tir); if n then goto 59;
52:alu := tir; if n then goto 56;
53:mar := ac; rd;                                   { 1111000 = PSHI }
54:sp := sp + (-1); rd;
55:mar := sp; wr; goto 10;
56:mar := sp; sp := sp + 1; rd;                     { 1111001 = POPI }
57:rd;
58:mar := ac; wr; goto 10;
59:alu := tir; if n then goto 62;
60:sp := sp + (-1);                                 { 1111010 = PUSH }
61:mar := sp; mbr := ac; wr; goto 10;
62:mar := sp; sp := sp + 1; rd;                     { 1111011 = POP }
63:rd;
64:ac := mbr; goto 0;
65:tir := lshift(tir); if n then goto 73;
66:alu := tir; if n then goto 70;
67:mar := sp; sp := sp + 1; rd;                     { 1111100 = RETN }
68:rd;
69:pc := mbr; goto 0;
70:a := ac;                                         { 1111101 = SWAP }
71:ac := sp;
72:sp := a; goto 0;
73:alu := tir; if n then goto 76;
74:a := band(ir, smask);                            { 1111110 = INSP }
75:sp := sp + a; goto 0;
76:tir := tir + tir; if n then goto 80;
77:a := band(ir, smask);                            { 11111110 = DESP }
78:a := inv(a);
79:a := a + 1; goto 75;
80:tir := tir + tir; if n then goto 115;        { if 1111 1111 1x goto line 150 }
81:alu := tir + tir; if n then goto 108;        { else if 1111 1111 01 goto line 130 }
82:a := 0;                                      { else 1111 1111 00 = MULT }
83:a := lshift(1);                              { get "MMM MMM" value into B }
84:a := lshift(a + 1);                          { similar to RSHIFT, but RSHIFT is 4 bits or SSSS }
85:a := lshift(a + 1);                          { and MULT is MMM MMM }
86:a := lshift(a + 1);                          { so we need to make a 6 bit mask to get }
87:a := lshift(a + 1);                          { the MMM MMM value at the end }
88:a := a + 1;                                  { basically 6 bits of 1 - or 111 111 }
89:b := band(ir, a);                            { B now holds "MMM MMM" value to mult by.}
90:mar := sp; rd;                               { need to get the top of the stack now. }
91:rd;                                          { need to read twice }
92:c := mbr;                                    { stack value is now in C }
93:d := 0;                                      { start result at 0 (D will hold final value) }
94:alu := b; if z then goto 100;                { if mult. by zero, we're done as D is 0 by default }
95:d := c + d;                                  { result = stack value + result (one round of mult.) }
96:alu := c; if n then goto 104;                { if the orig. number is NEGATIVE, check if it overflowed }
97:alu := d; if n then goto 103;                { if the orig. number is NOT neg, check if it overflowed }
98:b := b + (-1); if z then goto 100;           { check to see if we're done adding (when B = 0) }
99:goto 95;                                     { continue looping (lines 95 to 99) }
100:ac := 0;                                    { MULT was success, so AC = 0 }
101:mar := sp; mbr := d; wr;                    { write result to stack }
102:wr; goto 0;                                 { write twice and goto beg. of loop }
103:ac := -1; goto 0;                           { MULT overflowed, so AC = -1 & goto beg. of loop }
104:e := inv(d);                                { take original negative number, inverse it and add 1 }
105:e := e + 1;                                 { this way we can really see if it overflowed }
106:alu := e; if n then goto 103;               { check to see if negative number overflowed }
107:goto 98;        { not overflow, continue looping (at the end of the loop - NOT THE BEGINNING) }
108:a := lshift(1);                             { 1111 1111 01 = RSHIFT }
109:a := lshift(a + 1);                         { this is from Prof. Maloney's help directory }
110:a := lshift(a + 1);  { URL: http://www.cs.uml.edu/~bill/cs305/assignment_4_help_dir/promfile_nand_rshift.txt }
111:a := a + 1;
112:b := band(ir, a);
113:b := b + (-1); if n then goto 137;
114:ac := rshift(ac); goto 135;
115:alu := tir + tir; if n then goto 170;             { if 1111 1111 11 goto line 200 (HALT) }
116:mar := sp; f := sp + 1; rd;                       { else 1111 1111 10 = DIV }
117:rd;                                               { read SP+1. Remember to read twice. }
118:b := mbr;                                         { store SP+1 (divisor) into B }
119:mar := sp; f := sp + 1; rd;                       { read SP. }
120:rd;                                               { Remember to read twice. }
121:a := mbr;                                         { store SP (dividend) into A }
122:d := 0;                                           { start the remainder at 0 }
123:e := 0;                                           { counter (e) starts at 0 }
124:c := inv(b);      { make C negative so we can do subtraction by doing addition }
125:c := c + 1;       { add 1 to inverse to get negative }
126:alu := a; if n then goto 159;     { zero case, if dividend is zero, then result should be zero. }
127:d := a + c;                       { subtract the divisor from A (dividend). }
128:alu := d; if z then goto 160;     { if the remainder hits 0, we're done! }
129:alu := d; if n then goto 150;     { if the remainder hits negative, almost done. }
130:goto 160;                         { keep looping until remainder is 0 or negative. }
131:goto 0;
132:goto 0;
133:goto 0;
134:goto 0;                         { Other cases can go here }
135:goto 0;                         { Things to deal with include: }
136:goto 0;                         { 0 dividend }
137:goto 0;                         { Negative divisor / positive dividend }
138:goto 0;                         { Positive divisor / negative dividend }
139:goto 0;                         { Negative divisor and negative dividend }
140:goto 0;
141:goto 0;
142:goto 0;
143:goto 0;
144:goto 0;
145:goto 0;
146:goto 0;
147:goto 0;
148:goto 0;
149:goto 0;
150:d := inv(d);                    { since the remainder is negative, make it positive }
151:d := d + 1;                     { by flipping the bits / adding 1. }
152:goto 160;                       { now we're done! }
153:goto 0;
154:goto 0;
155:goto 0;
156:goto 0;
157:goto 0;
158:goto 0;
159:d := 0;                         { make quotient 0 }
160:sp := sp + (-1);                { move stack ptr back one }
161:mar := sp; mbr := e; wr;        { push remainder onto stack }
162:wr;                             { write twice! }
163:sp := sp + (-1);                { move stack ptr back one }
164:mar := sp; mbr := d; wr;        { push quotient onto stack }
165:wr; goto 0;                     { write twice! also return to beg. of loop }
166:goto 0;
167:goto 0;
168:goto 0;
169:goto 0;
170:rd; wr;                                          { 1111 1111 11 = HALT }
