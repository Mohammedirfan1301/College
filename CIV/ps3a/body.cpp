#include <iostream>
#include "body.hpp"

// Default Constructor
body::body()
{
  // We don't really need a default constructor it seems.
  return;
}


// Constructor with parameters
body::body(sf::Vector2f pos, sf::Vector2f vel, float obj_mass, float radius, std::string file_name)
{
  // Set member variables
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


// Sets the universe radius
void body::set_radius(float radius)
{
  _radius = radius;
  return;
}


// Sets the planets position
void body::set_position()
{
  /*
   * The math here probably needs some explaing:
   *
   * First thing I do is divide the pos by the radius. This gets me a nice
   * ratio I can use. For the earth this value comes out to .5984.
   *
   * Next, I use this ratio and multiply it by EITHER half the width or height of the window
   * (depends on whether its a x or y coordinate. x corsponds to wide, y corsponds with height)
   * which gets me a position that is actually in the SFML coordinate system.
   *
   * Finally, now that I have the position in SFML coordinates, I adjust for the fact
   * that the SFML window's center is half the height and side. Example would be
   * a window of 500 by 500 has its center at 250, 250. The coordinates that we are
   * given in the planets.txt file actually have their center at 0,0. So even though
   * I have the SFML coordinates, I must add 250 to both the x and y coordinates to
   * make the planets show up in the center of the screen.
   *
   * Example math for the earth:
   * [pos to radius ratio] * [side OR height / 2]
   * .5984 * 250 = 149.6
   *
   * The 149.6 in this case works perfectly with the SFML coordinate system.
   * We just add 250 to get the center for SFML coordinate, which would come out
   * to 399.6
   *
   * A quick note - y coordinates all have a '0' by default, so the below math
   * actually just sets all the y coordinates to 250 - which is the center of the SFML
   * height (0 to 500, 250 is the middle).
   *
   */
  _pos.x = ( (_pos.x / _radius) * (window_side / 2) ) + (window_side / 2);
  _pos.y = ( (_pos.y / _radius) * (window_height / 2) ) + (window_height / 2);

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
// Very useful for finding out why stuff doesn't work.
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

