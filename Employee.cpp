//
// Created by Mostafa Mahmoud on 5/7/2017.
//

#include "Employee.h"

Employee::Employee() : username(""), password("") {}

Employee::Employee(const string &username, const string &password) : username(username), password(password) {}

Employee::~Employee() {

}

const string &Employee::getUsername() const {
    return username;
}

void Employee::setUsername(const string &username) {
    this->username = username;
}

const string &Employee::getPassword() const {
    return password;
}

void Employee::setPassword(const string &password) {
    this->password = password;
}

ostream &operator<<(ostream &os, const Employee &employee) {
    os << "Username: " << employee.username << "\nPassword: " << employee.password;
    return os;
}
