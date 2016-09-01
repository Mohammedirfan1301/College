***********************************************************************
* Readme for PS1 - Sierpinski Triangle + Original Recusive Image      *
***********************************************************************

Name: Jason Downing

***************
* Discussion: *
***************
I built the Sierpinski Triangle (in red) and an original image that consists of circles
within circles, that randomly change between 19 different colors. The circles are all
separated by 10 radius, decreasing by 10 on each recusion, so that they appear within each other.
I had to set the origin of each circle to its radius (both x and y), since for some reason SFML
sets the default radius of circles to 0,0 - their upper left corner. Once you set the origin
correctly its pretty easy to center the circles using setPosition and then recusively decrement
the radius, so that all the circles appear inside of each other.

I used rand to randomize the colors along with a switch statement. I used all the default SFML colors
that I liked + I created an sf::Color object that can use Red Green Blue values to create custom
colors. For finding the colors, I used the following site:

http://www.rapidtables.com/web/color/RGB_Color.htm

The class reference for the sf::Color class was pretty useful too:

http://www.sfml-dev.org/documentation/2.0/classsf_1_1Color.php

I also uploaded a gif of the original image to imgur:

(5FPS version)
https://imgur.com/e3kgJPT

(60FPS version, lots of colors)
https://imgur.com/qeALOGf

The two screenshots in the directory:
Sierpinski.png - ran the following command: ./sierpinski 4 700
(depth 4, window size 700)

Original_Recusive_Image.png - ran using: ./original 35
(depth 35)

******************
* Memory Usage:  *
******************

The Sierpinski triangle uses quite a bit of RAM, as the recusion causes each increase in depth
to multiply quickly. This is because I set the triangle up using three Sierpinski pointers, which
are dynamically created for each depth.

At depth 1, there's just one object and 3 NULL pointers.
At depth 2, there's one object and 3 pointers to objects.
This multiplies pretty quick - depth 3 will have 12 pointers to objects, depth 4 will have 42, etc.

It ends up working like a binary tree in a way,

                                  Blank triangle
                                  /    |        \
                                ptr   ptr       ptr
                              /  | \ / | \     / | \
                             p   p p p p p    p  p  p
                            /|\/|\/|\|\|\|\  /|\/|\/|\
                                      etc

The program seems to use around 30-40MB of RAM until it hits a depth of 9 / 10.
It really hits 100MB of RAM around depth 12, and above 15 will probably slow down most PCs.
(I saw memory use hit 2GB at depth of 15, which I assume would have a huge number of objects being
drawn. Assuming 3 ^ 15, that would be 14,348,907 objects for just depth 15 - not including depths
14, 13, etc.)

Using valgrind, I find that the difference between depth 1 and 10 is roughly:

Depth  1:    10,343 allocations , 153,483,801 bytes allocated
Depth 10: 1,162,019 allocations , 254,089,870 bytes allocated

It seems each object would use very little RAM indiviually, but as I said, the number of objects
skyrockets after depth 10, so even though they use something tiny, like a few hundred / thousand
bytes for just one object, creating over a million objects will use at least 40MB of RAM.

**************************
* Time spent: ~10 hours? *
**************************

Several hours over the course of a few days. Getting the Sierpinski Triangle to work
took the longest. I'd estimate at least 5-6 hours to get that to work, plus some time
spent helping others with similar issues. The original work didn't take that long
once I figured out what I wanted to do. I originally tried to make squares that split into grids,
like this:

  -----------
  |--|-|--|-|
  |----|----|
  |--|-|--|-|
  -----------

The squares would continue to split, forming squares within squares. I couldn't quite get it to
work though, something in my formula was wrong so I settled on circles since they are a little
easier to work with. I just had to set the origin correctly and then set the position to the
center of the screen - after that I played around with colors, and made 19 different colors
and randomized it. All together that was probably another 5 or so hours spent playing around
with SFML and debugging code.