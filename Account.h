//
// Created by Mostafa Mahmoud on 5/7/2017.
//

#ifndef DS_PROJECT_BANKING_SYSTEM_ACCOUNT_H
#define DS_PROJECT_BANKING_SYSTEM_ACCOUNT_H

#include <iostream>
using namespace std;

class Account {

private:
    string accNumber;
    char accType;
    string firstName;
    string surName;
    string lastName;
    string phoneNum;
    string username;
    string password;
    string dateOfBirth;
    double balance;

public:
    // Constructors and destructor  (create_account() will replace constructor)

    Account();

    Account(const string &accNumber, char accType, const string &firstName, const string &surName,
            const string &lastName, const string &phoneNum, const string &username, const string &password,
            const string &dateOfBirth, double balance);

    /////////////////////////////////////////////////////////////////////////////////
    // Setters and getters

    const string &getAccNumber() const;

    void setAccNumber(const string &accNumber);

    char getAccType() const;

    void setAccType(char accType);

    const string &getFirstName() const;

    void setFirstName(const string &firstName);

    const string &getSurName() const;

    void setSurName(const string &surName);

    const string &getLastName() const;

    void setLastName(const string &lastName);

    const string &getPhoneNum() const;

    void setPhoneNum(const string &phoneNum);

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getDateOfBirth() const;

    void setDateOfBirth(const string &dateOfBirth);

    double getBalance() const;

    void setBalance(double balance);

    // << operator for printing using cout
    // password omitted so that employee can't show it
    friend ostream &operator<<(ostream &os, const Account &account);

    //////////////////////////////////////////////////////////////////////////
    // Other methods


};


#endif //DS_PROJECT_BANKING_SYSTEM_ACCOUNT_H
