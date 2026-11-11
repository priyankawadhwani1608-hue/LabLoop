#include "FileManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

// ================= HELPER FUNCTIONS =================

// Split a line using the pipe delimiter.
vector<string> splitLine(const string& line) {
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, '|')) {
        fields.push_back(field);
    }

    // Preserve an empty final field.
    if (!line.empty() && line.back() == '|') {
        fields.push_back("");
    }

    return fields;
}

// Strict integer parsing: rejects empty strings and trailing characters.
bool parseInt(const string& value, int& result) {
    if (value.empty()) {
        return false;
    }

    try {
        size_t pos = 0;
        long long number = stoll(value, &pos);

        if (pos != value.size() ||
            number < numeric_limits<int>::min() ||
            number > numeric_limits<int>::max()) {
            return false;
        }

        result = static_cast<int>(number);
        return true;
    }
    catch (...) {
        return false;
    }
}

// Validate a calendar date without rejecting historical bookings.
bool isValidCalendarDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 1 || year > 9999 ||
        month < 1 || month > 12) {
        return false;
    }

    int days[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leap = (year % 400 == 0) ||
                (year % 4 == 0 && year % 100 != 0);

    if (leap) {
        days[1] = 29;
    }

    return day >= 1 && day <= days[month - 1];
}

// Safely update the next available ID.
void updateNextId(int id, int& nextId) {
    if (id >= nextId && id < numeric_limits<int>::max()) {
        nextId = id + 1;
    }
}

// Read a NEXT|value line safely.
void readNextId(const string& line, int& nextId) {
    vector<string> fields = splitLine(line);

    int value;

    if (fields.size() == 2 &&
        fields[0] == "NEXT" &&
        parseInt(fields[1], value) &&
        value > 0) {
        nextId = max(nextId, value);
    }
}

// ================= EQUIPMENT =================

void FileManager::saveEquipment(
    const vector<Equipment>& equipmentList) {

    ofstream file("equipment.txt");

    if (!file) {
        cout << "Error opening equipment file!\n";
        return;
    }

    for (const auto& equipment : equipmentList) {

        file << equipment.getEquipmentId() << "|"
             << equipment.getName() << "|"
             << equipment.getCategory() << "|"
             << equipment.getLocation() << "|"
             << static_cast<int>(equipment.getStatus())
             << "\n";
    }

    if (!file) {
        cout << "Error while writing equipment data!\n";
        return;
    }

    cout << "Equipment saved successfully!\n";
}

void FileManager::loadEquipment(
    vector<Equipment>& equipmentList) {

    ifstream file("equipment.txt");

    if (!file) {
        cout << "No existing equipment file found.\n";
        return;
    }

    vector<Equipment> loadedEquipment;
    unordered_set<int> usedIds;

    string line;

    while (getline(file, line)) {

        vector<string> fields = splitLine(line);

        if (fields.size() != 5) {
            cout << "Skipping malformed equipment record.\n";
            continue;
        }

        int id, status;

        if (!parseInt(fields[0], id) ||
            !parseInt(fields[4], status)) {
            cout << "Skipping invalid equipment record.\n";
            continue;
        }

        string name = fields[1];
        string category = fields[2];
        string location = fields[3];

        if (id <= 0 ||
            name.find_first_not_of(" \t\r\n") == string::npos ||
            category.find_first_not_of(" \t\r\n") == string::npos ||
            location.find_first_not_of(" \t\r\n") == string::npos ||
            status < 0 || status > 2 ||
            usedIds.count(id)) {

            cout << "Skipping invalid or duplicate equipment record.\n";
            continue;
        }

        try {
            Equipment equipment(id, name, category, location);

            equipment.updateStatus(
                static_cast<EquipmentStatus>(status)
            );

            loadedEquipment.push_back(equipment);
            usedIds.insert(id);
        }
        catch (...) {
            cout << "Skipping equipment record due to an error.\n";
        }
    }

    if (file.bad()) {
        cout << "Error while reading equipment file!\n";
        return;
    }

    equipmentList = loadedEquipment;

    cout << "Equipment loaded successfully!\n";
}

// ================= BOOKINGS =================

void FileManager::saveBookings(const BookingManager& manager) {

    ofstream file("bookings.txt");

    if (!file) {
        cout << "Could not save bookings!\n";
        return;
    }

    const auto& bookings = manager.getBookings();

    int nextId = 1001;

    for (const auto& b : bookings) {

        file << b.getBookingId() << "|"
             << b.getStudentId() << "|"
             << b.getEquipmentId() << "|"
             << b.getDate() << "|"
             << b.getStartTime() << "|"
             << b.getEndTime() << "|"
             << static_cast<int>(b.getStatus()) << "\n";

        updateNextId(b.getBookingId(), nextId);
    }

    file << "NEXT|" << nextId << "\n";

    if (!file) {
        cout << "Error while writing booking data!\n";
        return;
    }

    cout << "Bookings saved successfully!\n";
}

void FileManager::loadBookings(BookingManager& manager) {

    ifstream file("bookings.txt");

    if (!file) {
        cout << "No booking file found.\n";
        return;
    }

    vector<Booking> saved;
    unordered_set<int> usedIds;

    string line;
    int nextId = 1001;

    while (getline(file, line)) {

        if (line.rfind("NEXT|", 0) == 0) {
            readNextId(line, nextId);
            continue;
        }

        vector<string> fields = splitLine(line);

        if (fields.size() != 7) {
            cout << "Skipping malformed booking record.\n";
            continue;
        }

        int id, student, equipment;
        int date, startTime, endTime, status;

        if (!parseInt(fields[0], id) ||
            !parseInt(fields[1], student) ||
            !parseInt(fields[2], equipment) ||
            !parseInt(fields[3], date) ||
            !parseInt(fields[4], startTime) ||
            !parseInt(fields[5], endTime) ||
            !parseInt(fields[6], status)) {

            cout << "Skipping booking with invalid numeric data.\n";
            continue;
        }

        if (id <= 0 || id == numeric_limits<int>::max() ||
            student <= 0 || equipment <= 0 ||
            !isValidCalendarDate(date) ||
            startTime < 0 || endTime > 1440 ||
            startTime >= endTime ||
            status < 0 || status > 2 ||
            usedIds.count(id)) {

            cout << "Skipping invalid or duplicate booking record.\n";
            continue;
        }

        try {
            Booking booking(
                id, student, equipment,
                date, startTime, endTime
            );

            booking.setStatus(
                static_cast<BookingStatus>(status)
            );

            saved.push_back(booking);
            usedIds.insert(id);

            updateNextId(id, nextId);
        }
        catch (...) {
            cout << "Skipping booking record due to an error.\n";
        }
    }

    if (file.bad()) {
        cout << "Error while reading booking file!\n";
        return;
    }

    manager.loadBookings(saved, nextId);

    cout << "Bookings loaded successfully!\n";
}

// ================= MAINTENANCE =================

void FileManager::saveMaintenance(
    const MaintenanceManager& manager) {

    ofstream file("maintenance.txt");

    if (!file) {
        cout << "Could not save maintenance records!\n";
        return;
    }

    const auto& records = manager.getRecords();

    int nextId = 5001;

    for (const auto& r : records) {

        file << r.getRecordId() << "|"
             << r.getEquipmentId() << "|"
             << r.getReportedBy() << "|"
             << r.getIssueDescription() << "|"
             << static_cast<int>(r.getStatus()) << "\n";

        updateNextId(r.getRecordId(), nextId);
    }

    file << "NEXT|" << nextId << "\n";

    if (!file) {
        cout << "Error while writing maintenance data!\n";
        return;
    }

    cout << "Maintenance records saved successfully!\n";
}

void FileManager::loadMaintenance(
    MaintenanceManager& manager) {

    ifstream file("maintenance.txt");

    if (!file) {
        cout << "No maintenance file found.\n";
        return;
    }

    vector<MaintenanceRecord> saved;
    unordered_set<int> usedIds;

    string line;
    int nextId = 5001;

    while (getline(file, line)) {

        if (line.rfind("NEXT|", 0) == 0) {
            readNextId(line, nextId);
            continue;
        }

        vector<string> fields = splitLine(line);

        if (fields.size() != 5) {
            cout << "Skipping malformed maintenance record.\n";
            continue;
        }

        int id, equipment, user, status;

        if (!parseInt(fields[0], id) ||
            !parseInt(fields[1], equipment) ||
            !parseInt(fields[2], user) ||
            !parseInt(fields[4], status)) {

            cout << "Skipping maintenance record with invalid data.\n";
            continue;
        }

        string description = fields[3];

        if (id <= 0 || id == numeric_limits<int>::max() ||
            equipment <= 0 || user <= 0 ||
            description.find_first_not_of(" \t\r\n") == string::npos ||
            status < 0 || status > 2 ||
            usedIds.count(id)) {

            cout << "Skipping invalid or duplicate maintenance record.\n";
            continue;
        }

        try {
            MaintenanceRecord record(
                id, equipment, user, description
            );

            record.setStatus(
                static_cast<MaintenanceStatus>(status)
            );

            saved.push_back(record);
            usedIds.insert(id);

            updateNextId(id, nextId);
        }
        catch (...) {
            cout << "Skipping maintenance record due to an error.\n";
        }
    }

    if (file.bad()) {
        cout << "Error while reading maintenance file!\n";
        return;
    }

    manager.loadRecords(saved, nextId);

    cout << "Maintenance records loaded successfully!\n";
}
