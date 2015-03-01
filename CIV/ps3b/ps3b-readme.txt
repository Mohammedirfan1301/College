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

  I should probably do this for fun.

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
