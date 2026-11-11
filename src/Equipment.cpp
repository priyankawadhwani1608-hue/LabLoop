#include "../include/Equipment.h"
#include <iostream>

Equipment::Equipment(int id, string n, string c, string loc) {
    equipmentId = id;
    name = n;
    category = c;
    location = loc;
    status = EquipmentStatus::AVAILABLE;
}

int Equipment::getEquipmentId() const {
    return equipmentId;
}

string Equipment::getName() const {
    return name;
}

string Equipment::getCategory() const {
    return category;
}

string Equipment::getLocation() const {
    return location;
}

EquipmentStatus Equipment::getStatus() const {
    return status;
}

void Equipment::updateStatus(EquipmentStatus newStatus) {
    status = newStatus;
}

void Equipment::markDamaged() {
    status = EquipmentStatus::UNDER_MAINTENANCE;
}

void Equipment::markRepaired() {
    if (status == EquipmentStatus::UNDER_MAINTENANCE) {
        status = EquipmentStatus::AVAILABLE;
    }
}

void Equipment::displayDetails() const {
    cout << "\nEquipment ID: " << equipmentId;
    cout << "\nName: " << name;
    cout << "\nCategory: " << category;
    cout << "\nLocation: " << location;

    cout << "\nStatus: ";

    switch (status) {
        case EquipmentStatus::AVAILABLE:
            cout << "Available";
            break;

        case EquipmentStatus::UNDER_MAINTENANCE:
            cout << "Under Maintenance";
            break;

        case EquipmentStatus::RETIRED:
            cout << "Retired";
            break;
    }

    cout << "\n";
}
