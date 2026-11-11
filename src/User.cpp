#include "../include/User.h"

User::User(int id, string n, string e) {
    userId = id;
    name = n;
    email = e;
}

int User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}


// Student implementation

Student::Student(int id, string n, string e)
    : User(id, n, e) {}

string Student::getRole() const {
    return "Student";
}

void Student::displayDashboard() const {
    cout << "\n--- Student Dashboard ---\n";
    cout << "1. View Equipment\n";
    cout << "2. Book Equipment\n";
    cout << "3. View My Bookings\n";
    cout << "4. Report Damage\n";
}

void Student::requestBooking() {
    cout << "Booking request initiated.\n";
}

void Student::reportDamage() {
    cout << "Damage reporting initiated.\n";
}


// LabAssistant implementation

LabAssistant::LabAssistant(int id, string n, string e)
    : User(id, name, email) {}

string LabAssistant::getRole() const {
    return "Lab Assistant";
}

void LabAssistant::displayDashboard() const {
    cout << "\n--- Lab Assistant Dashboard ---\n";
    cout << "1. Manage Returns\n";
    cout << "2. View Maintenance Reports\n";
    cout << "3. Update Equipment Condition\n";
}

void LabAssistant::manageReturns() {
    cout << "Return management initiated.\n";
}

void LabAssistant::manageMaintenance() {
    cout << "Maintenance management initiated.\n";
}


// Admin implementation

Admin::Admin(int id, string n, string e)
    : User(id, n, e) {}

string Admin::getRole() const {
    return "Admin";
}

void Admin::displayDashboard() const {
    cout << "\n--- Admin Dashboard ---\n";
    cout << "1. Add Equipment\n";
    cout << "2. Remove Equipment\n";
    cout << "3. Manage Users\n";
}

void Admin::addEquipment() {
    cout << "Equipment addition initiated.\n";
}

void Admin::removeEquipment() {
    cout << "Equipment removal initiated.\n";
}

void Admin::manageUsers() {
    cout << "User management initiated.\n";
}
