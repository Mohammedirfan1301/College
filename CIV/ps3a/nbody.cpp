#include "nbody.hpp"


// Default Constructor
nbody::nbody()
{
  std::cout << "I made le body.\n";
  return;
}


nbody::nbody(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name)
{
  position = pos;
  velocity = vel;
  mass = obj_mass; 
/*  
  image_sprite;
  image_texture;*/
}