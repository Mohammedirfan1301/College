#include <conio.h>
#include <iostream.h>
#include <iomanip.h>
#include <string.h>

char real[30] = {"random word here"};
char gues[30] = {'\0'};
char input[30] = {'\0'};
char g;
int a = 0, b = 0;
int c = 0, d = 0;
int x = 1, y = 1, z = 0;
int result = 0;

void printman(void);
void print(void);
void guess(void);
void compare(void);
void loser(void);
void winner(void);

main()
{
    do{
        memset(input, '\0', 30);
        memset(gues, '\0', 30);
        result = 0;
        y = 1;
        z = 0;
    do{
    cout<<"\t\t HANGMAN V2.1 \n\n";
    cout<<"\tWELCOME TO THE AWESOME HANGMAN GAME! \n";

    printman();
    
    cout<<"The word is: ";
    print();
    
    cout<<"\n\nGuess a letter: ";
    guess();
    compare();
    
    system("cls");
        
    }while(result == 0);
    
    if(result == 1)
        loser();
    if(result == 2)
        winner();
    
    do{
    cout<<"To restart the program, enter 1. To end the program, enter 2. -> ";
    cin>>x;
    }while(x != 1 && x != 2);
    system("cls");
    }while(x == 1);
    
    return 0;    
}

void printman(void)
{
    switch(y)
    {
        case 1:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;   
            
        case 2:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O   \n";
                cout<<"|     \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
            
        case 3:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O  \n";
                cout<<"|  |  \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
                
        case 4:
                cout<<"____  \n";
                cout<<"|  |  \n";
                cout<<"|  O  \n";
                cout<<"| /|  \n";
                cout<<"|     \n";
                cout<<"|________ \n\n";
                break;
            
        case 5:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"|      \n";
                cout<<"|________ \n\n";
                break;
            
        case 6:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"| /    \n";
                cout<<"|________ \n\n";
                break;
            
        case 7:
                cout<<"____   \n";
                cout<<"|  |   \n";
                cout<<"|  O   \n";
                cout<<"| /|\\ \n";
                cout<<"| / \\  \n";
                cout<<"|________ \n\n";
                cout<<"OH NO! HE DIED! \n";
                cout<<"YOU MONSTER! YOU KILLED HANGMAN! \n";
                break;
        default:
                cout<<"ERROR! \n";
                break;
    }   
}

void print(void)
{
    c = strlen(real);
    
    if(input[0] == '\0')
    {
    
        for(a = 0; a < c; a++)
        {
            if(real[a] != 32)
                cout<<"*";
            if(real[a] == 32)
                cout<<" ";
        }
    }
    
    
        for(a = 0; a < c; a++)
        {    
            cout<<gues[a];
        }
    
    
    cout<<"\n\nLETTERS GUESSED: ";
    
    for(a = 0; a < c; a++)
        cout<<input[a]<<" ";
}

void guess(void)
{
    cin>>input[z];
    z++;
}

void compare(void)
{
    b = 0;
    
    for(a = 0; a < c; a++)
    {
        if(real[a] != 32)
        {
            if(input[z-1] == real[a])
            {
                gues[a] = real[a];
                b++;
            }
        }
        
        if(real[a] == 32)
            gues[a] = ' ';
    }
    
    if(b == 0)
        y++;
        
    if(b == 0 && y == 7)
    {
        print();
        result = 1;
    }
       
    if(strncmp(gues, real, c) == 0)
        result = 2;          
}

void loser(void)
{
    cout<<"\t\t HANGMAN V2.1 \n";
    
    cout<<"____   \n";
    cout<<"|  |   \n";
    cout<<"|  O   \n";
    cout<<"| /|\\ \n";
    cout<<"| / \\  \n";
    cout<<"|________ \n\n";
    
    cout<<"OH DANG! YOU LOSE! FAILURE!! \n";
    cout<<"I mean, come on. YOU killed HANGMAN! \n";
    cout<<"Go die in a hole. \n\n";
}

void winner(void)
{
    cout<<"\t\t HANGMAN V2.1 \n\n";
    
    printman();
    
    cout<<"The word is: "<<real<<"\n\n";
    
    cout<<"CONGRATS! YOU WON! THE HANGMAN IS SAVED!!! \n";
    cout<<"Your prize is: NOTHING. \n";
    cout<<"HAVE A NICE DAY! \n\n";   
}
