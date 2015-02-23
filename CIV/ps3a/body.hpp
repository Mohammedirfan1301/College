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
  body(double pos_x, double pos_y, double vel_x, double vel_y,
       double obj_mass, double radius, std::string file_name);

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
  double _pos_x, _pos_y;
  double _vel_x, _vel_y;
  double _mass;
  double _radius;
  std::string _filename;

  // Image related objects
  sf::Image _image;
  sf::Sprite _sprite;
  sf::Texture _texture;
};
