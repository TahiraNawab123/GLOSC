#ifndef TRACKING_EVENT_H
#define TRACKING_EVENT_H

#include <string>
using namespace std;

class TrackingEvent {
private:
    string shipmentID;
    string eventType;
    string location;
    string timestamp;

public:
    TrackingEvent(string id, string type, string loc, string time);
    
    //getters
    string getShipmentID() const;
    string getEventType() const;
    string getLocation() const;
    string getTimestamp() const;
    
    //setters
    void setShipmentID(const string& id);
    void setEventType(const string& type);
    void setLocation(const string& loc);
    void setTimestamp(const string& time);
    
    void display() const;
};

#endif