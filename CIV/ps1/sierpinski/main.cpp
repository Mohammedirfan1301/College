#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sierpinski.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  // Make sure we are given exactly 3 arguments
  if(argc < 3 || argc > 4)
  {
    // Let the user know the correct way of calling the program.
    cout << "sierpinski [recursion-depth] [side-length]" << endl;
    return -1;
  }

  // test

  int depth = atoi(argv[1]);
  int side = atoi(argv[2]);

  cout << "depth: " << depth << endl;
  cout << "side: " << side << endl;

  Sierpinski s(depth, side);

  int window_height = (int)(0.5*sqrt(3.0)*(float)side);

  sf::RenderWindow window(sf::VideoMode(side, window_height), "Sierpinkski");

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
    window.draw(s);
    window.display();
  }

  return 0;
}