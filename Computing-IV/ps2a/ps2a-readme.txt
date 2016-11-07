*************************************************
* Name                                          *
*************************************************
Jason Downing
2/9/2015

*************************************************
* Explanation                                   *
*************************************************
I used strings for the register bits. It works because
C++ strings are simple to use - easy to set the seed,
and to access specific bits of the string you can just
use [] operators. For modifying the strings - that is,
shifting all the bits in the register left, I used a for
loop and a stringstream to redirect all the bits left once,
except for the last bit, which I XORed like the Princeton
website explained - left most bit with the tap position.


*************************************************
* Discussion                                    *
*************************************************
My first additional test pretty much tests what
the Princeton site gave as examples. I figured if my
code passes all their examples, then it should be pretty
much set to pass other tests.

Which for my second test I tried edge cases on the constructor
and << operator. Both the tiniest seed (1 bit) and a huge seed
(30 bits) are saved and output correctly. I a stringstream here
as well to catch the string that is operator by the << operator.

