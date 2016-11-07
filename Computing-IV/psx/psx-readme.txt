ps1

The only changes I made to this assignment were:

1. Fixed the one point I lost - that I did not read both a depth and size arg
   for the original project. I now read both depth and size, and the original
   project adjusts the image to the window size by setting the position
   relative to the window size.

2. Made any changes cpplint requested, including but not limited to:
   - Changing bracket placements (no new lines for them)
   - removing extra spaces, such as _depth: (depth) becomes _depth:(depth)
   - added extra spaces after if / else statements, like if (something == true)
   - making sure lines are less than 80 characters long
   - removed using namespace std
   - not using c style casts
   - and more stuff I can't remember