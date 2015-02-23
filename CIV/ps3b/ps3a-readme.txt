/**********************************************************************
 *  N-Body README
 **********************************************************************/

Name:   Jason Downing
OS:     Xubuntu 14.04LTS 64bit
Machine: ASUS Laptop / Custom built Desktop (Intel/Nvidia PCs)
Text editor:  Kate Text Editor (KDE editor)
Hours to complete assignment:  ~5 hours or so. Probably more. I lost track at some point.

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
1. Displays the planets in an SFML window. I first checked this manually.
   (I left my manual code in, as comments for future reference)

2. Reads input from a file, by using the < operator on a text file
   Ex: ./NBody < planets.txt
   I used cin to do this, so technically someone could just type all these
   commands out by hand. (that would be lame though!)

3. To do the above, I overloaded the >> operator.
   I also overloaded the << operator for debug output.
   (just like we did for the last program - ps2b)
   Both operators are pretty similar - they just use an ostream or an istream
   to redirect input. For the operator << it is an ostream that makes it possible
   to just call cout << obj and have all the values inside of the object be outputted
   to the screen or a file or w/e. The >> operator works similarly, but uses an istream
   to take input from stdin (cin in this case) and redirect that input into the member
   variables of the object. Examples:

   cin >> c_body;
   // inside the >> operator, I then do:
   input >> c_body._mass;
   input >> c_body._pos_x;
   etc

   For outputting to standard IO I just do:
   cout << c_body;
   // which inside of the << operator:
   output << c_body._mass;
   output << c_body.pos_x;
   etc

4. I also created methods for setting the radius and x / y positions.
   I made sure to convert the huge numbers (something * 10 ^ 11!)
   to workable numbers by dividing by the universe radius. This got me a
   ratio and I then multiplied that ratio by half the window height or side
   to get an SFML coordinate. From here, I adjusted for the SFML coordinate
   system using 0,0 as the upper left corner. Adding half the height or side
   of the given window lets me adjust the positions of the planets.
   (please see the huge comment block in body.cpp for more details)

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
  None (besides any code that was given during lectures).

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/
  No major problems! Yay!

/**********************************************************************
 *  List any other comments here.
 **********************************************************************/
  My code is really well commented, so it should be easy to see
  how and why I did most things.
