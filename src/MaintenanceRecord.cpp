#include "../include/MaintenanceRecord.h"
#include <iostream>

MaintenanceRecord::MaintenanceRecord(
    int rid, int eid, int uid, string description) {

    recordId = rid;
    equipmentId = eid;
    reportedBy = uid;
    issueDescription = description;
    status = MaintenanceStatus::REPORTED;
}

int MaintenanceRecord::getRecordId() const {
    return recordId;
}

int MaintenanceRecord::getEquipmentId() const {
    return equipmentId;
}

MaintenanceStatus MaintenanceRecord::getStatus() const {
    return status;
}

void MaintenanceRecord::startRepair() {
    if (status == MaintenanceStatus::REPORTED) {
        status = MaintenanceStatus::IN_PROGRESS;
    }
}

int MaintenanceRecord::getReportedBy() const {
    return reportedBy;
}

string MaintenanceRecord::getIssueDescription() const {
    return issueDescription;
}

void MaintenanceRecord::setStatus(MaintenanceStatus newStatus) {
    status = newStatus;
}

void MaintenanceRecord::resolveIssue() {
    if (status == MaintenanceStatus::IN_PROGRESS) {
        status = MaintenanceStatus::RESOLVED;
    }
}

void MaintenanceRecord::displayRecord() const {

    cout << "\nMaintenance ID: " << recordId;
    cout << "\nEquipment ID: " << equipmentId;
    cout << "\nReported By: " << reportedBy;
    cout << "\nIssue: " << issueDescription;

    cout << "\nStatus: ";

    switch (status) {
        case MaintenanceStatus::REPORTED:
            cout << "Reported";
            break;

        case MaintenanceStatus::IN_PROGRESS:
            cout << "In Progress";
            break;

        case MaintenanceStatus::RESOLVED:
            cout << "Resolved";
            break;
    }

    cout << "\n";
}
