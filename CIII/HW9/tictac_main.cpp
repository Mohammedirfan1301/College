/*
    Jason Downing, Copyright (C)2014
    12/8/2014
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include "tictac_header.h"

using namespace std;

// main function
int main()
{
    Game TheGame;

    // Using the magic of inheritance and OOP, this main requires
    // just one object and a call to "PlayGame".
    // The magic stuff happens in classes Game, Board, Human & Computer
    TheGame.PlayGame();

    return 0;
}
