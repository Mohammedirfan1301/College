#ifndef ORIGINAL_HPP
#define ORIGINAL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Original : public sf::Drawable
{
public:
  // Constructor that takes just depth and side
  Original(int depth);

  // Constructor that takes three points and depth
  Original(sf::Vector2f tleft, sf::Vector2f tright,
           sf::Vector2f bleft, sf::Vector2f bright, float side, int depth);

  // Destructor
  ~Original();

  // Make a vector of shapes to print out
  vector <sf::ConvexShape> make_vector(Original* const& squ, vector<sf::ConvexShape>& squares) const;

private:

  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // Member variables
  int _depth;
  sf::Vector2f _tleft, _bleft, _tright, _bright;

  // Pointers to additional triangles.
  Original *_square1, *_square2, *_square3, *_square4;
};

#endif