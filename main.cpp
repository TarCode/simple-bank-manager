#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

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
};

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

void account::showAccount() const {
    cout << "\nAccount No: " << accNo;
    cout << "\nAccount Holder: ";
    cout << name;
    cout << "\nAccount Type: " << type;
    cout << "\nBalance Amount: " << deposit;
}

void account::modify() {
    cout << "Account No: " << accNo;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Account Type: ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Account Balance: ";
    cin >> deposit;
}

void account::dep(int x) {
    deposit += x;
}

void account::draw(int x) {
    deposit -= x;
}

void account::report() const {
    cout << accNo << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retAccNo() const {
    return accNo;
}

int account::retDeposit() const {
    return deposit;
}

char account::retType() const {
    return type;
}

// Function Declarations
void write_account();
void displaySpecific(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int,int);
void intro();

int main() {
    char ch;
    int num;
    intro();

    do {
        system("clear");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        // cout << "\n\n\t02. DEPOSIT AMOUNT";
        // cout << "\n\n\t03. WITHDRAW AMOUNT";
        // cout << "\n\n\t04. BALANCE ENQUIRY";
        // cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        // cout << "\n\n\t06. CLOSE AN ACCOUNT";
        // cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";

        cin >> ch;

        system("clear");

        switch (ch) {
            case '1':
                write_account();
                break;
            case '8':
                cout << "\n\n\tThanks for using bank managemnt system";
                break;
            default:
                cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch!= '8');

    return 0;
}

// FUNCTIONS

//Intro
void intro() {
    cout << "BANK MANAGER";
    cout << "\n\nMADE BY : Tarcode";
    cin.get();
}

// Write Account
void write_account() {
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary|ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

// Display specific account
void displaySpecific(int n) {
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);

    if(!inFile) {
        cout << "File could not be opened!! Press any key...";
        return;
    }

    cout << "\nBALANCE DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        if(ac.retAccNo() == n) {
            ac.showAccount();
            flag=true;
        }
    }
    inFile.close();

    if (flag == false) {
        cout << "\nAccount number does not exist";
    }

}

void modifyAccount(int n) {
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);

    if (!File) {
        cout << "File could not be opened!! Press any key...";
        return;
    }

    while (!File.eof() && found ==false) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));

        if(ac.retAccNo() == n) {
            ac.showAccount();
            cout << "\n\nEnter the new Details of the Account"<< endl;
            ac.modify();

            int pos = (-1) *static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);

            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout << "\n\n\t Record Updated.";
            found=true;
        }
    }
    File.close();
    if(found == false) {
        cout << "\n\nRecord not found. ";
    }
}

void deleteAccount(int n) {
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!! Press any key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        if (ac.retAccNo() != n) {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted.";

}

void displayAll() {
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile) {
        cout << "File could not be opened!! Press any key..";
        return;
    }
    cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
    cout<<"####################################################\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"####################################################\n";
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
		ac.report();
	}
	inFile.close();
}