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
  _filename = file_name;

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
std::istream& operator>> (std::istream &input, body &cBody)
{
  // Read input into the object
  input >> cBody._pos.x >> cBody._pos.y;
  input >> cBody._vel.x >> cBody._vel.y;
  input >> cBody._mass;
  input >> cBody._filename;

  // Now set up the images
  // Just like the constructor

  // Load the image into an image object
  if (!cBody._image.loadFromFile(cBody._filename))
  {
    return input;    // Quit if the file doesn't exist.
  }

  // Load the image into a texture
  cBody._texture.loadFromImage(cBody._image);

  // Load the texture into a sprite
  cBody._sprite.setTexture(cBody._texture);

  // Set the position from the Vector2f for position
  cBody._sprite.setPosition(sf::Vector2f(cBody._pos.x, cBody._pos.y));

  return input;
}


// Overriddden operator << for debugging
std::ostream& operator<< (std::ostream &output, body &cBody)
{
  // For debugging, output all the data stored in the object.
  output << "Pos (x): " << cBody._pos.x << std::endl;
  output << "Pos (y): " << cBody._pos.y << std::endl;

  output << "Vel (x): " << cBody._vel.x << std::endl;
  output << "Vel (y): " << cBody._vel.y << std::endl;

  output << "Mass: " << cBody._mass << std::endl;

  output << "Filename: " << cBody._filename << std::endl;

  return output;
}

