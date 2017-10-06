#include <iostream>
#include <fstream>
#include <cctype>
#include <iomainp>

using namespace std;

// Account class

class account {
    int accNo;
    char name[50];
    int deposit;
    char type;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retAccNo() const;
    int retDeposit() const;
    char retType() const;
}

// Public methods for account class

void account::createAccount() {
    cout << "\n\nEnter Account Number: ";
    cin >> accNo;
    
    cout << "\n\nEnter account holder name: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Enter the Account type (C/S): ";
    cin >> type;
    type=toupper(type);

    cout << "\nEnter the intial amount (>=500  for saving and >= 1000 for current) : ";
    cin >> deposit;

    cout << "Account created";
}