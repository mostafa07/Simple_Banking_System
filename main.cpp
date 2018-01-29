#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "LinkedList.h"
#include "Account.h"
#include "Employee.h"
using namespace std;

// Global data
LinkedList<Account> accounts;
LinkedList<Employee> employees;
LinkedList<string> logEntries;
Account *currentClient;
Employee *currentEmployee;

// Macros
#define CLIENT      1
#define EMPLOYEE    2
#define OTHERWISE   0

// Functions prototypes
void saveAccountsList();
void loadAccountsList();
void saveEmployeesList();
void loadEmployeesList();
void saveIntoLog(string newEntry);
void loadLogList();

int login();
void showMenu(int who);

Account *searchAccount(string accNum);
void createAccount();
void deposit(Account &account, double value);
void withdraw(Account &account, double value);
void transferTo(Account &fromAcc, Account &toAcc, double value);
void inquireBalance(Account &account);
void modifyData(Account &account);
void showData(Account &account);
void showTransactions(Account &account);
void loan(Account &account, double value);
string generateAccNum();
string generateUserName(string fName, string lName);
string generatePassword();
void saveANDexit(int returnValue);
string getTime();
string getUser();

//////////////////////////////////////////////////////////////////////////////////
// Main function

int main() {


    cout << "**********************************************************************************************"
         << "\n\n\t\t\t\tBank Management System\t\t\t\n\n"
         << "**********************************************************************************************\n\n";

    loadAccountsList();
    loadEmployeesList();

    int who = login();
    showMenu(who);

    saveAccountsList();
    exit(0);
}



////////////////////////////////////////////////////////////////////////
// Functions implementation

void saveAccountsList() {

    // TO DO:   sort list
    ofstream fileRead("accounts.txt", ios::trunc);

    if (fileRead.is_open()){
        //cout << "Accounts File opened for saving" << endl;
        unsigned long accSize = accounts.size();
        for (int i = 0; i < accSize; ++i){
            fileRead << accounts.getAt(i).getAccNumber() << ' ' << accounts.getAt(i).getAccType() << ' '
                     << accounts.getAt(i).getFirstName() << ' ' << accounts.getAt(i).getSurName() << ' '
                     << accounts.getAt(i).getLastName() << ' ' << accounts.getAt(i).getPhoneNum() << ' '
                     << accounts.getAt(i).getUsername() << ' ' << accounts.getAt(i).getPassword() << ' '
                     << accounts.getAt(i).getDateOfBirth() << ' ' << accounts.getAt(i).getBalance() << endl;
        }

        fileRead.close();
    }
    else{
        cout << "Error: \"accounts.txt\" file not found!" << endl;
        exit(-1);
    }

}

void loadAccountsList() {

    string accNum, fName, surName, lName, phoneNum, username, password, dob;
    char accType;
    double balance;
    ifstream fileWrite("accounts.txt");

    if (fileWrite.is_open()) {
        //cout << "Accounts File opened for loading" << endl;
        while (fileWrite >> accNum >> accType >> fName >> surName >> lName
                         >> phoneNum >> username >> password >> dob >> balance) {

            Account obj;
            obj.setAccNumber(accNum);
            obj.setAccType(accType);
            obj.setFirstName(fName);
            obj.setSurName(surName);
            obj.setLastName(lName);
            obj.setPhoneNum(phoneNum);
            obj.setUsername(username);
            obj.setPassword(password);
            obj.setDateOfBirth(dob);
            obj.setBalance(balance);

            accounts.push_back(obj);
        }

        fileWrite.close();
    }
    else {
        cout << "Error: \"accounts.txt\" file not found!" << endl;
        exit(-1);
    }

}

void saveEmployeesList() {

    // TO DO:   sort list
    ofstream fileRead("employees.txt", ios::trunc);

    if (fileRead.is_open()) {
        //cout << "Employees File opened for saving" << endl;
        unsigned long empSize = employees.size();
        for (int i = 0; i < empSize; ++i) {
            fileRead << employees.getAt(i).getUsername() << ' ' << employees.getAt(i).getPassword() << endl;
        }

        fileRead.close();
    }
    else {
        cout << "Error: \"employees.txt\" file not found!" << endl;
        exit(-1);
    }

}

void loadEmployeesList() {

    string username, password;
    ifstream fileWrite("employees.txt");

    if (fileWrite.is_open()) {
        //cout << "Employees File opened for loading" << endl;
        while (fileWrite >> username >> password) {
            Employee obj;
            obj.setUsername(username);
            obj.setPassword(password);

            employees.push_back(obj);
        }

        fileWrite.close();
    }
    else {
        cout << "Error: \"employees.txt\" file not found!" << endl;
        exit(-1);
    }

}

void saveIntoLog(string newEntry) {

    ofstream fileRead("log.txt", ios::app);

    if (fileRead.is_open()) {
        fileRead << newEntry << endl;
        fileRead.close();
    }
    else {
        cout << "Error: \"log.txt\" file not found!" << endl;
        exit(-1);
    }

}

void loadLogList() {
    string line, logEntry;
    ifstream fileWrite("log.txt");

    if (fileWrite.is_open()) {
        while (getline (fileWrite, line)) {
            if (line[0] == '>') {
                logEntry = line;
            }
            else {
                logEntry = logEntry + ' ' + line;
                logEntries.push_back(logEntry);
            }
        }

        fileWrite.close();
    }
    else {
        cout << "Error: \"log.txt\" file not found!" << endl;
        exit(-1);
    }

}

int login() {

    // 1 for client, 2 for employee, 0 otherwise
    string username, password;
    cout << "Enter your login data:" << endl << "Username:\t";
    cin >> username;
    cout << "Password:\t";
    cin >> password;

    unsigned long empSize = employees.size();
    for (int i = 0; i < empSize; ++i) {
        Employee obj = employees.getAt(i);
        if (obj.getUsername() == username && obj.getPassword() == password) {
            cout << endl << "Login Successful!" << endl;
            currentEmployee = &obj;
            return EMPLOYEE;
        }
    }

    unsigned long accSize = accounts.size();
    for (int i = 0; i < accSize; ++i) {
        Account obj = accounts.getAt(i);
        if (obj.getUsername() == username && obj.getPassword() == password) {
            cout << endl << "Login Successful!" << endl;
            currentClient = &obj;
            return CLIENT;
        }
    }

    return OTHERWISE;

}

void showMenu(int who) {

    char reShow;
    do {

        if (who == EMPLOYEE) {
            short choice;
            cout << endl << "Choose one of the following:" << endl;
            cout << "\t 1. Create Account" << endl << "\t 2. Deposit" << endl << "\t 3. Withdraw" << endl
                 << "\t 4. Transfer Money" << endl << "\t 5. Inquire Balance" << endl
                 << "\t 6. Display Account Info" << endl << "\t 7. Show Transactions History" << endl
                 << "\t 8. Close Account" << endl << "\t 9. Quit Program" << endl;

            while (true) {
                cin >> choice;
                if (choice > 0 && choice < 10)
                    break;
                else
                    cout << "Retry:" << endl;
            }

            switch (choice) {
                // create account
                case (1): {
                    createAccount();

                    ostringstream logEntry;
                    logEntry << '>' << getTime() << "Account #" << currentClient->getAccNumber() << " created" << getUser();
                    saveIntoLog(logEntry.str());
                    break;
                }
                // deposit
                case (2): {
                    string accNum;
                    double value;

                    cout << "Enter Account Number: " << endl;
                    cin >> accNum;
                    currentClient = searchAccount(accNum);
                    if (currentClient == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    cout << "Enter value of money to deposit: " << endl;
                    cin >> value;
                    deposit(*currentClient, value);

                    ostringstream logEntry;
                    logEntry << '>' << getTime() << "Account #" << accNum << " made a $" << value << " deposit" << getUser();
                    saveIntoLog(logEntry.str());
                    break;
                }
                // withdraw
                case (3): {
                    string accNum;
                    double value;

                    cout << "Enter Account Number: " << endl;
                    cin >> accNum;
                    currentClient = searchAccount(accNum);
                    if (currentClient == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    cout << "Enter value of money to withdraw: " << endl;
                    cin >> value;
                    withdraw(*currentClient, value);

                    ostringstream logEntry;
                    logEntry << '>' << getTime() << "Account #" << accNum << " made a $" << value << " withdraw" << getUser();
                    saveIntoLog(logEntry.str());
                    break;
                }
                // transfer
                case (4): {
                    string fromAccNum, toAccNum;
                    double value;

                    cout << "Enter Account Number to transfer from: " << endl;
                    cin >> fromAccNum;
                    currentClient = searchAccount(fromAccNum);
                    if (currentClient == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    cout << "Enter Account Number to transfer into: " << endl;
                    cin >> toAccNum;
                    if (toAccNum == fromAccNum) {
                        cout << "Error: Invalid Operation!" << endl;
                        break;
                    }
                    Account *toAccPtr = searchAccount(toAccNum);
                    if (toAccPtr == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    cout << "Enter value of money to transfer: " << endl;
                    cin >> value;

                    transferTo(*currentClient, *toAccPtr, value);

                    ostringstream logEntry1, logEntry2;
                    logEntry1 << '>' << getTime() << "Account #" << fromAccNum << " made a $" << value
                             << " transfer to Account #" << toAccNum << getUser();
                    saveIntoLog(logEntry1.str());
                    logEntry2 << '>' << getTime() << "Account #" << toAccNum << " received a $" << value
                             << " transfer from Account #" << fromAccNum << getUser();
                    saveIntoLog(logEntry2.str());
                    break;
                }
                // inquire balance
                case (5): {
                    string accNum;
                    cout << "Enter Account Number: ";
                    cin >> accNum;
                    Account *accPtr = searchAccount(accNum);
                    if (accPtr == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    inquireBalance(*accPtr);
                    break;
                }
                // show info
                case (6): {
                    string accNum;
                    cout << "Enter Account Number: ";
                    cin >> accNum;
                    currentClient = searchAccount(accNum);
                    if (currentClient == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }
                    showData(*currentClient);
                    break;
                }
                // show transactions history
                case (7): {
                    string accNum;
                    cout << "Enter Account Number: ";
                    cin >> accNum;
                    currentClient = searchAccount(accNum);
                    if (currentClient == NULL) {
                        cout << "Error: Account doesn't exist" << endl;
                        break;
                    }

                    loadLogList();

                    unsigned long logSize = logEntries.size();
                    for (int i = 0; i < logSize; ++i) {
                        string *logEntry = &logEntries.getAt(i);
                        if ((*logEntry).find(accNum) != string::npos) {
                            cout << *logEntry << endl;
                        }
                    }

                    break;
                }
                // close account
                case (8): {
                    string accNum;
                    Account *obj;
                    unsigned long accSize = accounts.size();

                    cout << "Enter Account Number: ";
                    cin >> accNum;

                    char sure;
                    bool found = false;
                    cout << "Are you sure you want to close this account? (y/n) " << endl;
                    cin >> sure;
                    if (sure == 'y' || sure == 'Y') {
                        for (int i = 0; i < accSize; ++i) {
                            obj = &accounts.getAt(i);
                            if (obj->getAccNumber() == accNum) {
                                accounts.removeAt(i);
                                found = true;

                                ostringstream logEntry;
                                logEntry << '>' << getTime() << "Account #" << accNum << " closed" << getUser();
                                saveIntoLog(logEntry.str());
                                break;
                            }
                        }

                        if (!found) {
                            cout << "Error: Account doesn't exist" << endl;
                            break;
                        }
                    }
                    else {
                        cout << "Account Closing Canceled!" << endl;
                        break;
                    }

                    break;
                }
                // quit program
                case (9): {
                    saveANDexit(0);
                }
                default:
                    break;
            }

            currentClient = NULL;

            cout << endl << "Press any character for more operations, Q to quit Program" << endl;
            cin >> reShow;
        }
        else if (who == CLIENT) {

            short choice;
            cout << endl << "Choose one of the following:" << endl;
            cout << "\t 1. Inquire Balance" << endl << "\t 2. Display Account Info" << endl
                 << "\t 3. Show Transactions History" << endl << "\t 4. Quit Program" << endl;

            while (true) {
                cin >> choice;
                if (choice > 0 && choice < 5)
                    break;
                else
                    cout << "Retry:" << endl;
            }

            switch (choice) {
                // inquire balance
                case (1): {
                    inquireBalance(*currentClient);
                    break;
                }
                // show info
                case (2): {
                    showData(*currentClient);
                    break;
                }
                // show transactions history
                case (3): {
                    string accNum = currentClient->getAccNumber();
                    loadLogList();

                    unsigned long logSize = logEntries.size();
                    for (int i = 0; i < logSize; ++i) {
                        string *logEntry = &logEntries.getAt(i);
                        if ((*logEntry).find(accNum) != string::npos) {
                            cout << *logEntry << endl;
                        }
                    }
                    break;
                }
                // quit program
                case (4): {
                    saveANDexit(0);
                }
                default:
                    break;
            }

            cout << endl << "Press any character for more operations, Q to quit Program" << endl;
            cin >> reShow;
        }
        else {
            cout << endl << "Incorrect Login Data" << endl
                 << "Please refer to the nearest bank in case you are a new client" << endl;
        }

    } while( !(reShow == 'q' || reShow == 'Q') && who != OTHERWISE );

}

Account *searchAccount(string accNum) {
    unsigned long accSize = accounts.size();
    for (int i = 0; i < accSize; ++i) {
        Account *obj = &accounts.getAt(i);
        if (obj->getAccNumber() == accNum)
            return obj;
    }
    return NULL;
}

void createAccount() {

    string input;
    char accType;
    double balance;
    Account newAccount;

    cout << "Account Creation Form:" << endl << "First Name: ";
    cin >> input;
    newAccount.setFirstName(input);
    cout << "Sur Name: ";
    cin >> input;
    newAccount.setSurName(input);
    cout << "Last Name: ";
    cin >> input;
    newAccount.setLastName(input);

    cout << "Choose Account Type:\t'C' for Checking Account or 'S' for Savings Account: ";
    while (true) {
        cin >> accType;
        if (accType == 'c' || accType == 'C') {
            newAccount.setAccType('C');
            break;
        }
        else if (accType == 's' || accType == 'c') {
            newAccount.setAccType('S');
            break;
        }
        else
            cout << "Retry: ";
    }

    cout << "Birth Date:\t(DD/MM/YYYY): ";
    cin >> input;
    newAccount.setDateOfBirth(input);

    cout << "Mobile Number: ";
    while (true) {
        cin >> input;
        if (input[0] != '0' || input.length() != 11)
            cout << "Retry: ";
        else
            break;
    }
    newAccount.setPhoneNum(input);

    cout << "Enter Starting Balance to Create Account: " << endl << "(Note: Minimum Starting balance is $5000) ";
    while (true) {
        cin >> balance;
        if (balance < 5000.0)
            cout << "Invalid! Retry: ";
        else
            break;
    }
    newAccount.setBalance(balance);

    newAccount.setAccNumber( generateAccNum() );
    string username = generateUserName(newAccount.getFirstName(), newAccount.getLastName());
    newAccount.setUsername( username );
    newAccount.setPassword( generatePassword() );

    accounts.push_back(newAccount);
    currentClient = &accounts.getAt(accounts.size() - 1);
}

void deposit(Account &account, double value) {
    if (value < 0)
        cout << "Error: Invalid Operation" << endl;
    else if (value < 100)
        cout << "Error: Minimun amount to deposit is $100" << endl;
    else
        account.setBalance( account.getBalance() + value );
}

void withdraw(Account &account, double value) {
    if (value < 0)
        cout << "Error: Invalid Operation" << endl;
    else if (value < 500)
        cout << "Error: Minimun amount to withdraw is $500" << endl;
    else if (account.getBalance() - value < 5000)
        cout << "Error: Balance can't be lower than $5000" << endl;
    else
        account.setBalance( account.getBalance() - value );
}

void transferTo(Account &fromAcc, Account &toAcc, double value) {
    if (value < 0)
        cout << "Error: Invalid Operation" << endl;
    else if (value < 500)
        cout << "Error: Minimun amount to withdraw is $500" << endl;
    else if (fromAcc.getBalance() - value < 5000)
        cout << "Error: Balance can't be lower than $5000" << endl;
    else {
        fromAcc.setBalance( fromAcc.getBalance() - value );
        toAcc.setBalance( toAcc.getBalance() + value );
    }
}

void inquireBalance(Account &account) {
    cout << endl << "Account:\t#" << account.getAccNumber() << endl
         << "Balance Available:\t$" << account.getBalance() << endl;
}

void modifyData(Account &account) {

}

void showData(Account &account) {
    cout << account << endl;
}

void showTransactions(Account &account) {

}

void loan(Account &account, double value) {
    account.setBalance( account.getBalance() + value );
}

string generateAccNum() {
    ostringstream os;
    srand(time(NULL));
    for (int i = 0; i < 9; ++i)
    {
        int digit = rand() % 10;
        os << digit;
    }
    string accNum = os.str();

    int accSize = accounts.size();
    for (int i = 0; i < accSize; ++i) {
        if (accounts.getAt(i).getAccNumber() == accNum || accNum[0] == '0')
            generateAccNum();
    }

    return accNum;
}

string generateUserName(string fName, string lName) {
    int fSize = fName.length(), lSize = lName.length();
    for (int i = 0; i < fSize; ++i)
        fName[i] = (char) tolower(fName[i]);
    for (int i = 0; i < lSize; ++i)
        lName[i] = (char) tolower(lName[i]);
    string username = fName + lName;

    int accSize = accounts.size();
    for (int i = 0; i < accSize; ++i) {
        if (accounts.getAt(i).getUsername() == username) {
            username = username + "1";
            break;
        }
    }

    return username;
}

string generatePassword() {
    ostringstream os;
    srand(time(NULL));
    for (int i = 0; i < 8; ++i)
    {
        int digit = rand() % 10;
        os << digit;
    }
    string password = os.str();

    int accSize = accounts.size();
    for (int i = 0; i < accSize; ++i) {
        if (accounts.getAt(i).getPassword() == password)
            generatePassword();
    }

    return password;
}

void saveANDexit(int returnValue) {
    saveAccountsList();
    exit(returnValue);
}

string getTime() {
    time_t now = time(0);
    return ctime(&now);
}

string getUser() {
    string user;
    if (currentEmployee == NULL) {
        user = " | Client Username: ";
        user = user + currentClient->getUsername();
        return user;
    } else {
        user = " | Employee Username: ";
        user = user + currentEmployee->getUsername();
        return user;
    }
}
