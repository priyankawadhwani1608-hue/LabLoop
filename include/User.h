#pragma once

#include <iostream>
#include <string>
using namespace std;

class User {
private:
    int userId;
    string name;
    string email;

public:
    User(int id, string n, string e);

    virtual ~User() = default;

    int getUserId() const;
    string getName() const;
    string getEmail() const;

    virtual string getRole() const = 0;
    virtual void displayDashboard() const = 0;
};


class Student : public User {
public:
    Student(int id, string n, string e);

    string getRole() const override;
    void displayDashboard() const override;

    void requestBooking();
    void reportDamage();
};


class LabAssistant : public User {
public:
    LabAssistant(int id, string n, string e);

    string getRole() const override;
    void displayDashboard() const override;

    void manageReturns();
    void manageMaintenance();
};


class Admin : public User {
public:
    Admin(int id, string n, string e);

    string getRole() const override;
    void displayDashboard() const override;

    void addEquipment();
    void removeEquipment();
    void manageUsers();
};
