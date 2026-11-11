#include "Menu.h"
#include "User.h"

#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Safely read an integer without allowing cin to get stuck.
bool readInt(const string& prompt, int& value) {
    while (true) {
        cout << prompt;

        if (cin >> value) {
            return true;
        }

        if (cin.eof()) {
            return false;
        }

        cout << "Invalid input! Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a non-empty string.
bool readRequiredLine(const string& prompt, string& value) {
    while (true) {
        cout << prompt;

        if (!getline(cin, value)) {
            return false;
        }

        if (value.find_first_not_of(" \t\r\n") != string::npos) {
            return true;
        }

        cout << "This field cannot be empty!\n";
    }
}

// Clear the remaining input line after reading an integer.
void clearInputLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Convert HHMM format into minutes from midnight.
// Example: 930 becomes 570 minutes.
bool readTime(const string& prompt, int& result) {
    int time;

    if (!readInt(prompt, time)) {
        return false;
    }

    int hours = time / 100;
    int minutes = time % 100;

    if (time < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        cout << "Invalid time! Enter time in HHMM format.\n";
        result = -1;
        return true;
    }

    result = hours * 60 + minutes;
    return true;
}

// ================= STUDENT MENU =================

void studentMenu(LabManager& lab, int studentId) {
    int choice;

    do {
        cout << "\n===== STUDENT DASHBOARD =====\n";
        cout << "1. View Equipment\n";
        cout << "2. Book Equipment\n";
        cout << "3. View My Bookings\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Report Equipment Damage\n";
        cout << "0. Logout\n";

        if (!readInt("Enter choice: ", choice)) {
            return;
        }

        if (choice == 1) {
            lab.displayAllEquipment();
        }
        else if (choice == 2) {
            int equipmentId, date, start, end;

            if (!readInt("Enter Equipment ID: ", equipmentId) ||
                !readInt("Enter date (YYYYMMDD): ", date) ||
                !readTime("Enter start time (HHMM): ", start) ||
                !readTime("Enter end time (HHMM): ", end)) {
                return;
            }

            if (start == -1 || end == -1) {
                cout << "Booking cancelled due to invalid time.\n";
            }
            else {
                lab.createBooking(studentId, equipmentId,
                                  date, start, end);
            }
        }
        else if (choice == 3) {
            lab.displayStudentBookings(studentId);
        }
        else if (choice == 4) {
            int bookingId;

            if (!readInt("Enter Booking ID to cancel: ", bookingId)) {
                return;
            }

            if (!lab.cancelBooking(studentId, bookingId)) {
                cout << "Booking cancellation failed!\n";
            }
            else {
                cout << "Booking cancelled successfully!\n";
            }
        }
        else if (choice == 5) {
            int equipmentId;
            string description;

            if (!readInt("Enter Equipment ID: ", equipmentId)) {
                return;
            }

            clearInputLine();

            if (!readRequiredLine("Describe the damage: ", description)) {
                return;
            }

            lab.reportDamage(equipmentId, studentId, description);
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

// ================= LAB ASSISTANT MENU =================

void assistantMenu(LabManager& lab) {
    int choice;

    do {
        cout << "\n===== LAB ASSISTANT DASHBOARD =====\n";
        cout << "1. View Equipment\n";
        cout << "2. View All Bookings\n";
        cout << "3. View Maintenance Records\n";
        cout << "4. Start Repair\n";
        cout << "5. Resolve Repair\n";
        cout << "0. Logout\n";

        if (!readInt("Enter choice: ", choice)) {
            return;
        }

        if (choice == 1) {
            lab.displayAllEquipment();
        }
        else if (choice == 2) {
            lab.displayAllBookings();
        }
        else if (choice == 3) {
            lab.displayAllMaintenanceRecords();
        }
        else if (choice == 4 || choice == 5) {
            int recordId, equipmentId;

            if (!readInt("Enter Maintenance Record ID: ", recordId) ||
                !readInt("Enter Equipment ID: ", equipmentId)) {
                return;
            }

            if (choice == 4) {
                lab.startRepair(recordId, equipmentId);
            }
            else {
                lab.resolveRepair(recordId, equipmentId);
            }
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

// ================= ADMIN MENU =================

void adminMenu(LabManager& lab) {
    int choice;

    do {
        cout << "\n===== ADMIN DASHBOARD =====\n";
        cout << "1. Add Equipment\n";
        cout << "2. View All Equipment\n";
        cout << "3. View All Bookings\n";
        cout << "4. View Maintenance Records\n";
        cout << "0. Logout\n";

        if (!readInt("Enter choice: ", choice)) {
            return;
        }

        if (choice == 1) {
            int id;
            string name, category, location;

            if (!readInt("Enter Equipment ID: ", id)) {
                return;
            }

            clearInputLine();

            if (!readRequiredLine("Enter Equipment Name: ", name) ||
                !readRequiredLine("Enter Category: ", category) ||
                !readRequiredLine("Enter Location: ", location)) {
                return;
            }

            Equipment equipment(id, name, category, location);

            if (lab.addEquipment(equipment)) {
                cout << "Equipment added successfully!\n";
            }
            else {
                cout << "Could not add equipment. Check the ID and details.\n";
            }
        }
        else if (choice == 2) {
            lab.displayAllEquipment();
        }
        else if (choice == 3) {
            lab.displayAllBookings();
        }
        else if (choice == 4) {
            lab.displayAllMaintenanceRecords();
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

// ================= MAIN MENU =================

void runMenu(LabManager& lab) {
    int role;

    do {
        cout << "\n========== LABLOOP ==========\n";
        cout << "1. Student Login\n";
        cout << "2. Lab Assistant Login\n";
        cout << "3. Admin Login\n";
        cout << "0. Exit Application\n";

        if (!readInt("Select role: ", role)) {
            break;
        }

        if (role == 1 || role == 2 || role == 3) {
            int id;
            string name, email;

            string idPrompt;

            if (role == 1) {
                idPrompt = "Student ID: ";
            }
            else if (role == 2) {
                idPrompt = "Assistant ID: ";
            }
            else {
                idPrompt = "Admin ID: ";
            }

            if (!readInt(idPrompt, id)) {
                break;
            }

            if (id <= 0) {
                cout << "ID must be a positive number!\n";
                continue;
            }

            clearInputLine();

            if (!readRequiredLine("Name: ", name) ||
                !readRequiredLine("Email: ", email)) {
                break;
            }

            if (role == 1) {
                Student student(id, name, email);
                student.displayDashboard();

                studentMenu(lab, student.getUserId());
            }
            else if (role == 2) {
                LabAssistant assistant(id, name, email);
                assistant.displayDashboard();

                assistantMenu(lab);
            }
            else {
                Admin admin(id, name, email);
                admin.displayDashboard();

                adminMenu(lab);
            }
        }
        else if (role != 0) {
            cout << "Invalid role!\n";
        }

    } while (role != 0 && !cin.eof());

    lab.saveData();

    cout << "\nThank you for using LabLoop!\n";
}
