#ifndef SIERPINSKI_HPP
#define SIERPINSKI_HPP

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Sierpinski : public sf::Drawable
{
public:
  // Constructor that takes just depth and side
  Sierpinski(int depth, int side);

  // Constructor that takes three points and depth
  Sierpinski(sf::Vector2f top, sf::Vector2f left, sf::Vector2f right, int depth);

  // Destructor
  ~Sierpinski();

private:

  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // Member variables
  int _depth;
  sf::Vector2f _top, _left, _right;
  sf::Vector2f _p1, _p2, _p3;

  // Pointers to additional triangles.
  Sierpinski *_triangle1, *_triangle2, *_triangle3;
};

#endif
