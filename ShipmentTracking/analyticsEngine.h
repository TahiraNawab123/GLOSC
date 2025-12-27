#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include <iostream>
using namespace std;

// Forward declarations
class shipmentBST;
class LinkedList;
class RouteNetwork;
class Shipment;
template<typename T> class SmartArray;

class AnalyticsEngine {
private:
    shipmentBST* shipmentTree;
    LinkedList* trackingHistory;
    RouteNetwork* routeNetwork;

    SmartArray<Shipment*>* delayedShipments;
    SmartArray<Shipment*>* priorityShipments;

    string generateTimestamp();
    int getStatusIndex(const string& status);

public:
    AnalyticsEngine();
    ~AnalyticsEngine();

    void addShipment(Shipment* s);
    void removeShipment(string trackingID);
    Shipment* findShipment(string trackingID);
    SmartArray<Shipment*>* getAllShipments();

    int countHighPriorityShipments();
    SmartArray<Shipment*>* getPriorityShipments();
    SmartArray<Shipment*>* getDelayedShipments();

    void escalateAllPriority();

    // Tracking
    void addTrackingEvent(string shipmentID, string eventType, string location);
    void displayShipmentHistory(string shipmentID);

    LinkedList* getEventsByShipment(string shipmentID);

    // Routes
    void addCity(string name, int traffic = 0);
    void addRoute(string from, string to, int distance, int time);
    void displayRouteNetwork();
    void BFSTraversal(string startCity);
    void DFSTraversal(string startCity);

    // Sorting
    void bubbleSortByWeight();
    void countingSortByStatus();

    // Analytics
    void calculateSuccessRate();
    void displayAllShipments();
    void displayAlerts();
};

#endif