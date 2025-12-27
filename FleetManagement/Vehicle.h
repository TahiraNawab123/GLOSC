#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
using namespace std;
#include <string>


class Vehicle{
public:
    int vehicleId;
    string vehicleType;
    int vehiclecapacity;
    int fuel;
    int speed;
    int fuelConsumptionrate;//fuel per km
    bool isVehicleavaible;

    // default constructor
    Vehicle();
    // parameterized constructor
   Vehicle(int id,int capacity,int fuel,int speed,int consumptionRate,bool isAvailable,string type);
    // display function
    virtual void displayVehiclesInfo();
     //less than operator used by BST to place node on left side
    bool operator<(const Vehicle& other) const {
    return vehicleId < other.vehicleId;
}
    //greater than operator
    bool operator>(const Vehicle& other) const {
    return vehicleId > other.vehicleId;
}
   //equailty operator
    bool operator==(const Vehicle& other) const {
    return vehicleId == other.vehicleId;
}
    // destructor
    virtual ~Vehicle();

};
// truck class
class Truck : public Vehicle
{ // derived class
public:
    Truck();

    // parameterized constructor
     Truck(int id,int capacity,int fuel,int speed,int consumptionRate);

    void displayVehiclesInfo() override;
};

class Van : public Vehicle
{ // van class
public:
    Van();
    Van(int id,int capacity,int fuel,int speed,int consumptionRate);

    void displayVehiclesInfo() override;
};
// bike class (derived)
class Bike : public Vehicle
{
public:
    Bike();
    Bike(int id,int capacity,int fuel,int speed,int consumptionRate);


    void displayVehiclesInfo() override;



};
#endif