#include <iostream>
#include <vector>

// Avoid typing std:: everywhere
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

class ComputerLabs
{
    public:
        ComputerLabs();
        void show_labs(void);
        void login(void);
        void logoff(void);
        void searchUser(void);
        void addLab(void);
        void addComp(void);
        void removeLab(void);
        void removeComp(void);

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

    int ans;
    do{
        cout << "\nPlease enter one of the following options \n";
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
                computer_lab.show_labs();
                break;

            case 2:
                computer_lab.login();
                break;

            case 3:
                computer_lab.logoff();
                break;

            case 4:
                computer_lab.searchUser();
                break;

            case 5:
                computer_lab.addComp();
                break;

            case 6: 
                computer_lab.addLab();                
                break;

            case 7:
                computer_lab.removeComp();
                break;

            case 8:
                computer_lab.removeLab();
                break;

            case 9:
                cout << "\nQuitting the program...\n";
                break;

            default:
                cout << "\n*********************************\n";
                cout << "Error, you entered invalid input!\n";
                cout << "*********************************\n";
                break;
        }

    }while(ans != 9);

	return 0;
}


ComputerLabs::ComputerLabs()
{
    int column, row;

    // User input
    cout << "How many labs should I create?\nEnter an integer here: ";
    cin >> column;

    cout << "\nHow many computer should each lab have?\nEnter an integer here: ";
    cin >> row;

    cout << "\nCreating " << column << " labs and each lab will have " << row << " computers.\n";
    
    // Dynamically create the vector of vectors here. 
    // Making a column by row vector of vector of strings.
    for(int x = 0; x < column; x++)
    {
        // Make a new vector of strings
        vector <string> newlab;
        labs.push_back(newlab);

        for(int y = 0; y < row; y++)
        {
            labs[x].push_back("empty");
        }
    }
}


void ComputerLabs::show_labs(void)
{
    // Print out these before the loop so they don't show up all the time.
    cout << "\nComputer Lab Display System\n";
    cout << "Labs:\tComputers:\n";

    // This goes through and prints all the labs / computers out.
    for(int x = 0; x < labs.size(); x++)
    {
        cout << x << ":\t";
        for(int y = 0; y < labs[x].size(); y++)
        {
            cout << y << ": " << labs[x][y] << " ";
        }
        cout << endl;
    }
}


void ComputerLabs::login(void)
{
    string user_ID;
    int lab_num, comp_num;

    // User input
    cout << "\nComputer Lab Login System\n";
    
    cout << "Please enter your user ID: ";
    cin >> user_ID;
    cin.ignore();

    cout << "Please enter the lab number: ";
    cin >> lab_num;

    cout << "Please enter the computer number: ";
    cin >> comp_num;

    // Check for errors first.
    if(lab_num >= labs.size() || lab_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that lab number doesn't exist.\n";

        // We alerted the user, so exit from this function.
        return;
    }
    else if(comp_num >= labs[lab_num].size() || comp_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that computer number is too high to insert at.\n";

        cout << "Comp number: " << comp_num << "lab number: " << lab_num << endl;

        // We alerted the user, so exit from this function.
        return;
    }    // Set that user_ID to that specific computer

    labs[lab_num][comp_num] = user_ID;
}


void ComputerLabs::logoff(void)
{
    // User input
    cout << "\nComputer Lab Logoff System\n";
    string user_ID;

    cout << "Please enter your user ID: ";
    cin >> user_ID;
    cin.ignore();

    // Search for this user_ID
    for(int x = 0; x < labs.size(); x++)
    {
        for(int y = 0; y < labs[x].size(); y++)
        {
            // We found the USER ID in the vector!
            if(labs[x][y] == user_ID)
            {
                // Let the user know we're removing that ID, and then set that
                // spot in the vector equal to "empty"
                cout << "Removing " << user_ID << " from the computer system.\n";
                labs[x][y] = "empty";

                // Let's exit the function, since we found the user ID.
                return;
            }
        }
    }

    // If we get here, we came up empty handed. :(
    cout << "\nSorry, I couldn't find that user ID!\n";
}


void ComputerLabs::searchUser(void)
{
    // User input
    cout << "\nComputer Lab Search System\n";
    string user_ID;

    cout << "Please enter your user ID: ";
    cin >> user_ID;
    cin.ignore();

    // Search for this user_ID
    for(int x = 0; x < labs.size(); x++)
    {
        for(int y = 0; y < labs[x].size(); y++)
        { 
            // We found the USER ID in the vector!
            if(labs[x][y] == user_ID)
            {
                // We found it!
                cout << "\nFound the user ID: " << user_ID << endl;
                cout << "Currently logged into computer " << y << " in lab " << x << endl;

                // Let's exit the function, since we found the user ID.
                return;
            }
        }
    }

    // If we get here, we came up empty handed. :(
    cout << "\nSorry, I couldn't find that user ID!\n";
}


void ComputerLabs::addLab(void)
{
    int lab_num, comp_num;

    // User input
    cout << "\nComputer Lab Add Lab System\n";
    cout << "Enter the position you'd like to add a lab at: ";
    cin >> lab_num;

    cout << "Enter the number of computers this lab should have: ";
    cin >> comp_num;

    // Check the bounds, make sure the number isn't too large or too small.
    // The user should be able to insert a computer at the beginning, middle
    // or very end of the vector.
    if(lab_num > labs.size() || lab_num < 0)
    {
        // Too large or is a negative number.
        cout << "\nSorry, that lab number is either too high to insert at\n";
        cout << "or is a negative number.\n";

        // We alerted the user, so exit from this function.
        return;
    }

    // Make a new vector of strings
    vector <string> newlab;

    for(int y = 0; y < comp_num; y++)
    {
        newlab.push_back("empty");
    }

    // Rather using push_back, use insert to insert at a given position.
    // This will push all the other labs forward one.
    labs.insert(labs.begin() + lab_num, newlab);
}


void ComputerLabs::addComp(void)
{
    int lab_num, comp_num;

    // User input
    cout << "\nComputer Lab Add Computer System\n";
    cout << "Enter the lab you'd like to add a computer at: ";
    cin >> lab_num;

    cout << "Enter the position you'd like to insert the computer at: ";
    cin >> comp_num;

    // Check the bounds, make sure the number isn't too large or too small.
    // The user should be able to insert a computer at the beginning, middle
    // or very end of the vector.
    if(lab_num > labs.size() || lab_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that lab number doesn't exist.\n";

        // We alerted the user, so exit from this function.
        return;
    }
    else if(comp_num > labs[lab_num].size() || comp_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that computer number is too high to insert at.\n";

        // We alerted the user, so exit from this function.
        return;
    }

    // Rather using push_back, use insert to insert at a given position.
    // This will push all the other computers forward one.
    labs[lab_num].insert(labs[lab_num].begin() + comp_num, "empty");
}


void ComputerLabs::removeLab(void)
{
    int lab_num;

    // User input
    cout << "\nComputer Lab Remove Lab System\n";
    cout << "Enter a lab to remove: ";
    cin >> lab_num;

    /* 
        Check the bounds
        In general, we should make sure that the lab number / computer number is
        less than the total size of the number of labs / computers minus 1.
        One easy way to catch this is to see if the lab / computer number is greater than
        or equal to size. If this is true, then the lab / computer does not exist.
        Also, we can't have negative positions in vectors so check for negative numbers too.
    */
    if(lab_num >= labs.size() || lab_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that lab number doesn't exist.\n";

        // We alerted the user, so exit from this function.
        return;
    }

    // If we get here, we're safe to remove the computer from the vector.
    cout << "\nRemoving lab number " << lab_num << " from the computer system.\n";

    // This will remove the given lab and push every other lab forward one.
    labs.erase(labs.begin() + lab_num);
}


void ComputerLabs::removeComp(void)
{
    int lab_num, comp_num;

    // User input
    cout << "\nComputer Lab Remove Computer System\n";
    cout << "Enter a computer and its location to remove it.\n";

    cout << "Enter the computer's lab number: ";
    cin >> lab_num;

    cout << "Enter the computer's number: ";
    cin >> comp_num;

    /* 
        Check the bounds
        In general, we should make sure that the lab number / computer number is
        less than the total size of the number of labs / computers minus 1.
        One easy way to catch this is to see if the lab / computer number is greater than
        or equal to size. If this is true, then the lab / computer does not exist.
        Also, we can't have negative positions in vectors so check for negative numbers too.
    */
    if(lab_num >= labs.size() || lab_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that lab number doesn't exist.\n";

        // We alerted the user, so exit from this function.
        return;
    }

    // Assuming the above didn't force us to quit, we can check the specific lab vector.
    else if(comp_num >= labs[lab_num].size() || comp_num < 0)
    {
        // Too large, so it can't exist.
        cout << "\nSorry, that computer number doesn't exist.\n";

        // We alerted the user, so exit from this function.
        return;
    }

    // If we get here, we're safe to remove the computer from the vector.
    cout << "\nRemoving computer " << comp_num << " from lab number " << lab_num << ".\n";

    // This will remove the given lab and push every other lab forward one.
    labs[lab_num].erase(labs[lab_num].begin() + comp_num);
}
