#include "body.hpp"

// Default Constructor
body::body()
{
  // Does nothing since I call the setter methods and the >> operator.
  return;
}


// Constructor with parameters
body::body(double pos_x, double pos_y, double vel_x, double vel_y,
           double obj_mass, double radius, std::string file_name)
{
  // Set member variables
  _pos_x = pos_x;
  _pos_y = pos_y;
  _vel_x = vel_x;
  _vel_y = vel_y;
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
  _sprite.setPosition(sf::Vector2f(_pos_x, _pos_y));
}


// Sets the universe radius
void body::set_radius(float radius)
{
  _radius = radius;
  return;
}


// Sets the forces for a given object
void body::set_forces(double forcex, double forcey)
{
  _for_x = forcex;
  _for_y = forcey;
}


// Finds the force (x) between two body objects
double find_forcex(body &Body1, body &Body2)
{
  /*
   * Formulas:
   * F = (G * M1 * M2) / R^2
   * R =
   * R^2 = R squared
   * Δx = x2 - x1
   * Δy = y2 - y1
   */
  double dx = Body2._pos_x - Body1._pos_x;
  double dy = Body2._pos_y - Body1._pos_y;
  double R2 = pow(dx, 2) + pow(dy, 2);
  double R = sqrt(R2);
  double force = (gravity * Body1._mass * Body2._mass) / R2;
  double for_x = force * (dx / R);

  std::cout << "Body1 Filename: " << Body1._filename << "\n";
  std::cout << "dx: " << dx << "\n";
  std::cout << "dy: " << dy << "\n";
  std::cout << "Force: " << force << "\n";
  std::cout << "Force(x) " << for_x << "\n";
  std::cout << "Gravity: " << gravity << "\n";
  std::cout << "Body1 Mass: " << Body1._mass << "\n";
  std::cout << "Body2 Mass: " << Body2._mass << "\n\n";

  return for_x;
}


// Finds the force (y) between two body objects
double find_forcey(body &Body1, body &Body2)
{
  /*
   * Formula is: F = (G * M1 * M2) / R^2
   */
  double dx = Body2._pos_x - Body1._pos_x;
  double dy = Body2._pos_y - Body1._pos_y;
  double R2 = pow(dx, 2) + pow(dy, 2);
  double R = sqrt(R2);
  double force = (gravity * Body1._mass * Body2._mass) / R2;
  double for_y = force * (dy / R);

  std::cout << "Body1 Filename: " << Body1._filename << "\n";
  std::cout << "dx: " << dx << "\n";
  std::cout << "dy: " << dy << "\n";
  std::cout << "Force: " << force << "\n";
  std::cout << "Force(y " << for_y << "\n";
  std::cout << "Gravity: " << gravity << "\n";
  std::cout << "Body1 Mass: " << Body1._mass << "\n";
  std::cout << "Body2 Mass: " << Body2._mass << "\n\n";

  return for_y;
}


void body::step(double time_t)
{
  /*
   * Convert forces into acceleration
   *
   *  F =  m * a
   * Ax = Fx / m
   * Ay = Fy / m
   *
   */
  _acc_x = _for_x / _mass;
  _acc_y = _for_y / _mass;

  /*
   * Calculate change in velocity
   *
   * dvelx = (ax * time_step)
   * _velx = = _velx + (ax * time_step)
   *
   * (vx + Δt ax, vy + Δt ay)
   *
   */
  _vel_x = _vel_x + (_acc_x * time_t);
  _vel_y = _vel_y + (_acc_y * time_t);

  /*
   * Body moves based on its velocity
   *
   * _xpos = _xpos + (_xvel * time_step)
   *
   * (px + Δt vx, py + Δt vy)
   *
   */
  _pos_x = _pos_x + (_vel_x * time_t);
  _pos_y = _pos_y + (_vel_y * time_t);

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

  // Note - using temp variables to avoid modifying the member variables and having
  // to switch back and forth between astronomical and pixel measurements.
  double pos_x = ( (_pos_x / _radius) * (window_side / 2) ) + (window_side / 2);
  double pos_y = ( (_pos_y / _radius) * (window_height / 2) ) + (window_height / 2);

  // Set the position from the Vector2f for position
  // Flip the x and y positions for going counter-clockwise
  _sprite.setPosition(sf::Vector2f(pos_y, pos_x));
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
  input >> cBody._pos_x >> cBody._pos_y;
  input >> cBody._vel_x >> cBody._vel_y;
  input >> cBody._mass  >> cBody._filename;

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

  // Set the initial position
  cBody._sprite.setPosition(sf::Vector2f(cBody._pos_x, cBody._pos_y));

  // Set force / acceleration to 0.
  cBody._for_x = 0;
  cBody._for_y = 0;
  cBody._acc_x = 0;
  cBody._acc_y = 0;

  return input;
}


// Overriddden operator << for debugging
// Very useful for finding out why stuff doesn't work.
std::ostream& operator<< (std::ostream &output, body &cBody)
{
  // For debugging, output all the data stored in the object.
  output << "Filename: " << cBody._filename << std::endl;
  output << "Acceleration (x): " << cBody._acc_x << std::endl;
  output << "Acceleration (y): " << cBody._acc_y << std::endl;
  output << "Force (x): " << cBody._for_x << std::endl;
  output << "Force (y): " << cBody._for_y << std::endl;
  output << "Pos (x): " << cBody._pos_x << std::endl;
  output << "Pos (y): " << cBody._pos_y << std::endl;
  output << "Vel (x): " << cBody._vel_x << std::endl;
  output << "Vel (y): " << cBody._vel_y << std::endl;
  output << "Mass: " << cBody._mass << std::endl;
  output << "Radius: " << cBody._radius << std::endl << std::endl;

  return output;
}

