/*
 * Copyright 2015 Jason Downing
 *
*/
#include "original.hpp"

int main(int argc, char* argv[]) {
  // Make sure we are given exactly 3 arguments
  if (argc < 3 || argc > 4) {
    // Let the user know the correct way of calling the program.
    std::cout << "./original [recursion-depth] [side-length] \n";
    return -1;
  }

  int depth = atoi(argv[1]);
  int side = atoi(argv[2]);

  std::cout << "depth: " << depth << std::endl;
  std::cout << "side: " << side << std::endl;

  Original obj(depth, side);

  int window_height = 0.5*sqrt(3.0)*static_cast<float>(side);

  sf::RenderWindow window(sf::VideoMode(side, window_height),
                          "Original Recursive Image");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

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
