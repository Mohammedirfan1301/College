#include <iostream>
#include "body.hpp"

// Constants for the window size.
const int window_height = 500;
const int window_side = 500;

int main(int argc, char* argv[])
{
  // Get the center of the window.
  int c_height = window_height / 2;
  int c_side = window_side / 2;

  // body objects
  body sun(sf::Vector2f(c_height, c_side), sf::Vector2f(0,0), 200.99, "sun.gif");
  body mercury(sf::Vector2f(c_height + 50, c_side), sf::Vector2f(0,0), 200.99, "mercury.gif");
  body venus(sf::Vector2f(c_height + 100, c_side), sf::Vector2f(0,0), 200.99, "venus.gif");
  body earth(sf::Vector2f(c_height + 160, c_side), sf::Vector2f(0,0), 200.99, "earth.gif");
  body mars(sf::Vector2f(c_height + 210, c_side), sf::Vector2f(0,0), 200.99, "mars.gif");

  // SFML Window
  sf::RenderWindow window(sf::VideoMode(window_side, window_height), "The Solar System");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  // Window loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;

    while(window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // Pressing escape will quit the program.
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }

    window.clear();

    // Draw the objects we made above.
    window.draw(sun);
    window.draw(mercury);
    window.draw(venus);
    window.draw(earth);
    window.draw(mars);

    window.display();
  }

  return 0;
}
