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

// Constructor                               (Initialize private variables)
Sierpinski::Sierpinski(int depth, int side) : _depth (depth)
{
  // Initialize other member variables - top, left, right
  _top = sf::Vector2f(side / 2, 0);

  // Calculate the height using triangle geometry
  float height = .5 * sqrt(3.0) * (float) side;

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

  // Now that we have the points, create 3 triangles
  triangle1 = new Sierpinski(_p1, _left, _p2, depth - 1);
  triangle2 = new Sierpinski(_top, _p1, _p3, depth - 1);
  triangle3 = new Sierpinski(_p3, _p2, _right, depth - 1);
}


Sierpinski::Sierpinski(sf::Vector2f top, sf::Vector2f left,
                       sf::Vector2f right, int depth) : _depth (depth)
{
  // End of the recurrsion.
  if(_depth == 0)
  {
    // Set the 3 triangle pointers to null.
    triangle1 = NULL;
    triangle2 = NULL;
    triangle3 = NULL;

    return;
  }

  // Continue making new triangles until we've recursed the whole way to 0.
  _p1 = sf::Vector2f( ((_top.x + _left.x) / 2), ((_top.y + _left.y) / 2) );
  _p2 = sf::Vector2f( ((_left.x + _right.x) / 2), ((_left.y + _right.y) / 2) );
  _p3 = sf::Vector2f( ((_top.x + _right.x) / 2), ((_top.y + _right.y) / 2) );

  // Now that we have the points, create 3 triangles
  triangle1 = new Sierpinski(_p1, _left, _p2, depth - 1);
  triangle2 = new Sierpinski(_top, _p1, _p3, depth - 1);
  triangle3 = new Sierpinski(_p3, _p2, _right, depth - 1);
}


// Destructor
Sierpinski::~Sierpinski()
{
  // Would destroy any objects and stuff.
  // Nothing to destroy yet.
}


Sierpinski Sierpinski::get_triangle(int num)
{
  switch(num)
  {
    case 1:
          return *this->triangle1;
    case 2:
          return *this->triangle2;
    case 3:
          return *this->triangle3;
  }
  Sierpinski nothing(0, 0);
  return nothing;
}


void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  cout << "_depth is: " << _depth << endl;
  cout << "_top is: (" << _top.x << ", " << _top.y << ") \n";
  cout << "_left is (" << _left.x << ", " << _left.y << ") \n";
  cout << "_right is (" << _right.x << ", " << _right.y << ") \n";

  // Draw all the triangles
  // When they are NULL stop recursing.

  if(_depth == 0)
  {
    // Stop making ConvexShapes to draw.
    // Now just draw them all.

  }

  // This vector will hold all the triangles we want to draw.
  vector <sf::ConvexShape> triangles;

  // The outside triangle.
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, _left);
  triangle.setPoint(1, _right);
  triangle.setPoint(2, _top);
  triangle.setPosition(0, 0);

  // The filled upside down triangle.
  sf::ConvexShape triangle2;
  triangle2.setPointCount(3);
  triangle2.setPoint(0, _p1);
  triangle2.setPoint(1, _p2);
  triangle2.setPoint(2, _p3);
  triangle2.setPosition(0, 0);
  triangle2.setFillColor(sf::Color::Blue);

  // Add these to the vector
  triangles.push_back(triangle);
  triangles.push_back(triangle2);

  // Now call the draw function again.
  
}
