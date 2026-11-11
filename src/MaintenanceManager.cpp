#include "../include/MaintenanceManager.h"
#include <iostream>

MaintenanceManager::MaintenanceManager() {
    nextRecordId = 5001;
}

bool MaintenanceManager::reportDamage(Equipment& equipment, int reportedBy, const string& description) {

    if (reportedBy <= 0 || description.empty()) {
        cout << "\nInvalid damage report.\n";
        return false;
    }

    if (equipment.getStatus() != EquipmentStatus::AVAILABLE) {
        cout << "\nEquipment is not currently available.\n";
        return false;
    }

    MaintenanceRecord record(
        nextRecordId,
        equipment.getEquipmentId(),
        reportedBy,
        description
    );

    records.push_back(record);

    equipment.markDamaged();

    cout << "\nDamage reported successfully.";
    cout << "\nMaintenance ID: " << nextRecordId << "\n";

    nextRecordId++;

    return true;
}

bool MaintenanceManager::startRepair(
    int recordId, Equipment& equipment) {

    for (MaintenanceRecord& record : records) {

        if (record.getRecordId() == recordId &&
            record.getEquipmentId() == equipment.getEquipmentId() &&
            record.getStatus() == MaintenanceStatus::REPORTED) {

            record.startRepair();

            cout << "\nRepair started.\n";
            return true;
        }
    }

    cout << "\nMaintenance record not found.\n";
    return false;
}

bool MaintenanceManager::resolveRepair(
    int recordId, Equipment& equipment) {

    for (MaintenanceRecord& record : records) {

        if (record.getRecordId() == recordId &&
            record.getEquipmentId() == equipment.getEquipmentId() &&
            record.getStatus() == MaintenanceStatus::IN_PROGRESS) {

            record.resolveIssue();

            equipment.markRepaired();

            cout << "\nEquipment repaired successfully!\n";
            return true;
        }
    }

    cout << "\nRepair cannot be resolved.\n";
    return false;
}

const vector<MaintenanceRecord>&
MaintenanceManager::getRecords() const {
    return records;
}

void MaintenanceManager::loadRecords(
    const vector<MaintenanceRecord>& savedRecords, int nextId) {

    records = savedRecords;
    nextRecordId = nextId;
}

void MaintenanceManager::displayAllRecords() const {

    if (records.empty()) {
        cout << "\nNo maintenance records found.\n";
        return;
    }

    for (const MaintenanceRecord& record : records) {
        record.displayRecord();
        cout << "-------------------------\n";
    }
}
