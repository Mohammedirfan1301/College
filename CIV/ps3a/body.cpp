#include <iostream>
#include "body.hpp"

// Default Constructor
body::body()
{
  // We don't really need a default constructor it seems.
  return;
}


// Constructor with parameters
body::body(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name)
{
  _pos = pos;
  _vel = vel;
  _mass = obj_mass;

  // Load the image into an image object
  if (!_image.loadFromFile(file_name))
  {
    return;    // Quit if the file doesn't exist.
  }

  // Load the image into a texture
  _texture.loadFromImage(_image);

  // Load the texture into a sprite
  _sprite.setTexture(_texture);

  // Set the position from the Vector2f for position
  _sprite.setPosition(sf::Vector2f(_pos.x, _pos.y));
}


// Drawable method
void body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Testing outputting an image.
  target.draw(_sprite);
}


// Overridden operator >> for inputing from a file
std::istream& operator>> (std::istream &in, body &cBody)
{

  return in;
}


// Overriddden operator << for debugging
std::ostream& operator<< (std::ostream &out, body &cBody)
{
  // For debugging, output all the data stored in the object.
  out << "Pos (x): " << cBody._pos.x << std::endl;
  out << "Pos (y): " << cBody._pos.y << std::endl;

  out << "Vel (x): " << cBody._vel.x << std::endl;
  out << "Vel (y): " << cBody._vel.y << std::endl;

  out << "Mass: " << cBody._mass << std::endl;

  return out;
}

