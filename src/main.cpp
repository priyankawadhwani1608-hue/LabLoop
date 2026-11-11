#include <iostream>
#include "LabManager.h"
#include "Menu.h"

using namespace std;

int main() {
    LabManager lab;

    cout << "Loading LabLoop data...\n";
    lab.loadData();

    runMenu(lab);

    return 0;
}
