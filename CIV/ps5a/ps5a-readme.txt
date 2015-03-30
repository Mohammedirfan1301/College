Name:   Jason Downing
OS:     Xubuntu 14.04LTS 64bit
Machine: ASUS Laptop / Custom built Desktop (Intel/Nvidia PCs)
Text editor:  Kate Text Editor (KDE editor)
Hours to complete assignment:  3-4 hours

1) I tested my implementation using a main function to move the Ring Buffer around
and test random edge cases and to also check the ring buffer itself by outputting
all the values inside the buffer. I also used Boost to check the Ring Buffer as
well, by again testing edge cases and cases of invalid input or invalid use of
various methods.

2) Exceptions that I used:

std::invalid_argument - for when negative numbers are passed to the constructor,
since the Ring Buffer can't be less then 1, so it can't be 0, -1, -2, etc.

std::runtime_error - for attempts to enqueue or dequeue past the capacity of
the Ring Buffer. You obviously can't add another number if the Ring Buffer is
full, and you can't remove numbers if the Ring Buffer is empty.

3) Space /  Time performance

I used a vector, which normally would probably impact space and time, as vectors
aren't quite as efficient as c arrays, but in the case of this assignment, the
ring buffer is a set size, so using the resize() method on the vector can make
the vector act like a c array - assuming you don't push back or change the size
of the vector.

The only other thing that would impact perfomance is the fact that vectors
keep track of size, capacity and other values internally, which is redundant
as I also keep track of size and capacity for the Ring Buffer. A c array would
save a few bytes, which can add up if we had say 1,000 Ring Buffers, but in the
case of just 1 ring buffer that's not much of an issue - a few bytes won't
change the space or time of the program by much.