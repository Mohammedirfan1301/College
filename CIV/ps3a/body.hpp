#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Constants for the window size.
const int window_height = 500;
const int window_side = 500;

class body: public sf::Drawable
{
public:

  // Constructors
  body();
  body(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, float radius, std::string file_name);

  void set_radius(float radius);
  void set_position();              // Sets the planets positions

  // Overridden operator >> for inputing from a file
  friend std::istream& operator>> (std::istream &input, body &cBody);

  // Overriddden operator << for debugging
  friend std::ostream& operator<< (std::ostream &output, body &cBody);

private:

  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // Member variables
  sf::Vector2f _pos;
  sf::Vector2f _vel;
  float _mass;
  std::string _filename;

  // Image related objects
  sf::Image _image;
  sf::Sprite _sprite;
  sf::Texture _texture;

  // Universe Radius
  float _radius;
};
