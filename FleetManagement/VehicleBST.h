#ifndef VEHICLEBST_H
#define VEHICLEBST_H

#include <iostream>
using namespace std;
#include <string>
#include "Vehicle.h"
#include "../Common/AllStructures.h"




class VehicleBST{
private:
BinarySearchTree<Vehicle>bst;
public:

    VehicleBST();//constructor
   
    void insertVehicle(Vehicle *v);//insert a vehicle into BST

    Vehicle *searchVehicle(int Id);//search a vehicle in BST

   
    void display();//display all vehicle stored in bst

    void deleteVehicle(int id);//delete a vehicle from BST

    
};

#endif

