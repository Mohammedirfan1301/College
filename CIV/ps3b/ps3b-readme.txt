/**********************************************************************
 *  N-Body README
 **********************************************************************/

Name:   Jason Downing
OS:     Xubuntu 14.04LTS 64bit
Machine: ASUS Laptop / Custom built Desktop (Intel/Nvidia PCs)
Text editor:  Kate Text Editor (KDE editor)
Hours to complete assignment:  ~5 hours or so. Probably more. I lost track at some point.

/**********************************************************************
 *  If you created your own universe for extra credit, describe it
 *  here and why it is interesting.
 **********************************************************************/

  I attempted to create a full simulation of the universe - that is,
  all the planets rotating around the sun in a somewhat realistic way.
  I ended up only being able to get Jupiter and Saturn working - if I added
  Uranus and Neptune, the scale got weird (due to the vast distances between
  planets) and sometimes Neptune and Uranus would just slingshot out of the
  solar system.

  I used the following sites to get my data

  Mass of the planets:
  http://www.smartconversion.com/otherInfo/Mass_of_planets_and_the_Sun.aspx

  Speed of the planets:
  http://www.sjsu.edu/faculty/watkins/orbital.htm

  Distance from the sun:
  http://idahoptv.org/ntti/nttilessons/lessons2000/lau1.html

  I used the following command to run my universe file:
  ./NBody 157788000.0 575000.0 < solarsystem.txt

  This makes the universe go pretty quick for the inside planents, but it
  shows Jupiter and Saturn remain in their orbits for the most part.

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
  None (besides any code that was given during lectures).

/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/
  This round I had tons of issues with simulating the universe.
  For some reason I kept getting NaN, -NaN, and my planets would just
  magically disappear after a few steps (due to the "NaN" numbers).
  Turns out NaN stands for "Not a Number" and is related to either
  dividing by 0, pow / squaring 0 or doing anything else that results in
  a unpredictable number. See this stackoverflow for more info:

  In my case - it turns out I had a very tiny bug in my input operator
  (<< operator). This piece of code is what was wrong:

  input >> cBody._vel_y >> cBody._vel_y;

  I was actually inputting the y velocity twice and NEVER setting the x velocity!
  So whenever I used the x velocity in my code, it was completely unpredictable
  what number would end up there. And since I pow / square / multiply the variables
  throughout my code, that unknown / not preset variable caused a bunch of problems
  in the simulation.

  Oh and I was also dumb and initally made my gravity constant this:
  667000000000

  Instead of the correct constant:
  6.67e-11;

  The only other issue I had was I tried to calculate the forces inside the
  body class because I thought it would work - until I realized it didn't
  since the force were member variables and never reset (although I could have
  made a reset forces function I guess...). In the end it made more sense to make
  a friend function which gets passed two body objects and calculates either the
  x or the y force and returns it.

/**********************************************************************
 *  List any other comments here.
 **********************************************************************/
  My code is really well commented, so it should be easy to see
  how and why I did most things.

  Also I did the following extra credit:

  1. Music plays (2001 Space Odyssey theme)
  2. Time displays in the top left hand corner
  3. I created my own universe