#include <iostream>

using namespace std;


class ComputerLabs()
{
    public:
        ComputerLabs();
        void show_labs();
        void login();
        void logoff();
        void search_user();
        void addLab();
        void removeLab();
        void removeComp();

    private:
        /*  2D vector of strings
            Basically:
            first [] is a vector (lab) of computers
            second [] is a specific computer in that lab    */
        vector < vector <string> > labs;
};


int main()
{
    ComputerLabs computer_lab;

    int ans = 1;
    do{
        cout << "Please enter one of the following options \n";
        cout << "1) Display all the labs, computers, and users \n";
        cout << "2) Login \n";
        cout << "3) Logoff \n";
        cout << "4) Search user \n";
        cout << "5) Add a computer \n";
        cout << "6) Add a lab \n";
        cout << "7) Remove a computer \n";
        cout << "8) Remove a lab \n";
        cout << "9) Quit \n";
        cout << "Enter your selection: ";
        cin  >> ans;

        switch(ans)
        {
            case 1:

            case 2:

            case 3:

            case 4:

            case 5:

            case 6: 

            case 7:

            case 8:

            case 9:

            default:
                cout << "Error, you entered invalid input! \n";
        }
    }while(ans != 0);

	return 0;
}


ComputerLabs::ComputerLabs()
{
    cout << "Making a computer lab. \n";

}


void ComputerLabs::show_labs()
{
    cout << "Showing all labs. \n";

}

void ComputerLabs::login()
{
    cout << "Logging in. \n";

}


void ComputerLabs::logoff()
{
    cout << "Logging off a user. \n";

}


void ComputerLabs::search_user()
{
    cout << "Searching for user \n";

}


void ComputerLabs::addLab()
{
    cout << "Adding a lab. \n";

}


void ComputerLabs::removeLab()
{
    cout << "Removing a lab. \n";

}


void ComputerLabs::removeComp()
{
    cout << "Removing a computer. \n";

}