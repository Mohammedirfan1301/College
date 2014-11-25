#include <iostream>
using namespace std;

class BankAccount
{
    public:
        BankAccount();
        BankAccount(string set_name, double set_balance);
        string getName();
        double getBalance();
        void deposit(float amount);
        void withdraw(float amount);
        void transfer(float amount, BankAccount &ToAccount);

    private:
        string name;
        double balance;
};


class MoneyMarketAccount: public BankAccount
{
    public:
        int num_of_withdrawls;

        // Override the withdraw function?
};


class CDAccount: public BankAccount
{
    public:
        float interest_rate;
        void apply_interest();      // increase balance by doing balance += interest rate * balance
};


int main()
{
    BankAccount test("Jason", 1000.22);
    string the_name;
    double balance;

    the_name = test.getName();
    balance = test.getBalance();

    cout << "Your name is: " << the_name << endl;
    cout << "Your balance is: " << balance << endl;

    // Add like $5
    test.deposit(5.00);
    balance = test.getBalance();
    cout << "Your balance is: " << balance << endl;

    // Remove like $5
    test.withdraw(5.00);
    balance = test.getBalance();
    cout << "Your balance is: " << balance << endl;


    return 0;
}


BankAccount::BankAccount(string set_name, double set_balance)
{
    name = set_name;
    balance = set_balance;
}


string BankAccount::getName()
{
    // Return the name of this account
    return name;
}


double BankAccount::getBalance()
{
    // Return the balance of this account
    return balance;
}


void BankAccount::deposit(float amount)
{
    // Add the amount they want into the account.
    balance += amount;
}

void BankAccount::withdraw(float amount)
{
    // Remove the amount from the account.
    balance -= amount;
}