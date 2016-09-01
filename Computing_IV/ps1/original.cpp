/*
 * Copyright 2015 Jason Downing
 *
*/
#include "original.hpp"

/*
 * Inital coordinates of the circle will be:
 * 1) set the origin to be radius, radius - this makes it so that the circle's center for
 * transforming / moving / etc is its middle point.
 * 2) set the position to be the center of the screen
 */


// Constructor with just the depth as a parameter
Original::Original(int depth) {
  // Seed the rand function for random colors - uses current time to do so
  srand(time(NULL));

  // Set the inital depth
  _depth = depth;

  // Set the inital radius.
  _radius = 350;

  // Create a new circle;
  _circle = new Original(_radius - 10, _depth - 1);
}


// Constructor with coordinates - recusive
Original::Original(float radius, int depth) {
  // When depth is less than 0, the recusion is done.
  if (depth < 0) {
    _circle = NULL;

    return;
  }

  // Set member variables
  _depth = depth;
  _radius = radius;

  // Create a new circle;
  _circle = new Original(_radius - 10, _depth - 1);
  return;
}


// Destructor
Original::~Original() {
  if (_circle != NULL) {
    delete _circle;
  }
}


// Draw method
void Original::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  std::cout << "_depth is: " << _depth << std::endl;
  std::cout << "_Radius is: " << _radius << std::endl;

  // First circle
  sf::CircleShape shape(_radius);
  shape.setOrigin(_radius, _radius);
  shape.setPosition(400, 400);
  shape.setPointCount(10000);

  unsigned int seed = time(NULL);

  // Make a random number between 1 and 19
  // That means there will be 19 different colors flashing!
  int random_number = rand_r(&seed) % 19 + 1;

  // Make three random numbers, trip Udit.

  // Color object
  sf::Color color(0, 0, 0, 255);

  switch (random_number) {
    case 1:
      // Red Color
      shape.setFillColor(sf::Color::Red);
      break;

    case 2:
      // Orange Color
      color.r = 255;
      color.g = 128;
      color.b = 0;
      shape.setFillColor(color);
      break;

    case 3:
      // Yellow Color
      shape.setFillColor(sf::Color::Yellow);
      break;

    case 4:
      // Green
      shape.setFillColor(sf::Color::Green);
      break;

    case 5:
      // Magenta
      shape.setFillColor(sf::Color::Magenta);
      break;

    case 6:
      // Cyan
      shape.setFillColor(sf::Color::Cyan);
      break;

    case 7:
      // Purple
      color.r = 127;
      color.g = 0;
      color.b = 255;
      shape.setFillColor(color);
      break;

    case 8:
      // Pink
      color.r = 255;
      color.g = 0;
      color.b = 255;
      shape.setFillColor(color);
      break;


    case 9:
      // Dark Orange
      color.r = 204;
      color.g = 102;
      color.b = 0;
      shape.setFillColor(color);
      break;


    case 10:
      // Dark Blue
      color.r = 0;
      color.g = 0;
      color.b = 102;
      shape.setFillColor(color);
      break;


    case 11:
      // Dark Purple
      color.r = 255;
      color.g = 0;
      color.b = 0;
      shape.setFillColor(color);
      break;

    case 12:
      // Dark Green
      color.r = 0;
      color.g = 51;
      color.b = 0;
      shape.setFillColor(color);
      break;

    case 13:
      // Gold
      color.r = 102;
      color.g = 102;
      color.b = 0;
      shape.setFillColor(color);
      break;

    case 14:
      // Lime Green
      color.r = 51;
      color.g = 255;
      color.b = 51;
      shape.setFillColor(color);
      break;

    case 15:
      // Lime Green
      color.r = 51;
      color.g = 255;
      color.b = 51;
      shape.setFillColor(color);
      break;

    case 16:
      // Light Orange
      color.r = 255;
      color.g = 153;
      color.b = 51;
      shape.setFillColor(color);
      break;

    case 17:
      // Light Yellow
      color.r = 255;
      color.g = 255;
      color.b = 51;
      shape.setFillColor(color);
      break;

    case 18:
      // Light Blue
      color.r = 51;
      color.g = 255;
      color.b = 255;
      shape.setFillColor(color);
      break;

    case 19:
      // Light Red
      color.r = 255;
      color.g = 0;
      color.b = 0;
      shape.setFillColor(color);
      break;

    default:
      break;
  }

  /*
   * Colors to use
   * I generated these using:
   * http://www.rapidtables.com/web/color/RGB_Color.htm
   * I then used the Color() constructor which takes a Red, Green, Blue int for setting
   * custom colors.
   *
   *  "Standard colors"
   *  Red       -> sf::Color::Color(255, 0, 0)
   *  Orange    -> sf::Color::Color(255, 128, 0)
   *  Yellow    -> sf::Color::Color(255, 255, 51)
   *  Green     -> sf::Color::Color(0, 153, 0)
   *  Blue      -> sf::Color::Color(0, 0, 255)
   *  Purple    -> sf::Color::Color(127, 0, 255)
   *  Pink      -> sf::Color::Color(255, 0, 255)
   *
   *  "Dark colors"
   *  Dark Orange:  sf::Color::Color(204, 102, 0)
   *  Dark Blue:    sf::Color::Color(0, 0, 102)
   *  Dark Purple:  sf::Color::Color(255, 0, 0)
   *  Dark Green:   sf::Color::Color(0, 51, 0)
   *  Gold:         sf::Color::Color(102, 102, 0)
   *
   *  "Light colors"
   *  Lime Green:   sf::Color::Color(51, 255, 51)
   *  Light Orange: sf::Color::Color(255, 153, 51)
   *  Light Yellow: sf::Color::Color(255, 255, 51)
   *  Light Blue:   sf::Color::Color(51, 255, 255s)
   *  Light Blue:   sf::Color::Color(51, 153, 255)
   *  Light Purple: sf::Color::Color(153, 51, 255)
   *  Light Red:    sf::Color::Color(255, 0, 0)
   *
   */

  // Draw this circle
  target.draw(shape);

  // Recusive calls
  if (_circle != NULL) {
    _circle->draw(target, states);
  }
}

