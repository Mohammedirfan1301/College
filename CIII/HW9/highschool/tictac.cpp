#include <iostream.h>
#include <iomanip.h>
#include "H:\Programming\L15\TicTacToe\print.cpp"
#include "H:\Programming\L15\TicTacToe\print.h"
//5-18-2012
//due on 5-28-2012

/*
    To do:

    1. test the program, make sure it works

    Completed? Has:
    Single Player (VS Computer)
    Two Player (Human VS Human)
    Scoring system with win %

*/

int main()
{
    int z = 1;
    int e = 0;
    int moves = 0;
    int menu = 0;
    float xwins = 0;
    float owins = 0;
    float ties = 0;
    float totalgames = 0;
    float winper = 0;
    printscreen x;

    x.intro();
    cout<<"This game of TICTACTOE can be played in two ways: \n";
    cout<<"1. One Player (Human VS Computer)  \n";
    cout<<"2. Two Player (Human VS Human)     \n\n";
    cout<<"Which game type do you wish to play? \n";

    do{
    cout<<"Enter the number of your selection here. -> ";
    cin>>menu;
    }while(menu != 1 && menu != 2);

    do{
    x.cleargrid();

    if(menu == 1)
    {
        do{
        //Player X moves
        x.clearscreen();
        x.intro();
        x.map();
        x.makemoveX();
        moves++;

        if(x.test3() == 1)
        {
            x.clearscreen();
            x.intro();
            x.map();
            xwins++;
            break;
        }

        if(moves == 9 && x.test3() == 0)
        {
            x.clearscreen();
            x.intro();
            x.map();
            ties++;
            break;
        }

        //Player O (Computer) moves
        x.clearscreen();
        x.intro();
        x.map();
        x.movecomp();
        moves++;

     if(x.test3() == 2)
        {
            x.clearscreen();
            x.intro();
            x.map();
            owins++;
            break;
        }

        if(moves == 9 && x.test3() == 0)
        {
            x.clearscreen();
            x.intro();
            x.map();
            ties++;
            break;
        }

        }while(z == 1);
    }

    if(menu == 2)
    {

    do{
    //Player X moves
    x.clearscreen();
    x.intro();
    x.map();
    x.makemoveX();
    moves++;

    if(x.test3() == 1)
    {
        x.clearscreen();
        x.intro();
        x.map();
        xwins++;
        break;
    }

    if(moves == 9 && x.test3() == 0)
    {
        x.clearscreen();
        x.intro();
        x.map();
        ties++;
        break;
    }

    //Player O moves
    x.clearscreen();
    x.intro();
    x.map();
    x.makemoveO();
    moves++;

    if(x.test3() == 2)
    {
        x.clearscreen();
        x.intro();
        x.map();
        owins++;
        break;
    }

    if(moves == 9 && x.test3() == 0)
    {
        x.clearscreen();
        x.intro();
        x.map();
        ties++;
        break;
    }

    }while(z == 1);
    }

    totalgames++;

    cout<<"Well done, ";
    if(x.test3() == 0)
    cout<<"but it's a TIE! \n";
    if(x.test3() == 1)
    cout<<"X won! \n";
    if(x.test3() == 2)
    cout<<"O won! \n";

    cout<<"\nWin Percentages: \n";
    cout<<"Player 1 (X) -> ";
    winper = (xwins / totalgames) * 100;
    cout<<setprecision(4)<<winper<<"% \n";

    cout<<"Player 2 (O) -> ";
    winper = (owins / totalgames) * 100;
    cout<<setprecision(4)<<winper<<"% \n";

    cout<<"        Ties -> ";
    winper = (ties / totalgames) * 100;
    cout<<setprecision(4)<<winper<<"% \n";

    cout<<"\nPlay again? \n";
    cout<<"Enter 1 for Yes or 2 for No -> ";
    cin>>e;

    if(e == 1)
    {
    z = 1;
    moves = 0;
    }

    }while(e == 1);

    x.clearscreen();
    cout<<"\t\t    TicTacToe V1.5 \n";
    cout<<"\t\t THANKS FOR PLAYING!";

    return 0;
}

/*

Main Menu:

TicTacToe

Choose a game type:

1 Player
2 Player

Enter the # here ->

//loads into the game

 --- --- ---
| O | X | X |
|---|---|---|
| X | O | O |
|---|---|---|
| X | X | O |
 --- --- ---

*/
