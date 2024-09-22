#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;

#define MIN_BALANCE 500 // Define the minimum balance allowed for an account

// Custom exception class for handling insufficient funds scenario
class InsufficientFunds{};

// Account class to represent a bank account
class Account {
private:
    long accountNumber; // Unique account number for each account
    string firstName;   // Account holder's first name
    string lastName;    // Account holder's last name
    float balance;      // Current balance in the account
    static long NextAccountNumber; // Static member to track the next account number
public:
    // Default constructor
    Account() {}

    // Parameterized constructor
    Account(string fname, string lname, float balance);

    // Getters for account properties
    long getAccNo() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }

    // Functions for deposit and withdrawal
    void Deposit(float amount);
    void Withdraw(float amount);

    // Static functions to get and set the last account number
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();

    // Overloading the << and >> operators for file I/O
    friend ofstream& operator<<(ofstream& ofs, Account& acc);
    friend ifstream& operator>>(ifstream& ifs, Account& acc);
    friend ostream& operator<<(ostream& os, Account& acc);
};

long Account::NextAccountNumber = 0; // Initializing static member

// Bank class to handle multiple accounts
class Bank {
private:
    map<long, Account> accounts; // Map to store all accounts by account number
public:
    Bank(); // Constructor
    Account OpenAccount(string fname, string lname, float balance); // Function to open an account
    Account BalanceEnquiry(long accountNumber); // Function to check account balance
    Account Deposit(long accountNumber, float amount); // Function to deposit money
    Account Withdraw(long accountNumber, float amount); // Function to withdraw money
    void CloseAccount(long accountNumber); // Function to close an account
    void ShowAllAccounts(); // Function to display all accounts
    ~Bank(); // Destructor
};

// Main function to drive the banking system
int main() {
    Bank b;
    Account acc;

    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;
    cout << "***Banking System***" << endl;

    // Loop to keep the system running until user quits
    do {
        cout << "\n\tSelect one option below ";
        cout << "\n\t1 Open an Account";
        cout << "\n\t2 Balance Enquiry";
        cout << "\n\t3 Deposit";
        cout << "\n\t4 Withdrawal";
        cout << "\n\t5 Close an Account";
        cout << "\n\t6 Show All Accounts";
        cout << "\n\t7 Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                cout << "Enter initial Balance: ";
                cin >> balance;
                acc = b.OpenAccount(fname, lname, balance);
                cout << endl << "Congratulations! Account is Created" << endl;
                cout << acc;
                break;

            case 2:
                cout << "Enter Account Number:";
                cin >> accountNumber;
                acc = b.BalanceEnquiry(accountNumber);
                cout << endl << "Your Account Details" << endl;
                cout << acc;
                break;

            case 3:
                cout << "Enter Account Number:";
                cin >> accountNumber;
                cout << "Enter Amount:";
                cin >> amount;
                acc = b.Deposit(accountNumber, amount);
                cout << endl << "Amount is Deposited" << endl;
                cout << acc;
                break;

            case 4:
                cout << "Enter Account Number:";
                cin >> accountNumber;
                cout << "Enter Amount:";
                cin >> amount;
                acc = b.Withdraw(accountNumber, amount);
                cout << endl << "Amount Withdrawn" << endl;
                cout << acc;
                break;

            case 5:
                cout << "Enter Account Number:";
                cin >> accountNumber;
                b.CloseAccount(accountNumber);
                cout << endl << "Account is Closed" << endl;
                break;

            case 6:
                b.ShowAllAccounts();
                break;

            case 7:
                break;

            default:
                cout << "\nEnter correct choice";
                exit(0);
        }
    } while (choice != 7);

    return 0;
}

// Parameterized constructor for Account class
Account::Account(string fname, string lname, float balance) {
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}

// Function to deposit an amount
void Account::Deposit(float amount) {
    balance += amount;
}

// Function to withdraw an amount
void Account::Withdraw(float amount) {
    if (balance - amount < MIN_BALANCE)
        throw InsufficientFunds();
    balance -= amount;
}

// Setter for the last account number
void Account::setLastAccountNumber(long accountNumber) {
    NextAccountNumber = accountNumber;
}

// Getter for the last account number
long Account::getLastAccountNumber() {
    return NextAccountNumber;
}

// Overloading << operator for file output
ofstream& operator<<(ofstream& ofs, Account& acc) {
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}

// Overloading >> operator for file input
ifstream& operator>>(ifstream& ifs, Account& acc) {
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}

// Overloading << operator for console output
ostream& operator<<(ostream& os, Account& acc) {
    os << "First Name: " << acc.getFirstName() << endl;
    os << "Last Name: " << acc.getLastName() << endl;
    os << "Account Number: " << acc.getAccNo() << endl;
    os << "Balance: " << acc.getBalance() << endl;
    return os;
}

// Constructor for Bank class to initialize accounts from file
Bank::Bank() {
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile) {
        return;
    }

    while (!infile.eof()) {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());

    infile.close();
}

// Function to open a new account
Account Bank::OpenAccount(string fname, string lname, float balance) {
    ofstream outfile;
    Account account(fname, lname, balance);
    accounts.insert(pair<long, Account>(account.getAccNo(), account));

    outfile.open("Bank.data", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        outfile << itr->second;
    }
    outfile.close();
    return account;
}

// Function to check balance of an account
Account Bank::BalanceEnquiry(long accountNumber) {
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}

// Function to deposit an amount into an account
Account Bank::Deposit(long accountNumber, float amount) {
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}

// Function to withdraw an amount from an account
Account Bank::Withdraw(long accountNumber, float amount) {
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

// Function to close an account
void Bank::CloseAccount(long accountNumber) {
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    cout << "Account Deleted: " << itr->second;
    accounts.erase(accountNumber);
}

// Function to display all accounts
void Bank::ShowAllAccounts() {
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        cout << "Account " << itr->first << endl << itr->second << endl;
    }
}

// Destructor for Bank class to save all account data before closing the application
Bank::~Bank() {
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        outfile << itr->second;
    }
    outfile.close();
}
