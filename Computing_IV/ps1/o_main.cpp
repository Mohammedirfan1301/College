/*
 * Copyright 2015 Jason Downing
 *
*/
#include "original.hpp"

int main(int argc, char* argv[]) {
  // Make sure we are given exactly 2 arguments
  if (argc < 2 || argc > 3) {
    // Let the user know the correct way of calling the program.
    std::cout << "./original [recursion-depth]" << "\n";
    return -1;
  }

  int depth = atoi(argv[1]);

  Original obj(depth);

  sf::RenderWindow window(sf::VideoMode(800, 800), "Original Recursive Image");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(60);

  // Window loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;

    while (window.pollEvent(event)) {
      // Close window : exit
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
      }
    }

    window.clear();
    window.draw(obj);     // Call the draw object in the Original class
    window.display();
  }

  return 0;
}
