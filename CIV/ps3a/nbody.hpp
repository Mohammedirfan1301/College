#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class nbody
{
public:
  nbody();
  nbody(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name);
  
protected:
  
private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  float mass; 
  sf::Sprite image_sprite;
  sf::Texture image_texture;
};