#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

int main()
{
  // Set the size of the window.
  // In this case I make it 605 by 605. The title is "Program 0".
  RenderWindow window(VideoMode(605, 605), "Program 0: Doge Sprite Moves");

  // Change the framerate to make it easier to see the image moving.
  window.setFramerateLimit(1);

  // Loads a doge from file - in this case a doge
  Texture image_texture;

  // Check to see if the file loaded correctly.
  // I make just the doge part of the image load - it's actually 300 by 372
  // but I cut off 50 pixels from the height.
  if (!image_texture.loadFromFile( "sprite.png",  IntRect(0, 50, 300, 300) ) )
  {
    // Return failure if the image doesn't load
    cout << "Failed to load image!\n";
    return EXIT_FAILURE;
  }

  // Make the image look nice.
  image_texture.setSmooth(true);

  // Now set the doge using the texture
  Sprite doge;
  doge.setTexture(image_texture);

  // Set the origin for rotation to the center of the doge.
  doge.setOrigin(150, 125);

  // Move to the top left corner.
  doge.move(150, 100);    // Top left corner

  // Create an image to move in a rectangle pattern
  Texture image2_texture;

  // Load the image
  if (!image2_texture.loadFromFile( "doge.png"))
  {
    // Return failure if the image doesn't load
    cout << "Failed to load image!\n";
    return EXIT_FAILURE;
  }

  image2_texture.setSmooth(true);

  // Second doge settings
  Sprite doge2;
  doge2.setTexture(image2_texture);  // Set the texture
  doge2.scale(.25f, .25f);           // Shrink the image
  doge2.setOrigin(732, 620);         // Set the center of the image
  doge2.move(300, 300);              // Move the image to the top left corner

  int dir = 1;

  // Create a graphical text to display
  Font font;
  if (!font.loadFromFile("arial.ttf"))
  {
    cout << "Failed to load font!\n";
    return EXIT_FAILURE;
  }

  // Create a text.
  Text text("Woof", font, 70);

  // Move the text to the bottom center (roughly)
  text.move(230,500);

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

      // Move the image if an arrow key is pressed.
      else if(Event::KeyPressed)
      {
        // Arrow keys will move the doge in the
        // expected direction.
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
          doge2.move(-15, 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
          doge2.move(15, 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
          doge2.move(0, -15);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
          doge2.move(0, 15);
        }

        // Enter will rotate the doge
        else if (Keyboard::isKeyPressed(Keyboard::Space))
        {
          doge2.rotate(45);
        }

        // Pressing + will increase the size of the doge.
        else if (Keyboard::isKeyPressed(Keyboard::Add))
        {
          doge2.scale(1.05f, 1.05f);
        }

        // Pressing - will decrease the size of the doge.
        else if (Keyboard::isKeyPressed(Keyboard::Subtract))
        {
          doge2.scale(.95f, .95f);
        }

        // Pressing escape will quit the program.
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
          return 0;
        }
      }
    }

    // Clear the screen - so that the doge's previous image gets erased.
    window.clear();

    // Ifs that will keep the Doge sprite moving in a rectangle pattern.
    // Basically they increase int dir by 1 until it reaches 5, then it resets
    // the int dir to 1.
    switch(dir)
    {
      case 1:
        doge.move(300, 0);      // Top right corner
        dir++;
        break;

      case 2:
        doge.move(0, 325);      // Bottom right corner
        dir++;
        break;

      case 3:
        doge.move(-300, 0);     // Bottom left corner
        dir++;
        break;

      case 4:
        doge.move(0, -325);     // Top left corner again.
        dir++;
        break;

      default:
        dir = 1;
        break;
    }

    // Redraw the doge
    window.draw(doge);

    // This is the second doge - the one that moves in a rectangle.
    window.draw(doge2);

    // Draw the string
    window.draw(text);

    // Update the window
    window.display();
  }

  return 0;
}