#include "body.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "Usage: ./NBody [simulation time] [time step] < planets.txt\n";
    return -1;
  }

  std::string sim_time(argv[1]);
  std::string step_time(argv[2]);

  std::cout << "Simulation time: " << sim_time << "\n";
  std::cout << "Time Step: " << step_time << "\n\n";

  // Get the first two numbers in the text file. The first should be an int telling us
  // how many planets there are. The second should be a float telling us the radius of
  // the universe.
  std::string num_planets, radius;

  // Use cin to redirect the input
  std::cin >> num_planets;
  std::cin >> radius;

  // Now we know how many planets + the radius. Convert these from std::strings to int / float
  int number_planets = atoi(num_planets.c_str());
  float universe_radius = atof(radius.c_str());

  std::cout << "Num of planets: " << number_planets << std::endl;
  std::cout << "Radius: " << universe_radius << std::endl << std::endl;

  // Create a vector of body objects
  std::vector<body> body_vector;

  // Loop through, create 5 (or how ever many we're asked for) body objects using the input file.
  for(int i = 0; i < number_planets; i++)
  {
    // Create a new object
    body* tmp = new body();

    // Read input into the object
    std::cin >> *tmp;

    // Set the radius and the planet positions.
    tmp->set_radius(universe_radius);
    tmp->set_position();

    // Save the object to the vector
    body_vector.push_back(*tmp);

    // Test the object (debugging)
    std::cout << *tmp;
  }

  // SFML Window
  sf::RenderWindow window(sf::VideoMode(window_side, window_height), "The Solar System");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  // Background image
  sf::Image background_image;

  // Background image
  if (!background_image.loadFromFile("stars.jpg"))
  {
    return -1;    // Quit if the file doesn't exist.
  }

  // Load the image into a texture
  sf::Texture background_texture;
  background_texture.loadFromImage(background_image);

  // Load the texture into a sprite
  sf::Sprite background_sprite;
  background_sprite.setTexture(background_texture);

  // Set the position to make the background look cool
  background_sprite.setPosition(sf::Vector2f(-700, -700));

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

    // Draws the starry background (black backgrounds are so lame for a solar system)
    window.draw(background_sprite);

    // Display the vector of objects
    std::vector<body>::iterator it;

    for(it = body_vector.begin(); it != body_vector.end(); it++)
    {
      window.draw(*it);
    }

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
