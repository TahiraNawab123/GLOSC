#include "linkedList.h"
#include "../ShipmentTracking/trackingEvent.h"
#include <iostream>
using namespace std;

// ListNode Implementation
ListNode::ListNode(TrackingEvent* e) : event(e), next(nullptr), prev(nullptr) {}

ListNode::~ListNode() {
    if (event) {
        delete event;
        event = nullptr;
    }
}

void ListNode::display() const {
    if (event) {
        event->display();
    }
}

TrackingEvent* ListNode::getEvent() const {
    return event;
}

// LinkedList Implementation
LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insertFront(TrackingEvent* event) {
    ListNode* newNode = new ListNode(event);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

void LinkedList::insertEnd(TrackingEvent* event) {
    ListNode* newNode = new ListNode(event);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

void LinkedList::insertSorted(TrackingEvent* event) {
    if (isEmpty() || event->getTimestamp() < head->event->getTimestamp()) {
        insertFront(event);
        return;
    }

    if (event->getTimestamp() >= tail->event->getTimestamp()) {
        insertEnd(event);
        return;
    }

    ListNode* current = head;
    while (current != nullptr && current->event->getTimestamp() < event->getTimestamp()) {
        current = current->next;
    }

    if (current == nullptr) {
        insertEnd(event);
        return;
    }

    ListNode* newNode = new ListNode(event);
    newNode->next = current;
    newNode->prev = current->prev;
    
    if (current->prev != nullptr) {
        current->prev->next = newNode;
    }
    current->prev = newNode;
    
    // if inserting at head position
    if (current == head) {
        head = newNode;
    }
    
    count++;
}

void LinkedList::deleteFront() {
    if (isEmpty()) { return; } 
    ListNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    count--;
}

void LinkedList::deleteEnd() {
    if (isEmpty()) { return; }
    ListNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    count--;
}

bool LinkedList::deleteByShipmentID(string id) {
    if (isEmpty()) { return false; }
    ListNode* current = head;
    while (current != nullptr) {
        if (current->event->getShipmentID() == id) {
            if (current == head) {
                deleteFront();
                return true;
            }
            if (current == tail) {
                deleteEnd();
                return true;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool LinkedList::deleteByTimestamp(string timestamp) {
    if (isEmpty()) { return false; }
    ListNode* current = head;
    while (current != nullptr) {
        if (current->event->getTimestamp() == timestamp) {
            if (current == head) {
                deleteFront();
                return true;
            }
            if (current == tail) {
                deleteEnd();
                return true;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

ListNode* LinkedList::searchByShipmentID(string id) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->event->getShipmentID() == id) { 
            return current; 
        }
        current = current->next;
    }
    return nullptr;
}

ListNode* LinkedList::searchByTimestamp(string timestamp) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->event->getTimestamp() == timestamp) { 
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

ListNode* LinkedList::searchByEventType(string type) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->event->getEventType() == type) { 
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

ListNode* LinkedList::searchByPosition(int pos) {
    if (pos < 1 || pos > count) return nullptr;
    ListNode* current = head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    return current;
}

int LinkedList::getCount() const { 
    return count; 
}

bool LinkedList::isEmpty() const { 
    return head == nullptr; 
}

void LinkedList::displayForward() const {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        return;
    }
    ListNode* current = head;
    int pos = 1;
    while (current) {
        cout << pos << ". ";
        current->display();
        cout << endl;
        current = current->next;
        pos++;
    }
}

void LinkedList::displayBackward() const {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        return;
    }
    ListNode* current = tail;
    int pos = count;
    while (current) {
        cout << pos << ". ";
        current->display();
        cout << endl;
        current = current->prev;
        pos--;
    }
}

void LinkedList::clear() {
    while (!isEmpty()) deleteFront();
}

int LinkedList::countEventsByType(string type) const {
    int counter = 0;
    ListNode* current = head;
    while (current) {
        if (current->event->getEventType() == type) counter++;
        current = current->next;
    }
    return counter;
}

int LinkedList::countEventsByShipment(string shipmentID) const {
    int counter = 0;
    ListNode* current = head;
    while (current) {
        if (current->event->getShipmentID() == shipmentID) counter++;
        current = current->next;
    }
    return counter;
}

LinkedList* LinkedList::getEventsByShipment(string shipmentID) {
    LinkedList* result = new LinkedList();
    ListNode* current = head;
    while (current) {
        if (current->event->getShipmentID() == shipmentID) {
            TrackingEvent* copyEv = new TrackingEvent(*current->event);
            result->insertEnd(copyEv);
        }
        current = current->next;
    }
    return result;    
}

