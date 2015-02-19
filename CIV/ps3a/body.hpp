#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class body: public sf::Drawable
{
public:
  body();
  body(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, std::string file_name);

  // Overridden operator >> for inputing from a file
  friend std::istream& operator>> (std::istream &in, body &cBody);

  // Overriddden operator << for debugging
  friend std::ostream& operator<< (std::ostream &out, body &cBody);

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
