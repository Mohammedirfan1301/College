#include "game_includes.h"

Game::Game()
{
  response = ' ';
  number = 0;
  firstMove = ' ';
  move = 0;
  low = 1;
  high = 9;
  Game_Board = new Board();
  Player = new AbstractPlayer();
  CPU = new Computer();
  The_Human = new Human();
}


void Game::instructions()
{
  cout << "Welcome to tic-tac-toe.\n";
  cout << "This will be a friendly battle of human vs computer.\n\n";

  cout << "Make your move by entering a number, 1 - 9.  The number\n";
  cout << "corresponds to the desired board position, as illustrated:\n\n";

  // I'm changing this because the original game was very counterintuitive
  cout << "       7 | 8 | 9\n";
  cout << "      -----------\n";
  cout << "       4 | 5 | 6\n";
  cout << "      -----------\n";
  cout << "       1 | 2 | 3\n\n";

  cout << "Prepare yourself.  The battle is about to begin.\n\n";
}


void Game::askYesNo(void)
{
  do{
    cout << "Do you want to make the first move? (y/n): ";
    cin >> response;
  }while (response != 'y' && response != 'n');
}


void Game::askNumber(void)
{
  cout << "Where will you move? -> ";
  cin >> number;
}


void Game::announceWinner(int Winner)
{
  switch(Winner)
{
  case 1:
  cout << "The Computer won!\n";
  cout << "As I predicted, human, I am triumphant once more -- proof\n";
  cout << "that computers are superior to humans in all regards.\n";
  break;

  case 2:
  cout << "You won!\n";
  cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
  cout << "But never again!  I, the computer, so swear it!\n";
  break;

  case 3:
  cout << "It's a tie.\n";
  cout << "You were most lucky, human, and somehow managed to tie me.\n";
  cout << "Celebrate... for this is the best you will ever achieve.\n";
  break;
}
}
