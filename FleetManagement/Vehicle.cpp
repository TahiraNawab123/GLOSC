#include <iostream>
using namespace std;
#include <string>
#include "Vehicle.h"
//default constructor
Vehicle::Vehicle(){
    vehicleId=0;
    vehiclecapacity=0;
    fuel=0;
    speed=0;
    fuelConsumptionrate=0;
    isVehicleavaible=true;//available by default
    vehicleType = "None";
}
//parameterized constructor

Vehicle::Vehicle(int id,int capacity,int fuel,int speed,int consumptionRate,bool isAvailable,string type){
    this->vehicleId=id;
    this->vehiclecapacity=capacity;
    this->vehicleType=type;
    this->fuel=fuel;
    this->speed=speed;
    this->fuelConsumptionrate=consumptionRate;
    this-> isVehicleavaible=isAvailable;
}

//display function
void Vehicle::displayVehiclesInfo(){
    // cout<<"\n=======Vehicle Details=======\n";
    cout<<"vehicle ID: "<<vehicleId<<"\n";
    cout<<"vehicle Capcity: "<<vehiclecapacity<<"\n";
    cout<<"vehicle type: "<<vehicleType<<"\n";
    cout<<"fuel: "<<fuel<<"\n";
    cout<<"Speed: "<<speed<<"\n";
    cout<<"fuel/km: "<<fuelConsumptionrate<<"\n";
    cout<<"isAvaiable "<<(isVehicleavaible?"Yes": "No")<<"\n";
}

//destructor
Vehicle:: ~Vehicle(){
//there is no dynamic member so nothing to delete here
}

Truck::Truck(): Vehicle(){//default constructor
vehicleType="Truck";
    }

    //parameterized constructor
Truck::Truck(int id,int capacity,int fuel,int speed,int consumptionRate)
    : Vehicle(id, capacity, fuel, speed, consumptionRate, true, "Truck"){
}
void Truck::displayVehiclesInfo(){//display function
cout<<"=========Truck Details=========\n";
Vehicle::displayVehiclesInfo();
}


Van::Van(): Vehicle(){//dafult constructor
    vehicleType="Van";
}
Van::Van(int id,int capacity,int fuel,int speed,int consumptionRate)
    : Vehicle(id, capacity, fuel, speed, consumptionRate, true, "Van"){}
void Van::displayVehiclesInfo(){//display function
cout<<"=======Van Details=======\n";
Vehicle::displayVehiclesInfo();
}


Bike::Bike(): Vehicle(){//default
    vehicleType="Bike";
}
Bike::Bike(int id,int capacity,int fuel,int speed,int consumptionRate)
    : Vehicle(id, capacity, fuel, speed, consumptionRate, true, "Bike"){}
void Bike::displayVehiclesInfo() {//display
cout<<"=======Bike Details=======\n";
Vehicle::displayVehiclesInfo();
}