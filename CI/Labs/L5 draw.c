#include <stdio.h>
#include <draw.h>
#include <math.h>

void square(int x, int y);

int main(int argc, char * argv[])
{
    int squares = 0;        //int to hold the number of blue/cyan squares to display
    int i = 0, x, y;               //ints for the while/loop for blue/cyan circles
    int across, vertical;   //ints for the grid lines
   
    //Take user input
    printf("How many squares should display in the blue/cyan row? ");
    scanf("%d", &squares);

    //  Start displaying the grid lines first!
    //  Then display the shapes!

    draw_begin();             //start drawing - this will last throughout the program until the draw_finish is called.
    draw_moveTo(0, 0);      //Start at 0, 0
    draw_lineTo(300, 0);    //draw the first HORIZONTAL line
   
    //Draw the grid lines across the screen
    for(across = 1; across <= 300; across++)
    {
        if( (across % 10) == 0) //if across can be divided evenly by 10, then draw the line!
        {
            draw_moveTo(0, across);         //move to the next line.
            draw_lineTo(300, across);       //draw 300 across
        }
    }
   
    //Start the first vertical line
    draw_moveTo(0,0);       //Start at x=0, y=0
    draw_lineTo(0, 300);    //Draw a vertical line at x=0 all the way to y=200
   
    //Draw the vertical grid lines
    for(vertical = 1; vertical <= 300; vertical++)
    {
        if( (vertical % 10) == 0) //if vertical can be divided evenly by 10, then draw the line!
        {
            draw_moveTo(vertical, 0);       //move to the next line.
            draw_lineTo(vertical, 300);     //draw 300 vertically
        }
    }
   
    draw_finish(0);             //stop drawing the grid lines
   
    //  Now start drawing the GREEN SQUARE (40x40 pixels)
    draw_begin();                   //Start dawing
    draw_moveTo(10,10);             //Move to 10,10 to start the square
    draw_setColor("green");         //Make the square GREEN
    draw_lineTo(10,50);             //Draw the first line across
    draw_lineTo(50,50);             //Draw down for the right hand line
    draw_lineTo(50,10);             //Draw back across for the bottom line
    draw_lineTo(10,10);             //Draw up to finish the square
    draw_finish(1);                 //Done, so finish with a 1 so it is filled in.
   
    //  Now start drawing the BLACK, OPEN CIRCLE (10 pi radius)
    draw_begin();               //Start drawing
    draw_setColor("black");     //Color set to BLACK
    draw_arc(100,           //x coord of the center
              40,           //y coord of the center
              30,           //radius, which is 30
               0,           //Start a 0 angle
               M_PI*2,      //Since a circle is 2pi, go to that angle for a complete circle
               0);          //Make it go clockwise
    draw_finish(0);         //do not fill the circle in

    //  Now start drawing the ORANGE HALF CIRCLE that overlaps the BLACK CIRCLE by 20 pixles
    draw_begin();               //start dawing
    draw_setColor("orange");    //draw the circle in ORANGE
    draw_arc(140,           //start at x = 140, which is 40 over from the black circle
              40,           //start at y = 40, the same y as the black circle
              30,           //radius of 30
               0,           //start at angle 0
               M_PI*1,      //a half circle is 1 pi
               1);          //go counter clockwise to make it upright
    draw_finish(1);         //fill the circle in.
   
    //  Now start drawing the BLUE HALF CIRCLE BASE.
    draw_begin();               //start drawing
    draw_setColor("blue");      //set color to blue
    draw_arc(200,               //start at x = 200, which is decently far from the orange circle
              40,               //start at y = 40, the same y as the black circle/orange circle
              30,               //radius of 30
               M_PI*.5,         //start at angle .5pi, to make the half center have a vertical base
               M_PI*1.5,        //a half circle is 1 pi, so go out to 1.5pi
               1);              //go counter clockwise to make it face right
    draw_finish(1);             //fill the circle in.
   
    //  Now start drawing the RED OPEN ISOSCELES TRIANGLE
    draw_begin();               //Start drawing
    draw_setColor("red");       //Make the color red
    draw_moveTo(250,40);        //Move 50 over from the blue half circle
    draw_lineTo(250,20);        //Draw up 20, starting the base
    draw_lineTo(300,40);        //Draw to the point of the triangle
    draw_lineTo(250,60);        //Draw back to the base of the triangle
    draw_lineTo(250,40);        //Draw to the end of the triangle
    draw_finish(0);             //FINISHED! so 0 for clear.
   
    //  NOW THE FUN PART! Time to use that use input we got waaay up top to make: 0 TO 10 BLUE/CYAN SQUARES!
    x = 10;
    y = 100;
    //i =  squares;
    draw_setColor("blue");
    i = 10;
    while(squares > 0)
    {
        if( (squares % 2) == 0)     //Covers the even numbers, which will be blue!
            square(x, y);
        else                        //everything else is BLUE!
            square(x, y);
            
        //MAKE SURE THAT THE FIRST SQUARE IS BLUE!
        if(i % 2 == 0)
            draw_setColor("cyan");
        else if(i % 2 != 0)
            draw_setColor("blue");
       
        x = x + 20;
        squares--;
        i--;
    }
   
    draw_setColor("grey");     //make sure the grid lines are BLACK.
    return 0;
}

void square(int x, int y)
{
    draw_begin();                   //Start dawing
    draw_moveTo(x, y);              //Move to 10,10 to start the square
    draw_lineTo(x,y+20);            //Draw the first line across
    draw_lineTo(x+20,y+20);         //Draw down for the right hand line
    draw_lineTo(x+20,y);            //Draw back across for the bottom line
    draw_lineTo(x,y);               //Draw up to finish the square
    draw_finish(1);                 //Done, so finish with a 1 so it is filled in.
}