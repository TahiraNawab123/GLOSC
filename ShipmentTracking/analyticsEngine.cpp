#include "analyticsEngine.h"
#include "shipmentBST.h"
#include "../Common/linkedList.h"
#include "shipmentGraph.h"
#include "trackingEvent.h"
#include "../Common/smartArray.h"
#include "shipment.h"  
#include <iostream>
using namespace std;

AnalyticsEngine::AnalyticsEngine() {
    shipmentTree=new shipmentBST();
    trackingHistory=new LinkedList();
    routeNetwork=new RouteNetwork();
    delayedShipments=new SmartArray<Shipment*>();
    priorityShipments=new SmartArray<Shipment*>();
}

AnalyticsEngine::~AnalyticsEngine() {
    delete shipmentTree;
    delete trackingHistory;
    delete routeNetwork;
    delete delayedShipments;
    delete priorityShipments;
}

string AnalyticsEngine::generateTimestamp() {
    static int counter=0;  
    counter++; 
    return "T" + to_string(counter);  
}

//counting sort helper function
//counting sort helper
int AnalyticsEngine::getStatusIndex(const string& status) {
    if (status == "Pending")        return 0;
    if (status == "IN_TRANSIT")     return 1;
    if (status == "DELAYED")        return 2;
    if (status == "DELIVERED")      return 3;
    if (status == "HIGH_PRIORITY")  return 4;

    return 0;
}

void AnalyticsEngine::addShipment(Shipment* s) {
    if (!s) { return; }
    shipmentTree->insert(s);
    addTrackingEvent(s->getID(), "CREATED", "WAREHOUSE");
    if (s->isPriority()) {
        priorityShipments->push(s);
    }
}

void AnalyticsEngine::removeShipment(string trackingID) {
    Shipment* s=shipmentTree->search(trackingID);
    
    if (s && s->isPriority()) {
        for (int i=0; i<priorityShipments->getSize(); i++) {
            if (priorityShipments->get(i)->getID() == trackingID) {
                priorityShipments->removeAt(i);
                break;
            }
        } 
    }
    shipmentTree->remove(trackingID);
    addTrackingEvent(trackingID, "REMOVED", "SYSTEM");
}

Shipment* AnalyticsEngine::findShipment(string trackingID) {
    return shipmentTree->search(trackingID);
}

SmartArray<Shipment*>* AnalyticsEngine::getAllShipments() {
    return shipmentTree->inorderTraversal();
}

int AnalyticsEngine::countHighPriorityShipments() {
    return shipmentTree->countPriorityShipments();
}

SmartArray<Shipment*>* AnalyticsEngine::getPriorityShipments() {
    return shipmentTree->getPriorityShipments();
}

SmartArray<Shipment*>* AnalyticsEngine::getDelayedShipments() {
    return shipmentTree->getDelayedShipments();
}

void AnalyticsEngine::escalateAllPriority() {
    SmartArray<Shipment*>* priorities = getPriorityShipments();
    
    for (int i=0; i<priorities->getSize(); i++) {
        Shipment* s=priorities->get(i);

        if (s->isPriority()) {
            s->escalate();   //calls PriorityShipment::escalate()
        }
    }
    
    delete priorities;
}

void AnalyticsEngine::addTrackingEvent(string shipmentID, string eventType, string location) {
    // Shipment* s = shipmentTree->search(shipmentID);
    // if (s) {
    //     s->updateStatus(eventType);
    // }

    TrackingEvent* event = new TrackingEvent(shipmentID, eventType, location, generateTimestamp());

    trackingHistory->insertEnd(event);
}

void AnalyticsEngine::displayShipmentHistory(string shipmentID) {
    
    LinkedList* history = getEventsByShipment(shipmentID);
    cout << "=== HISTORY FOR SHIPMENT " << shipmentID << " ===" << endl;
    history->displayForward();
    delete history;
}

LinkedList* AnalyticsEngine::getEventsByShipment(string shipmentID) {
    return trackingHistory->getEventsByShipment(shipmentID);
}

void AnalyticsEngine::addCity(string name, int traffic) {
    routeNetwork->addCity(name, traffic);
}

void AnalyticsEngine::addRoute(string from, string to, int distance, int time) {
    routeNetwork->addRoute(from, to, distance, time);
}

void AnalyticsEngine::BFSTraversal(string startCity) {
    routeNetwork->BFS(startCity);
}

void AnalyticsEngine::DFSTraversal(string startCity) {
    routeNetwork->DFS(startCity);
}


void AnalyticsEngine::bubbleSortByWeight() {
    SmartArray<Shipment*>* shipments = getAllShipments();
    int n = shipments->getSize();
    if (n == 0) { 
        delete shipments; 
        return;
    }

    Shipment** arr = new Shipment*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = shipments->get(i);
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j]->getWeight() > arr[j+1]->getWeight()) {
                Shipment* tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    cout << "=== BUBBLE SORT BY WEIGHT (O(n^2)) ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << arr[i]->getID() << " - " << arr[i]->getWeight() << " kg" << endl;
    }
    delete[] arr;
    delete shipments;
}

void AnalyticsEngine::countingSortByStatus() {

    SmartArray<Shipment*>* arr = getAllShipments();
    int n = arr->getSize();

    if (n == 0) {
        delete arr;
        return;
    }

    //5 possible statuses
    int count[5] = {0};

    //STEP 1: frequency count
    for (int i = 0; i < n; i++) {
        int idx = getStatusIndex(arr->get(i)->getStatus());
        count[idx]++;
    }

    //STEP 2: Prefix sum
    for (int i = 1; i < 5; i++) {
        count[i] += count[i - 1];
    }

    //STEP 3: output array
    Shipment** output = new Shipment*[n];

    for (int i = n - 1; i >= 0; i--) {
        Shipment* s = arr->get(i);
        int idx = getStatusIndex(s->getStatus());
        count[idx]--;
        output[count[idx]] = s;
    }

    //STEP 4: display sorted result
    cout << "=== COUNTING SORT BY STATUS (O(n)) ===";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". "
             << output[i]->getID()
             << " → " << output[i]->getStatus()
             << endl;
    }

    delete[] output;
    delete arr;
}

void AnalyticsEngine::calculateSuccessRate() {
    SmartArray<Shipment*>* shipments = getAllShipments();
    int total = shipments->getSize();
    int delivered = 0;
    for (int i = 0; i < total; i++) {
        if (shipments->get(i)->getStatus() == "DELIVERED") { 
            delivered++; 
        }
    }
    double rate = (total > 0) ? (delivered * 100.0 / total) : 0.0;
    cout << "Success Rate: " << rate << "% (" << delivered << "/" << total << ")" << endl;
    delete shipments;
}

void AnalyticsEngine::displayAllShipments() {
    SmartArray<Shipment*>* shipments = getAllShipments();
    cout << "== ALL SHIPMENTS (" << shipments->getSize() << ") ===" << endl;
    for (int i = 0; i < shipments->getSize(); i++) {
        cout << i+1 << ". " << shipments->get(i)->getDetails() << endl;
    }
    delete shipments;
}

void AnalyticsEngine::displayRouteNetwork() {
    routeNetwork->displayGraph();
}

void AnalyticsEngine::displayAlerts() {
    SmartArray<Shipment*>* delayed = getDelayedShipments();
    cout << "=== SYSTEM ALERTS ===" << endl;
    cout << "Delayed Shipments: " << delayed->getSize() << endl;
    for (int i = 0; i < delayed->getSize(); i++) {
        cout << "ALERT: " << delayed->get(i)->getDetails() << endl;
    }
    delete delayed;
}







