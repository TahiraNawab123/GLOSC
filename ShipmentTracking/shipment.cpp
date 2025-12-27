#include "shipment.h"

Shipment::Shipment(string id, string dest, double w) : trackingID(id), destination(dest), weight(w), status("Pending") {}

Shipment::~Shipment() {}

void Shipment::updateStatus(string newStatus) {
    status=newStatus;
}

string Shipment::getDetails() {
    return "ID: "+trackingID+" | To: "+destination+" | Status: "+status+" | Weight: "+to_string(weight)+" kg";
}

void Shipment::displayInfo() {
    cout<<getDetails() << endl;
}

bool Shipment::isPriority() { return false; }

void Shipment::escalate() {}

string Shipment::getID() { return trackingID; }
string Shipment::getStatus() { return status; }
double Shipment::getWeight() { return weight; }
string Shipment::getDestination() { return destination; }

void Shipment::setWeight(double w) { weight=w; }
void Shipment::setDestination(string d) { destination=d; }

PriorityShipment::PriorityShipment(string id, string dest, double w, int level, string handling) : Shipment(id, dest, w) {
    priorityLevel=level;
    specialHandling=handling;
    status="HIGH_PRIORITY";
}

PriorityShipment::~PriorityShipment() {}

string PriorityShipment::getDetails() {
    return Shipment::getDetails()+" | Priority: "+to_string(priorityLevel)+" | Handling: "+specialHandling;
}

void PriorityShipment::displayInfo() {
    cout<<getDetails()<<endl;
}

bool PriorityShipment::isPriority() { return true; }
int PriorityShipment::getPriorityLevel() { return priorityLevel; }
string PriorityShipment::getSpecialHandling() { return specialHandling; }

void PriorityShipment::escalatePriority() {
    if (priorityLevel>1) {
        priorityLevel--;
        cout<<"Priority escalated to level "<<priorityLevel<<" for shipment "<<getID()<<endl;
    }
}

void PriorityShipment::escalate() {
    escalatePriority();  
}

