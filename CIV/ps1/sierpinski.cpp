#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "sierpinski.hpp"

using namespace std;

/*

         _top
           .
          / \
         /   \
        /     \
    p1 .-------. p3
      / \     / \
     /   \   /   \
    /     \ /     \
   .-------.-------.
 _left    p2     _right

 The above is an ASCII representation of what this code does.
 We have _top, _left, _right member variables we use to
 to draw the triangle in the middle using p1/p2/p3

 */

// Constructor                              (Initialize private variables)
Sierpinski::Sierpinski(int depth, int side) : _depth (depth)
{
  // Initialize other member variables - top, left, right
  _top = sf::Vector2f(side / 2, 0);

  // Calculate the height using triangle geometry
  float height = .5 * sqrt(3.0) * (float) side;

  // Calculate left and right using the height.
  _left = sf::Vector2f(0, height);
  _right = sf::Vector2f(side-1, height);

  /* Call the constructor that accepts 3 points.
   * First find p1, p2, p3.
   * To do so, use the midpt formula:
   *
   * ( ( (x1 + x2) / 2) , ( (y1 + y2) / 2) )
   *
   */
  _p1 = sf::Vector2f( ((_top.x + _left.x) / 2), ((_top.y + _left.y) / 2) );
  _p2 = sf::Vector2f( ((_left.x + _right.x) / 2), ((_left.y + _right.y) / 2) );
  _p3 = sf::Vector2f( ((_top.x + _right.x) / 2), ((_top.y + _right.y) / 2) );

  if(_depth - 1 > 0)
  {
    // Now that we have the points, create 3 triangles
    _triangle1 = new Sierpinski(_p1, _left, _p2, depth - 1);
    _triangle2 = new Sierpinski(_top, _p1, _p3, depth - 1);
    _triangle3 = new Sierpinski(_p3, _p2, _right, depth - 1);
  }
  else{
    _triangle1 = NULL;
    _triangle2 = NULL;
    _triangle3 = NULL;
  }
}


Sierpinski::Sierpinski(sf::Vector2f top, sf::Vector2f left,
                       sf::Vector2f right, int depth) : _depth (depth)
{
  // End of the recurrsion.
  if(depth <= 0)
  {
    // Set the 3 triangle pointers to null
    _triangle1 = NULL;
    _triangle2 = NULL;
    _triangle3 = NULL;

    return;
  }

  // Set member variables - points of the triangle
  _top = top;
  _left = left;
  _right = right;

  // Set the filled triangle points - use midpoint formula
  _p1 = sf::Vector2f( ((top.x + left.x) / 2), ((top.y + left.y) / 2) );
  _p2 = sf::Vector2f( ((left.x + right.x) / 2), ((left.y + right.y) / 2) );
  _p3 = sf::Vector2f( ((top.x + right.x) / 2), ((top.y + right.y) / 2) );

  // Now that we have the points, create 3 triangles
  _triangle1 = new Sierpinski(_p1, left, _p2, depth - 1);
  _triangle2 = new Sierpinski(top, _p1, _p3, depth - 1);
  _triangle3 = new Sierpinski(_p3, _p2, right, depth - 1);
}


// Destructor
Sierpinski::~Sierpinski()
{
  // Need to destroy all the objects that were created
  if(_triangle1 != NULL)
  {
    // Recusively call the destructor
    delete _triangle1;
    delete _triangle2;
    delete _triangle3;
  }

  // After we clear the allocated objects, we don't have to worry about stuff allocated
  // on the stack since that will be handled automagically.
}


void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Check the beginning dimensions of the overall triangle
//   cout << "_depth is: " << _depth << endl;
//   cout << "_top is: (" << _top.x << ", " << _top.y << ") \n";
//   cout << "_left is (" << _left.x << ", " << _left.y << ") \n";
//   cout << "_right is (" << _right.x << ", " << _right.y << ") \n";

  // The outside triangle.
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, _left);
  triangle.setPoint(1, _right);
  triangle.setPoint(2, _top);

  // The filled upside down triangle.
  sf::ConvexShape triangle2;
  triangle2.setPointCount(3);
  triangle2.setPoint(0, _p1);
  triangle2.setPoint(1, _p2);
  triangle2.setPoint(2, _p3);
  triangle2.setFillColor(sf::Color::Red);

  // Draw the two triangles above.
  target.draw(triangle);

  // Make _depth just print out a blank triangle
  if(_depth > 0)
  {
    target.draw(triangle2);
  }

  if(_triangle1 != NULL)
  {
    _triangle1->draw(target, states);
    _triangle2->draw(target, states);
    _triangle3->draw(target, states);
  }
}
