#pragma once

#include <string>
using namespace std;

enum class MaintenanceStatus {
    REPORTED,
    IN_PROGRESS,
    RESOLVED
};

class MaintenanceRecord {
private:
    int recordId;
    int equipmentId;
    int reportedBy;
    string issueDescription;
    MaintenanceStatus status;

public:
    MaintenanceRecord(int rid, int eid, int uid,
                      string description);

    int getRecordId() const;
    int getEquipmentId() const;
    MaintenanceStatus getStatus() const;

    void startRepair();
    void resolveIssue();
    int getReportedBy() const;
    string getIssueDescription() const;
    void setStatus(MaintenanceStatus newStatus);
    void displayRecord() const;
};
