#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

int main()
{
  // Set the size of the window.
  // In this case I make it 605 by 605. The title is "Program 0".
  sf::RenderWindow window(sf::VideoMode(605, 605), "Program 0: Doge Meme");

  // Loads a doge from file - in this case a doge
  sf::Texture image_texture;

  // Check to see if the file loaded correctly.
  // I make just the dog part of the image load - it's actually 300 by 372
  // but I cut off 50 pixels from the height.
  if (!image_texture.loadFromFile( "doge.png",  sf::IntRect(0, 50, 300, 300) ) )
  {
    // Return failure if the image doesn't load
    cout << "Failed to load image!\n";
    return EXIT_FAILURE;
  }

  // Make the image look nice.
  image_texture.setSmooth(true);

  // Now set the doge using the texture
  sf::Sprite doge;

  doge.setTexture(image_texture);

  // Set the origin for rotation to the center of the doge.
  doge.setOrigin(150, 125);

  doge.move(302, 200);

  // Create a graphical text to display
  sf::Font font;
  if (!font.loadFromFile("arial.ttf"))
  {
    cout << "Failed to load font!\n";
    return EXIT_FAILURE;
  }
  sf::Text text("Woof", font, 70);

  // Move the text to the bottom center (roughly)
  text.move(230,500);

  // Window loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;

    // See if the window closes
    while(window.pollEvent(event))
    {
      // Close window : exit
      if (sf::Event::Closed)
      {
        window.close();
      }

      // Move the image if an arrow key is pressed.
      else if(sf::Event::KeyPressed)
      {
        // Arrow keys will move the doge in the
        // expected direction.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
          doge.move(-15, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
          doge.move(15, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
          doge.move(0, -15);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
          doge.move(0, 15);
        }

        // Enter will rotate the doge
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
          doge.rotate(45);
        }

        // Pressing + will increase the size of the doge.
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
          doge.scale(1.05f, 1.05f);
        }

        // Pressing - will decrease the size of the doge.
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
          doge.scale(.95f, .95f);
        }

        // Pressing escape will quit the program.
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
          return 0;
        }
      }

    }

    // Clear the screen - so that the doge's previous image
    // gets erased.
    window.clear();

    // Redraw the doge
    window.draw(doge);

    // Draw the string
    window.draw(text);

    // Update the window
    window.display();
  }

  return 0;
}