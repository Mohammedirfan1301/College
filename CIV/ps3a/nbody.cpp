#include <iostream>
#include "nbody.hpp"

// Default Constructor
nbody::nbody()
{
  std::cout << "I made le body.\n";
  return;
}


// Constructor with parameters
nbody::nbody(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name)
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
}


// Drawable method
void nbody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cout << "Howdy there m8.\n";
}