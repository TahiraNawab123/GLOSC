#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

class TrackingEvent; //forward declaration

class ListNode {
private:
    TrackingEvent* event;
    ListNode* next;
    ListNode* prev;
    
    //make LinkedList a friend class to access private members
    friend class LinkedList;

public:
    ListNode(TrackingEvent* e);
    ~ListNode();
    
    //public functions for display 
    void display() const;
    TrackingEvent* getEvent() const;
};

class LinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int count;

public:
    LinkedList();
    ~LinkedList();

    void insertFront(TrackingEvent* event);
    void insertEnd(TrackingEvent* event);
    void insertSorted(TrackingEvent* event);

    void deleteFront();
    void deleteEnd();
    bool deleteByShipmentID(string id);
    bool deleteByTimestamp(string timestamp);

    ListNode* searchByShipmentID(string id);
    ListNode* searchByTimestamp(string timestamp);
    ListNode* searchByEventType(string type);
    ListNode* searchByPosition(int pos);

    int getCount() const;
    bool isEmpty() const;
    void displayForward() const;
    void displayBackward() const;
    void clear();

    int countEventsByType(string type) const;
    int countEventsByShipment(string shipmentID) const;
    LinkedList* getEventsByShipment(string shipmentID);
};

#endif
