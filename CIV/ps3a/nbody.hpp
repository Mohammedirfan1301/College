#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class nbody: public sf::Drawable
{
public:
  nbody();
  nbody(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name);
  
  // Overridden operator
  //friend std::ostream& operator>> (std::ostream &out, LFSR &cLFSR);
  
private:
  
  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  sf::Vector2f _pos;
  sf::Vector2f _vel;
  float _mass; 
  
  sf::Image _image;
  sf::Sprite _sprite;
  sf::Texture _texture;
};