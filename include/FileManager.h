#pragma once

#include "Equipment.h"
#include <vector>
#include <string>
#include "BookingManager.h"
#include "MaintenanceManager.h"

using namespace std;

class FileManager {
public:
    static void saveEquipment(const vector<Equipment>& equipmentList);
    static void loadEquipment(vector<Equipment>& equipmentList);

    static void saveBookings(const BookingManager& manager);
    static void loadBookings(BookingManager& manager);

    static void saveMaintenance(const MaintenanceManager& manager);
    static void loadMaintenance(MaintenanceManager& manager);
};
