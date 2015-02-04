#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

int main()
{
  // Settings to make stuff look pretty.
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  // Set the size of the window.
  // In this case I make it 605 by 605. The title is "Program 0".
  RenderWindow window(VideoMode(800, 800), "Program 1: Circles of death");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  sf::CircleShape shape1(200);
  shape1.setFillColor(sf::Color::Cyan);
  shape1.setOrigin(200, 200);
  shape1.setPosition(400, 400);
  shape1.setPointCount(10000);

  sf::CircleShape shape2(190);
  shape2.setFillColor(sf::Color::Red);
  shape2.setOrigin(190, 190);
  shape2.setPosition(400, 400);
  shape2.setPointCount(10000);

  sf::CircleShape shape3(180);
  shape3.setFillColor(sf::Color::Green);
  shape3.setOrigin(180, 180);
  shape3.setPosition(400, 400);
  shape3.setPointCount(10000);

  sf::CircleShape shape4(170);
  shape4.setFillColor(sf::Color::Yellow);
  shape4.setOrigin(170, 170);
  shape4.setPosition(400, 400);
  shape4.setPointCount(10000);

  sf::CircleShape shape5(160);
  shape5.setFillColor(sf::Color::Blue);
  shape5.setOrigin(160, 160);
  shape5.setPosition(400, 400);
  shape5.setPointCount(10000);

  sf::CircleShape shape6(150);
  shape6.setFillColor(sf::Color::Magenta);
  shape6.setOrigin(150, 150);
  shape6.setPosition(400, 400);
  shape6.setPointCount(10000);

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
  polygon3.setPointCount(3);
  polygon3.setPoint(0, sf::Vector2f(400, 400));
  polygon3.setPoint(1, sf::Vector2f(500, 600));
  polygon3.setPoint(2, sf::Vector2f(300, 600));
  polygon3.setPosition(0, 0);
  polygon3.setFillColor(Color::Blue);

//   sf::ConvexShape polygon4;
//   polygon2.setPointCount(3);
//   polygon2.setPoint(0, sf::Vector2f(200, 400));
//   polygon2.setPoint(1, sf::Vector2f(600, 400));
//   polygon2.setPoint(2, sf::Vector2f(400, 800));
//   polygon2.setPosition(0, 0);
//   polygon2.setFillColor(Color::Blue);
//
//   sf::ConvexShape polygon5;
//   polygon2.setPointCount(3);
//   polygon2.setPoint(0, sf::Vector2f(200, 400));
//   polygon2.setPoint(1, sf::Vector2f(600, 400));
//   polygon2.setPoint(2, sf::Vector2f(400, 800));
//   polygon2.setPosition(0, 0);
//   polygon2.setFillColor(Color::Blue);

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

    window.clear();

    window.draw(shape1);
    window.draw(shape2);
    window.draw(shape3);
    window.draw(shape4);
    window.draw(shape5);
    window.draw(shape6);

    window.display();
  }


  return 0;
}