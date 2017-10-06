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