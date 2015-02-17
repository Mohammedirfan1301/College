#include <iostream>
#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "LFSR.hpp"


int main(int argc, char* argv[])
{
  // Must enter
  if(argc != 5)
  {
    std::cout << "Usage: $ ./PhotoMagic [input file] [output file] [seed] [tap] \n";
    return -1;
  }

  // Save the command line arguments to variables
  std::string input_filename(argv[1]);
  std::string output_filename(argv[2]);
  std::string seed(argv[3]);
  int tap = atoi(argv[4]);

  // LSFR stuff
  LFSR randomizer(seed, tap);

  // Setup the two images
  sf::Image input_image;
  if (!input_image.loadFromFile(input_filename))
  {
    return -1;
  }

  sf::Image output_image;
  if (!output_image.loadFromFile(input_filename))
  {
    return -1;
  }

  // p is a pixel
  sf::Color p;

  // Setup the two windows
  sf::Vector2u size = input_image.getSize();
  sf::RenderWindow input_window(sf::VideoMode(size.x, size.y), "Input Image");
  sf::RenderWindow output_window(sf::VideoMode(size.x, size.y), "Output Image");

  // Randomize the bits in the image
  for(int x= 0; x < (signed)size.x; x++)
  {
    for(int y = 0; y < (signed)size.y; y++)
    {
      // Get the current pixel from the input image
      p = input_image.getPixel(x, y);

      // XOR the pixels
      p.r = p.r ^ randomizer.generate(tap);
      p.g = p.g ^ randomizer.generate(tap);
      p.b = p.b ^ randomizer.generate(tap);

      // Modify just the output image
      output_image.setPixel(x, y, p);
    }
  }

  // Load the images into textures
  sf::Texture input_texture, output_texture;
  input_texture.loadFromImage(input_image);
  output_texture.loadFromImage(output_image);

  // Then load the textures into sprites
  sf::Sprite input_sprite, output_sprite;
  input_sprite.setTexture(input_texture);
  output_sprite.setTexture(output_texture);

  // Window loop
  while (input_window.isOpen() && output_window.isOpen())
  {
    sf::Event event;

    while (input_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        input_window.close();
      }
    }

    while (output_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        output_window.close();
      }
    }

    input_window.clear();
    input_window.draw(input_sprite);    // Input image
    input_window.display();

    output_window.clear();
    output_window.draw(output_sprite);    // Output image
    output_window.display();
  }

  // Save the modified image to the output file
  if (!output_image.saveToFile(output_filename))
  {
    return -1;
  }

  return 0;
}
