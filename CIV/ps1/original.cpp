#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "original.hpp"

using namespace std;

/*
 * tleft = top left point
 * bleft = bottom left point
 * bright = bottom right point
 * tright = top right point
 *
 */

// Constructor with just the depth as a parameter
Original::Original(int depth) : _depth (depth)
{
  // Set the initial coordinates
  _tleft  = sf::Vector2f(  0,   0);
  _bleft  = sf::Vector2f(800,   0);
  _bright = sf::Vector2f(800, 800);
  _tright = sf::Vector2f(  0, 800);

  // Define a side variable
  float side = 800;
  side = side / 2;    // Divide by two to make more squares

  // Create four new squares
  // Top left square
  _square1 = new Original(sf::Vector2f(    0,    0), sf::Vector2f( side,    0),
                         sf::Vector2f( side, side), sf::Vector2f(    0, side), side, depth - 1);

  // Top right square
  _square2 = new Original(sf::Vector2f(    0, side), sf::Vector2f( side, side),
                         sf::Vector2f( side, side * 2), sf::Vector2f(    0, side * 2), side, depth - 1);

  // Bottom left square
  _square3 = new Original(sf::Vector2f( side,    0),  sf::Vector2f( side, side),
                         sf::Vector2f( side * 2, 0), sf::Vector2f( side * 2, side), side, depth - 1);

  // Bottom right square
  _square4 = new Original(sf::Vector2f( side, side), sf::Vector2f(side, side * 2),
                         sf::Vector2f( side * 2, side), sf::Vector2f(side * 2, side * 2), side, depth - 1);

}


// Constructor with coordinates - recusive
Original::Original(sf::Vector2f tleft, sf::Vector2f tright,
                   sf::Vector2f bleft, sf::Vector2f bright, float side, int depth) : _depth (depth)
{
  // When depth is less than 0, the recusion is done.
  if(_depth < 0)
  {
    _square1 = NULL;
    _square2 = NULL;
    _square3 = NULL;
    _square4 = NULL;

    return;
  }

  side = side / 2;    // Divide by two to make more squares

  // Create four new squares
  // Top left square
  _square1 = new Original(sf::Vector2f(    0,    0), sf::Vector2f( side,    0),
                         sf::Vector2f( side, side), sf::Vector2f(    0, side), side, depth - 1);

  // Top right square
  _square2 = new Original(sf::Vector2f(    0, side), sf::Vector2f( side, side),
                         sf::Vector2f( side, side * 2), sf::Vector2f(    0, side * 2), side, depth - 1);

  // Bottom left square
  _square3 = new Original(sf::Vector2f( side,    0),  sf::Vector2f( side, side),
                         sf::Vector2f( side * 2, 0), sf::Vector2f( side * 2, side), side, depth - 1);

  // Bottom right square
  _square4 = new Original(sf::Vector2f( side, side), sf::Vector2f(side, side * 2),
                         sf::Vector2f( side * 2, side), sf::Vector2f(side * 2, side * 2), side, depth - 1);

  return;
}


// Destructor
Original::~Original()
{

  // We will deal with this later.

}



// Make a vector of shapes to print out
vector <sf::ConvexShape> Original::make_vector(Original* const& squ, vector<sf::ConvexShape>& squares) const
{
  if(squ->_depth == 0)
  {
    return squares;
  }

  cout << "_depth is: " << squ->_depth << endl;
  cout << "_top left is: (" << squ->_tleft.x << ", " << squ->_tleft.y << ") \n";
  cout << "_bottom left is (" << squ->_bleft.x << ", " << squ->_bleft.y << ") \n";
  cout << "_bottom right is (" << squ->_bright.x << ", " << squ->_bright.y << ") \n";
  cout << "_top right is (" << squ->_tright.x << ", " << squ->_tright.y << ") \n";

  sf::ConvexShape square;
  square.setPointCount(4);
  square.setPoint(0, squ->_tleft);
  square.setPoint(1, squ->_bleft);
  square.setPoint(2, squ->_bright);
  square.setPoint(3, squ->_tright);
  square.setOutlineThickness(2);
  square.setOutlineColor(sf::Color::Red);
//   square.setFillColor(sf::Color::Blue);

  squares.push_back(square);        // Add to the back of the vector

  // Recursive calls
  squares = make_vector(squ->_square1, squares);
  squares = make_vector(squ->_square2, squares);
  squares = make_vector(squ->_square3, squares);
  squares = make_vector(squ->_square4, squares);

  return squares;   // Return the vector of shapes we just created
}


// Draw method
void Original::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Check the beginning dimensions of the overall shape
  //   cout << "_depth is: " << _depth << endl;
  //   cout << "_top is: (" << _top.x << ", " << _top.y << ") \n";
  //   cout << "_left is (" << _left.x << ", " << _left.y << ") \n";
  //   cout << "_right is (" << _right.x << ", " << _right.y << ") \n";

  // This vector will hold all the triangles we want to draw.
  vector <sf::ConvexShape> vec_squares;

  // The main square
  sf::ConvexShape square;
  square.setPointCount(4);
  square.setPoint(0, _tleft);
  square.setPoint(1, _bleft);
  square.setPoint(2, _bright);
  square.setPoint(3, _tright);
  square.setOutlineThickness(2);
  square.setOutlineColor(sf::Color::Red);
  square.setFillColor(sf::Color::Blue);

  // Draw the two triangles above.
  target.draw(square);

  // Recusively create the vectors
  vec_squares = make_vector(_square1, vec_squares);
  vec_squares = make_vector(_square2, vec_squares);
  vec_squares = make_vector(_square3, vec_squares);
  vec_squares = make_vector(_square4, vec_squares);

  // Test the size of the vector.
  cout << "Size of the vector is: " << vec_squares.size() << endl;

  for(vector<sf::ConvexShape>::iterator it = vec_squares.begin();
      it != vec_squares.end(); it++)
      {
        target.draw(*it);
      }
}


