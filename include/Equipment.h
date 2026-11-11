#pragma once

#include <string>
using namespace std;

enum class EquipmentStatus {
    AVAILABLE,
    UNDER_MAINTENANCE,
    RETIRED
};

class Equipment {
private:
    int equipmentId;
    string name;
    string category;
    string location;
    EquipmentStatus status;

public:
    Equipment(int id, string n, string c, string loc);
    string getLocation() const;
    int getEquipmentId() const;
    string getName() const;
    string getCategory() const;
    EquipmentStatus getStatus() const;

    void updateStatus(EquipmentStatus newStatus);
    void markDamaged();
    void markRepaired();
    void displayDetails() const;
};
