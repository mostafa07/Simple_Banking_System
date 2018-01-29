//
// Created by Mostafa Mahmoud on 5/7/2017.
//

#ifndef DS_PROJECT_BANKING_SYSTEM_EMPLOYEE_H
#define DS_PROJECT_BANKING_SYSTEM_EMPLOYEE_H

#include <iostream>
using namespace std;

class Employee {
private:
    string username;
    string password;

public:
    // Constructors and destructor

    Employee();

    Employee(const string &username, const string &password);

    ~Employee();

    // Getters and setters

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getPassword() const;

    void setPassword(const string &password);

    // << operator for printing using cout
    friend ostream &operator<<(ostream &os, const Employee &employee);
};


#endif //DS_PROJECT_BANKING_SYSTEM_EMPLOYEE_H
