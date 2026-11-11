#include "LabManager.h"
#include <iostream>
using namespace std;

// Find equipment using its ID
Equipment* LabManager::findEquipment(int equipmentId) {
    for (auto& equipment : equipmentList) {
        if (equipment.getEquipmentId() == equipmentId) {
            return &equipment;
        }
    }

    return nullptr;
}

// Add equipment to inventory
bool LabManager::addEquipment(const Equipment& equipment) {

    // Validate equipment ID
    if (equipment.getEquipmentId() <= 0) {
        cout << "Invalid Equipment ID! ID must be positive.\n";
        return false;
    }

    // Validate name, category and location
    if (equipment.getName().find_first_not_of(" \t\n\r") == string::npos) {
        cout << "Equipment name cannot be empty!\n";
        return false;
    }

    if (equipment.getCategory().find_first_not_of(" \t\n\r") == string::npos) {
        cout << "Equipment category cannot be empty!\n";
        return false;
    }

    if (equipment.getLocation().find_first_not_of(" \t\n\r") == string::npos) {
        cout << "Equipment location cannot be empty!\n";
        return false;
    }

    // Check duplicate equipment ID
    for (const auto& item : equipmentList) {
        if (item.getEquipmentId() == equipment.getEquipmentId()) {
            cout << "Equipment ID already exists!\n";
            return false;
        }
    }

    equipmentList.push_back(equipment);
    cout << "Equipment added successfully!\n";
    return true;
}

// Display inventory
void LabManager::displayAllEquipment() const {
    cout << "\n===== LAB INVENTORY =====\n";

    for (const auto& equipment : equipmentList) {
        equipment.displayDetails();
        cout << "------------------------\n";
    }
}

// Create booking
bool LabManager::createBooking(int studentId, int equipmentId, int date, int startTime, int endTime) {
    Equipment* equipment = findEquipment(equipmentId);

    if (equipment == nullptr) {
        cout << "Equipment not found!\n";
        return false;
    }

    return bookingManager.createBooking(
        studentId, *equipment, date, startTime, endTime
    );
}

// Report damage
bool LabManager::reportDamage(int equipmentId, int userId, const string& description) {
    Equipment* equipment = findEquipment(equipmentId);

    if (equipment == nullptr) {
        cout << "Equipment not found!\n";
        return false;
    }

    return maintenanceManager.reportDamage(
        *equipment, userId, description
    );
}

// Start repair
bool LabManager::startRepair(int recordId, int equipmentId) {
    Equipment* equipment = findEquipment(equipmentId);

    if (equipment == nullptr) {
        cout << "Equipment not found!\n";
        return false;
    }

    return maintenanceManager.startRepair(recordId, *equipment);
}

// Resolve repair
bool LabManager::resolveRepair(int recordId, int equipmentId) {
    Equipment* equipment = findEquipment(equipmentId);

    if (equipment == nullptr) {
        cout << "Equipment not found!\n";
        return false;
    }

    return maintenanceManager.resolveRepair(recordId, *equipment);
}

// Display bookings
void LabManager::displayAllBookings() const {
    bookingManager.displayAllBookings();
}

// Display maintenance records
void LabManager::displayAllMaintenanceRecords() const {
    maintenanceManager.displayAllRecords();
}

void LabManager::saveData() const {
    FileManager::saveEquipment(equipmentList);
    FileManager::saveBookings(bookingManager);
    FileManager::saveMaintenance(maintenanceManager);
}

void LabManager::loadData() {
    FileManager::loadEquipment(equipmentList);
    FileManager::loadBookings(bookingManager);
    FileManager::loadMaintenance(maintenanceManager);
}

bool LabManager::cancelBooking(int studentId, int bookingId) {
    return bookingManager.cancelBooking(bookingId, studentId);
}

void LabManager::displayStudentBookings(int studentId) const {
    bookingManager.displayStudentBookings(studentId);
}
