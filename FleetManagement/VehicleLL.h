#ifndef VEHICLELL_H
#define VEHICLELL_H

#include <iostream>
using namespace std;
#include <string>
#include "Vehicle.h"


//---------------linked list-------------------


template <typename T>

class VehicleNodeLL
{
public:
     T vehicle;
    VehicleNodeLL<T> *next;//pointer to next node
    VehicleNodeLL(T d){//constructor
        vehicle=d;
        next=nullptr; 
    }
   
};

template<typename T>
class VehicleList
{
public:
    VehicleNodeLL<T> *head; //head pointer

   VehicleList(){//constructor
   head=nullptr;
    }
    
    void addVehicle(T item){
        VehicleNodeLL<T>* newNode= new VehicleNodeLL<T>(item);// add newnode
         if(head==nullptr){//check if the list is empty
            head=newNode;//new Node will be head
            return;
         }

            VehicleNodeLL<T>*temp=head;//check if the list is not emmpty then move to the last last node
            while(temp->next!=nullptr){
            temp=temp->next;//move temp to the next
     }
           temp->next=newNode;//attach new node to the end

    }

   void display(){
        if(head==nullptr){//if the list is empty
            cout<<"No vehicles founded!\n";
            return;
     }  
       VehicleNodeLL<T>*temp=head;//start from head
       while(temp!=nullptr){
        temp->vehicle->displayVehiclesInfo();
        temp=temp->next;//move to the next node
       }
 }
   T searchById(int id){
        VehicleNodeLL<T>*temp=head;

        while(temp!= nullptr){
 
            if(temp->vehicle->vehicleId==id)//check if the id matches
            return temp->vehicle;
            temp=temp->next;//move to the next node

        }
        return nullptr;//return null ptr if the vehicle not found
    }


   int countVehicle(){
        int count=0;
        VehicleNodeLL<T>*temp =head;

        while(temp!=nullptr){

         count++;//increase cout for each node
         temp=temp->next;  //move to the next node

        }
        return count; //return total count
       
    }

   bool deleteVehicle(int id){
        //check if the list is empty or not
   if(head==nullptr){
    cout<<"List is empty\n";
    return false;
   }
   //case 2 
   //check if the first node has the sane id
  if(head->vehicle->vehicleId==id){
    VehicleNodeLL<T>* deleteNode=head;
    head= head->next;//move head to next node
    delete deleteNode->vehicle;//delete vehicle
    delete deleteNode;//delete node
    cout<<"Vehicle delete! \n";
    return true;
  }
  //search other nodes
   VehicleNodeLL<T>* current=head;//current pointer
   VehicleNodeLL<T>* previous=nullptr;//node just before the current node
//move foward until we the vehicle or reach at the end of node
   while(current!=nullptr && current->vehicle->vehicleId!=id){
    previous=current;//move previous foward
    current= current->next;//move current forward
   }
   if(current ==nullptr){//if not found then return false
    cout<<"Vehicle not founded! \n";
    return false;
   }
   //if we found the node
   previous->next=current->next;
   delete current->vehicle;//delete vehicle data
   delete current;//delte node
   cout<<"Vehicle delete! \n";
   return true;

    }
   
    //================sorting================
 void insertionSortByCapacity() {
  if (head == nullptr || head->next == nullptr) {//check if the list have only 0 or 1 node
  cout << "List too small to sort!\n";
  return;
}
VehicleNodeLL<T>* sorted =nullptr; // New empty sorted list
VehicleNodeLL<T>* current =head;
while (current != nullptr) {//go through all nodes
VehicleNodeLL<T>* nextNode = current->next;//save thr next node
//case 1 Insert at beginning
if (sorted == nullptr || sorted->vehicle->vehiclecapacity >= current->vehicle->vehiclecapacity) {
current->next = sorted;
sorted = current;
}
else {//case 2 insert in the middle or end
VehicleNodeLL<T>* temp = sorted;
  while (temp->next != nullptr && temp->next->vehicle->vehiclecapacity < current->vehicle->vehiclecapacity) {
  temp=temp->next;
}
  current->next = temp->next;
   temp->next = current;
}
    current = nextNode;//move to next node
 }
    head = sorted;//replace with origial head
    cout << "Insertion Sort by Capacity Completed!!!\n";
}

 ~VehicleList() {//destrcutor
    VehicleNodeLL<T>* temp;
    while(head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;//delete each  node
    }
  }

};

#endif