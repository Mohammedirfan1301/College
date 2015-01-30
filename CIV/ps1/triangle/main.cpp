#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

int main()
{
  // Set the size of the window.
  // In this case I make it 605 by 605. The title is "Program 0".
  RenderWindow window(VideoMode(800, 800), "Program 1: Triangles");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  sf::ConvexShape polygon;
  polygon.setPointCount(3);
  polygon.setPoint(0, sf::Vector2f(0, 800));
  polygon.setPoint(1, sf::Vector2f(400, 0));
  polygon.setPoint(2, sf::Vector2f(800, 800));
  polygon.setPosition(0, 0);

  sf::ConvexShape polygon2;
  polygon2.setPointCount(3);
  polygon2.setPoint(0, sf::Vector2f(200, 400));
  polygon2.setPoint(1, sf::Vector2f(600, 400));
  polygon2.setPoint(2, sf::Vector2f(400, 800));
  polygon2.setPosition(0, 0);
  polygon2.setFillColor(Color::Red);

  sf::ConvexShape polygon3;
  polygon2.setPointCount(3);
  polygon2.setPoint(0, sf::Vector2f(200, 400));
  polygon2.setPoint(1, sf::Vector2f(600, 400));
  polygon2.setPoint(2, sf::Vector2f(400, 800));
  polygon2.setPosition(0, 0);
  polygon2.setFillColor(Color::Blue);

  sf::ConvexShape polygon4;
  polygon2.setPointCount(3);
  polygon2.setPoint(0, sf::Vector2f(200, 400));
  polygon2.setPoint(1, sf::Vector2f(600, 400));
  polygon2.setPoint(2, sf::Vector2f(400, 800));
  polygon2.setPosition(0, 0);
  polygon2.setFillColor(Color::Blue);

  sf::ConvexShape polygon5;
  polygon2.setPointCount(3);
  polygon2.setPoint(0, sf::Vector2f(200, 400));
  polygon2.setPoint(1, sf::Vector2f(600, 400));
  polygon2.setPoint(2, sf::Vector2f(400, 800));
  polygon2.setPosition(0, 0);
  polygon2.setFillColor(Color::Blue);

  // Window loop
  while (window.isOpen())
  {
    // Process events
    Event event;

    while(window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == Event::Closed)
      {
        window.close();
      }

      // Pressing escape will quit the program.
      else if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
        window.close();
      }
    }

    window.draw(polygon);
    window.draw(polygon2);
    window.display();
  }


  return 0;
}