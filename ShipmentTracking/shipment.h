#ifndef SHIPMENT_H
#define SHIPMENT_H
     
#include <iostream>    
using namespace std; 

class Shipment {
protected:
    string trackingID;
    string destination;
    string status;
    double weight;

public:
    Shipment(string id, string dest, double w);
    virtual ~Shipment();

    virtual void updateStatus(string newStatus);
    virtual string getDetails();
    virtual void displayInfo();

    virtual bool isPriority();

    virtual void escalate();

    string getID();
    string getStatus();
    double getWeight();
    string getDestination();

    void setWeight(double w);
    void setDestination(string d);
};

class PriorityShipment : public Shipment {
private:
    int priorityLevel;
// Agar parcel mein glass ka saman ho, to “special handling” = “Handle with care”
// Agar medicine ho, to special handling = “Cold storage required”
// Agar VIP shipment ho, to special handling = “Fast track / High Priority”
    string specialHandling;

public:
    PriorityShipment(string id, string dest, double w, int level, string handling);
    ~PriorityShipment();

    string getDetails() override;
    void displayInfo() override;

    bool isPriority() override;

    int getPriorityLevel();
    string getSpecialHandling();
    void escalatePriority();

    void escalate() override;
};

#endif