#pragma once

#include "Equipment.h"
#include "BookingManager.h"
#include "MaintenanceManager.h"
#include "FileManager.h"

#include <vector>
#include <string>
using namespace std;

class LabManager {
private:
    vector<Equipment> equipmentList;

    BookingManager bookingManager;
    MaintenanceManager maintenanceManager;

    Equipment* findEquipment(int equipmentId);

public:
    bool addEquipment(const Equipment& equipment);
    void saveData() const;
    void loadData();
    bool cancelBooking(int studentId, int bookingId);

    void displayStudentBookings(int studentId) const;
    void displayAllEquipment() const;

    bool createBooking(int studentId, int equipmentId, int date, int startTime, int endTime);

    bool reportDamage(int equipmentId, int userId, const string& description);

    bool startRepair(int recordId, int equipmentId);

    bool resolveRepair(int recordId, int equipmentId);

    void displayAllBookings() const;
    void displayAllMaintenanceRecords() const;
};
