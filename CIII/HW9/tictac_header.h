
// Abstract Player Class. Child classes: Computer, Human.
class AbstractPlayer: public Game
{
public:
  virtual void selectPiece();
  virtual void move();
};
