//
// Created by Mostafa Mahmoud on 5/7/2017.
//

#include "Account.h"

// Constructors and destructor

Account::Account() {}

Account::Account(const string &accNumber, char accType, const string &firstName, const string &surName,
                 const string &lastName, const string &phoneNum, const string &username, const string &password,
                 const string &dateOfBirth, double balance) : accNumber(accNumber), accType(accType),
                                                              firstName(firstName), surName(surName),
                                                              lastName(lastName), phoneNum(phoneNum),
                                                              username(username), password(password),
                                                              dateOfBirth(dateOfBirth), balance(balance) {}

// Setters and getters

const string &Account::getAccNumber() const {
    return accNumber;
}

void Account::setAccNumber(const string &accNumber) {
    Account::accNumber = accNumber;
}

char Account::getAccType() const {
    return accType;
}

void Account::setAccType(char accType) {
    Account::accType = accType;
}

const string &Account::getFirstName() const {
    return firstName;
}

void Account::setFirstName(const string &firstName) {
    Account::firstName = firstName;
}

const string &Account::getSurName() const {
    return surName;
}

void Account::setSurName(const string &surName) {
    Account::surName = surName;
}

const string &Account::getLastName() const {
    return lastName;
}

void Account::setLastName(const string &lastName) {
    Account::lastName = lastName;
}

const string &Account::getPhoneNum() const {
    return phoneNum;
}

void Account::setPhoneNum(const string &phoneNum) {
    Account::phoneNum = phoneNum;
}

const string &Account::getUsername() const {
    return username;
}

void Account::setUsername(const string &username) {
    Account::username = username;
}

const string &Account::getPassword() const {
    return password;
}

void Account::setPassword(const string &password) {
    Account::password = password;
}

const string &Account::getDateOfBirth() const {
    return dateOfBirth;
}

void Account::setDateOfBirth(const string &dateOfBirth) {
    Account::dateOfBirth = dateOfBirth;
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double balance) {
    Account::balance = balance;
}

// password omitted so that employee can't show it
ostream &operator<<(ostream &os, const Account &account) {
    os << "Account Number: " << account.accNumber << "\nAccount Type: " << account.accType
       << "\nName: " << account.firstName << ' ' << account.surName << ' ' << account.lastName
       << "\nPhone Number: " << account.phoneNum << "\nUsername: " << account.username
       << "\nDate of Birth: " << account.dateOfBirth << "\nBalance: " << account.balance;
    return os;
}



/////////////////////////////////////////////////////////////////////////
// Other methods


