#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount
{
public:
	BankAccount();
	BankAccount(string set_name, double set_balance);
	string getName();
	double getBalance();
	void deposit(float amount);
	int withdraw(float amount);
	virtual void transfer(float amount, BankAccount &ToAccount);
	friend ostream& operator <<(ostream& out, const BankAccount& Acc);

protected:
	string name;
	double balance;
};


class MoneyMarketAccount :public BankAccount
{
public:
	// I was going to just reuse the BankAccount's functions, but then we have 
	// withdraws to deal with.
	MoneyMarketAccount();
	MoneyMarketAccount(string set_name, double set_balance, int set_withdraws);
	friend ostream& operator <<(ostream& out, const MoneyMarketAccount& Acc);

	// Override the withdraw function
	int withdraw(float amount);

protected:
	int withdraws;
};


class CDAccount :public BankAccount
{
public:
	// I was going to just reuse the BankAccount's functions, but then we 
	// have the interest rate to deal with.
	CDAccount();
	CDAccount(string set_name, double set_balance, float set_interest_rate);
	friend ostream& operator <<(ostream& out, const CDAccount& Acc);

	// Increase balance by doing balance += interest rate * balance
	void apply_interest();

	// Override the withdraw function
	int withdraw(float amount);
private:
	float interest_rate;
};


int main()
{
	BankAccount test("Jason", 1000.22);

	cout << "Homework 8 - Inheritance \n";

	cout << "\nTesting the Bank Account class (BEFORE): " << test;

	test.deposit(5.00);
	cout << "\nBank Account testing (added $5)" << test;

	test.deposit(-5);
	cout << "\nBank Account testing (added -$5, can't do)" << test;

	test.withdraw(15.00);
	cout << "\nBank Account testing (removed $15)" << test;

	test.withdraw(5000.0);
	cout << "\nBank Account testing (removed $5000, too much)" << test;

	// Testing the MoneyMarketAccount
	MoneyMarketAccount JAccount("John", 5.00, 0);

	cout << "\n\nTesting the Money Market Account (BEFORE): " << JAccount;

	JAccount.deposit(15.00);
	cout << "\nMoney Market Account testing (added $15)" << JAccount;

	JAccount.deposit(-5);
	cout << "\nMoney Market  Account testing (added -$5, can't do)" << JAccount;

	JAccount.withdraw(15.00);
	cout << "\nMoney Market  Account testing (removed $15)" << JAccount;

	JAccount.withdraw(5000.0);
	cout << "\nMoney Market  Account testing (removed $5000, too much)" << JAccount;

	// Testing the CDAccount
	CDAccount Fun("FUN", 50000, .1);

	cout << "\n\nTesting the CD Account (BEFORE): " << Fun;

	Fun.deposit(5.00);
	cout << "\nMoney Market Account testing (added $5)" << Fun;

	Fun.deposit(-5);
	cout << "\nMoney Market  Account testing (added -$5, can't do)" << Fun;

	Fun.withdraw(15.00);
	cout << "\nMoney Market  Account testing (removed $15)" << Fun;

	Fun.withdraw(50000.0);
	cout << "\nMoney Market  Account testing (removed $50000, too much)" << Fun;

	// Transfer tests
	// BankAccount to MoneyMarket
	cout << "\n\nTesting the transfer function:";
	cout << "\nBEFORE: (test)" << test;
	cout << "\nBEFORE: (JAccount)" << JAccount;

	test.transfer(100, JAccount);

	cout << "\nAFTER: (test)" << test;
	cout << "\nAFTER: (JAccount)" << JAccount;

	// MoneyMarket to CD
	cout << "\nBEFORE: (JAccount)" << JAccount;
	cout << "\nBEFORE: (Fun)" << Fun;

	JAccount.transfer(110, Fun);

	cout << "\nAFTER: (JAccount)" << JAccount;
	cout << "\nAFTER: (Fun)" << Fun;

	// CD to BankAccount
	cout << "\nBEFORE: (Fun)" << Fun;
	cout << "\nBEFORE: (test)" << test;

	Fun.transfer(100, test);

	cout << "\nAFTER: (Fun)" << Fun;
	cout << "\nAFTER: (test)" << test;

	// Done ^^
	return 0;
}


// Bank Account's default constructor
BankAccount::BankAccount()
{
	name = "Default";
	balance = 100;
}


// Bank Account's constructor with parameters
BankAccount::BankAccount(string set_name, double set_balance)
{
	name = set_name;
	balance = set_balance;
}


// getName function
string BankAccount::getName()
{
	// Return the name of this account
	return name;
}


// getBalance function
double BankAccount::getBalance()
{
	// Return the balance of this account
	return balance;
}


// Bank Account's deposit function
void BankAccount::deposit(float amount)
{
	// Add the amount they want into the account.
	// First make sure the amount is greater than 0
	if (amount < 0)
	{
		cout << "\nNon-zero number, transaction failed.\n";
		return;
	}

	// If we get here, good to just add the amount.
	balance += amount;
	//cout << "\nTransaction complete.\n";
}


// Bank Account's withdraw function
int BankAccount::withdraw(float amount)
{
	// Remove the amount from the account.
	// First check to see if you can remove that amount
	if (amount < 0)
	{
		cout << "\nNon-zero number, transaction failed.\n";
		return 1;
	}
	// Withdraw isn't allowed, they don't have enough money in their account.
	if ((balance - amount) < 0)   // Must be greater than 0 for it to be allowed.
	{
		cout << "\nInsufficient funds.\n";
		return 1;
	}

	balance -= amount;
	cout << "\nTransaction complete.\n";
	return 0;
}


// Bank Account's transfer function
void BankAccount::transfer(float amount, BankAccount &ToAccount)
{
	int worked = withdraw(amount);

	if (worked == 0)
	{
		ToAccount.deposit(amount);
		return;
	}
	else if (worked == 1)
	{
		cout << "\nWithdrawing failed, so transfer failed as well.\n";
		return;
	}
}


// Bank Account's << operator function
ostream& operator <<(ostream& out, const BankAccount& Acc)
{
	out << "\nAccount Name: " << Acc.name << endl;
	out << "Account Balance: " << Acc.balance << endl;

	return out;
}


// *******************************************************************
//      Money Market Account functions go here
// *******************************************************************
// Default constructor
MoneyMarketAccount::MoneyMarketAccount()
{
	name = "Default";
	balance = 100;
	withdraws = 0;
}


// Constructor with parameters
MoneyMarketAccount::MoneyMarketAccount(string set_name, double set_balance, int set_withdraws)
{
	name = set_name;
	balance = set_balance;
	withdraws = set_withdraws;
}


// << operator
ostream& operator <<(ostream& out, const MoneyMarketAccount& Acc)
{
	out << "\nAccount Name: " << Acc.name << endl;
	out << "Account Balance: " << Acc.balance << endl;
	out << "Withdraws: " << Acc.withdraws << endl;

	return out;
}


// MoneyMarket's overridden withdraw function
int MoneyMarketAccount::withdraw(float amount)
{
	// Check to see if they've used any withdraws yet.
	if (withdraws < 1)
	{
		// First check to see if you can remove that amount
		if (amount < 0)
		{
			cout << "\nNon-zero number, transaction failed.\n";
			return 1;
		}
		// Withdraw isn't allowed, they don't have enough money in their account.
		else if (balance - amount < 0)   // Must be greater than 0 for it to be allowed.
		{
			cout << "\nInsufficient funds.\n";
			return 1;
		}

		balance -= amount;
		withdraws++;
		cout << "\nTransaction complete.\n";
		return 0;
	}
	// Opps, they already used their free withdraw. Sucks for them. $1.50 fee time.
	else
	{
		// First check to see if you can remove that amount
		if (amount < 0)
		{
			cout << "\nNon-zero number, transaction failed.\n";
			return 1;
		}
		// Withdraw isn't allowed, they don't have enough money in their account.
		else if (balance - amount < 0)   // Must be greater than 0 for it to be allowed.
		{
			cout << "\nInsufficient funds.\n";
			return 1;
		}

		balance -= amount;       // Usual removal.
		balance -= 1.50;            // Don't forget the $1.50 fee!
		withdraws++;
		cout << "\nTransaction complete.\n";
		return 0;
	}
}

// *******************************************************************
//      CD Account's functions go here
// *******************************************************************
// CD Account default constructor
CDAccount::CDAccount()
{
	name = "Default";
	balance = 100;
	interest_rate = .1;
}


// CD Account constructor with parameters
CDAccount::CDAccount(string set_name, double set_balance, float set_interest_rate)
{
	name = set_name;
	balance = set_balance;
	interest_rate = set_interest_rate;
}


// << operator
ostream& operator <<(ostream& out, const CDAccount& Acc)
{
	out << "\nAccount Name: " << Acc.name << endl;
	out << "Account Balance: " << Acc.balance << endl;
	out << "Interest rate: " << Acc.interest_rate << endl;

	return out;
}


// Apply interest function
void CDAccount::apply_interest()
{
	balance += interest_rate * balance;
}


// Overridden withdraw function
int CDAccount::withdraw(float amount)
{
	// ANY withdraw gets a 25% fee, so don't bother keeping track of that.
	// Remove the amount from the account.
	// First check to see if you can remove that amount
	if (amount < 0)
	{
		cout << "\nNon-zero number, transaction failed.\n";
		return 1;
	}
	// Withdraw isn't allowed, they don't have enough money in their account.
	else if (balance - amount < 0)   // Must be greater than 0 for it to be allowed.
	{
		cout << "\nInsufficient funds.\n";
		return 1;
	}

	balance -= amount + (balance * .25);
	cout << "\nTransaction complete.\n";
	return 0;
}