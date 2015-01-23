#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(500, 375), "SFML works!");
  sf::CircleShape shape(100.f);

  // Loads a sprite from file - in this case a doge
  sf::Texture texture;
  if (!texture.loadFromFile("doge.jpg"))
    return EXIT_FAILURE;
  sf::Sprite sprite(texture);

  // Creates text to display on the screen.
  sf::Font font;
  if (!font.loadFromFile("arial.ttf"))

  // Make some text to display
  sf::Text text("Hello SFML", font, 50);

  while (window.isOpen())
  {
    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Close window : exit
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Clear screen
    window.clear();

    // Draw the sprite
    window.draw(sprite);

    // Draw the string
    window.draw(text);

    // Update the window
    window.display();
  }

  return 0;
}