#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
using namespace std;
#include <string>
//---------driver class--------------
class Driver
{
public:
    int driverId;
    string driverName;
    bool isAvailable; // driver free or booked
    int assignedVehicleId;
    Driver();

    Driver(int id, string name);
    // assign vehicle
    void assignVehicle(int vehicleId);
    void FreeDriver();

    void displayDriverInfo();
    void freeDriverByVehicleId(int vid);
};
Driver *findDriverById(Driver drivers[], int driverCount, int id); 



#endif