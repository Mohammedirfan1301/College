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
