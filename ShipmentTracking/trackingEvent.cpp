#include "trackingEvent.h"
#include <iostream>
using namespace std;

// TrackingEvent Implementation
TrackingEvent::TrackingEvent(string id, string type, string loc, string time) : shipmentID(id), eventType(type), location(loc), timestamp(time) {}

// Getters
string TrackingEvent::getShipmentID() const {
    return shipmentID;
}

string TrackingEvent::getEventType() const {
    return eventType;
}

string TrackingEvent::getLocation() const {
    return location;
}

string TrackingEvent::getTimestamp() const {
    return timestamp;
}

// Setters
void TrackingEvent::setShipmentID(const string& id) {
    shipmentID=id;
}

void TrackingEvent::setEventType(const string& type) {
    eventType=type;
}

void TrackingEvent::setLocation(const string& loc) {
    location=loc;
}

void TrackingEvent::setTimestamp(const string& time) {
    timestamp=time;
}

void TrackingEvent::display() const {
    cout<<"["<<timestamp<<"] "<<shipmentID<<": "<<eventType<<" at "<<location;
}
