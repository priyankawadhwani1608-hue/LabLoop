#pragma once

#include "MaintenanceRecord.h"
#include "Equipment.h"
#include <vector>

class MaintenanceManager {
private:
    vector<MaintenanceRecord> records;
    int nextRecordId;

public:
    MaintenanceManager();

    bool reportDamage(Equipment& equipment, int reportedBy, const string& description);

    bool startRepair(int recordId, Equipment& equipment);

    bool resolveRepair(int recordId, Equipment& equipment);

    void displayAllRecords() const;

    const vector<MaintenanceRecord>& getRecords() const;

    void loadRecords(const vector<MaintenanceRecord>& savedRecords, int nextId);
};
