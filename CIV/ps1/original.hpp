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
  Original(float radius, int depth);

  // Destructor
  ~Original();

private:

  // Draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // Member variables
  int _depth;
  float _radius;

  // Pointers to additional triangles.
  Original *_circle;
};

#endif