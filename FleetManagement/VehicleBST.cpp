#include <iostream>
using namespace std;
#include <string>
#include "Vehicle.h"
#include "VehicleBST.h"


VehicleBST::VehicleBST(){//constructor
  //constructor
}

  void VehicleBST::insertVehicle(Vehicle*v){
    if (v == nullptr)// check if the vehicle pointer is NULL
        return;

    bst.insert(*v);  //insert vehicle into BST also dereference pointer pointer beacuse BST Stores Vehicle object
  }

//   //search will search vehicle on the basis of their id
//   Vehicle* VehicleBST::searchRecord(VehicleNode* node, int id){
//   if(node==nullptr)
//     return nullptr;//if not founded then return null

//   if(id==node->vehicle->vehicleId)
//     return node->vehicle;//if id match the return 
  
//   if(id<node->vehicle->vehicleId)
//     return searchRecord(node->left,id);//search on left side
//     else{
//     return searchRecord(node->right,id);//search on right side
//    } 
//  }

 Vehicle*VehicleBST::searchVehicle(int Id){

    Vehicle temp;
    temp.vehicleId=Id;//assign id 

     if (!bst.search(temp))//check if the vehicle exist in BST or not
        return nullptr;//if not found return null ptr

        //if founded then get all vehicle in sorted order
    DynamicArray<Vehicle> arr = bst.inorderTraversal();

    //using array to find the exact vehicle
    for (int t= 0; t< arr.getSize(); t++)
    {
        if (arr.get(t).vehicleId == Id)
        {
            return new Vehicle(arr.get(t));  // return safe copy
        }
    }
    return nullptr;//if vehicle doesn't found then return nullptr

 }

//  void VehicleBST::inorderDisplay(VehicleNode*node){
//     if(node==nullptr){//base case
//         return;
//     }
//     inorderDisplay(node->left);//left
//     node->vehicle->displayVehiclesInfo();//currnt node
//     inorderDisplay(node->right);//then right
//  }

 void VehicleBST::display(){//display
    cout<<"\n======Vehicle BST======\n";

    //inorder traversal
    DynamicArray<Vehicle> arr = bst.inorderTraversal();
    for (int l= 0;l < arr.getSize(); l++)//display eavh vehicle
    {
        arr.get(l).displayVehiclesInfo();
    }
 }

 void VehicleBST::deleteVehicle(int id){
    Vehicle temp;

    temp.vehicleId = id;//set id
      if (!bst.search(temp))//check if the vehicle exist
    {
        cout<<"Vehicle not found in BST!!\n";
        return;
    }
     bst.remove(temp);//remove the vehicle from BST
    cout<<"Vehicle deleted from BST successfully!!\n";
}
 
