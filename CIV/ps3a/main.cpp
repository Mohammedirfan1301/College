#include <iostream>
#include "body.hpp"

// Constants for the window size.
const int window_height = 500;
const int window_side = 500;

int main(int argc, char* argv[])
{
  // Get the center of the window.
//   int c_height = window_height / 2;
//   int c_side = window_side / 2;

  // File I/O - open the planets.txt file
  std::fstream planets_file("planets.txt", std::ios::in);

  // Make sure the file open opened correctly.
  if(!planets_file.is_open())
  {
    std::cout << "planets.txt failed to open!\n";
    return -1;
  }

  // Get the first two numbers in the text file. The first should be an int telling us
  // how many planets there are. The second should be a float telling us the radius of
  // the universe.
  std::string num_planets, radius;

  getline(planets_file, num_planets, '\n');
  getline(planets_file, radius, '\n');

  // Now we know how many planets + the radius. Convert these from std::strings to int / float
  int number_planets = atoi(num_planets.c_str());
  float universe_radius = atof(radius.c_str());

  std::cout << "Num of planets: " << number_planets << std::endl;
  std::cout << "Radius: " << universe_radius << std::endl;

  // Create a vector of body objects
  std::vector<body> body_vector;

  // strings to hold in values
  std::string x_pos, y_pos, x_vel, y_vel, mass, filename;

  // Loop through, create 5 (or how ever many we're asked for) body objects using the input file.
  for(int i = 0; i < number_planets; i++)
  {
    // Get input from the file

    /*
     *  turns out this should actually be using
     *  the >> operator
     *  so I should stop here and fix this tomorrow or whenever.
     *
     */

    getline(planets_file, x_pos, ' ');
    getline(planets_file, y_pos, ' ');
    getline(planets_file, x_vel, ' ');
    getline(planets_file, y_vel, ' ');
    getline(planets_file, mass, ' ');
    getline(planets_file, filename, ' ');

    // Create a new object
    

  }


  // body objects (manually created)
//   body sun(sf::Vector2f(c_height, c_side), sf::Vector2f(0,0), 200.99, "sun.gif");
//   body mercury(sf::Vector2f(c_height + 50, c_side), sf::Vector2f(0,0), 200.99, "mercury.gif");
//   body venus(sf::Vector2f(c_height + 100, c_side), sf::Vector2f(0,0), 200.99, "venus.gif");
//   body earth(sf::Vector2f(c_height + 160, c_side), sf::Vector2f(0,0), 200.99, "earth.gif");
//   body mars(sf::Vector2f(c_height + 210, c_side), sf::Vector2f(0,0), 200.99, "mars.gif");

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

    // Draw the objects we made above. (manually)
//     window.draw(sun);
//     window.draw(mercury);
//     window.draw(venus);
//     window.draw(earth);
//     window.draw(mars);

    window.display();
  }

  return 0;
}
