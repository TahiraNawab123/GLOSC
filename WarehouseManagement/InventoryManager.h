#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <iostream>
#include <fstream>
#include "Product.h"
#include "../Common/AllStructures.h"

using namespace std;

// TEMPLATE CLASS
template <typename T>
class InventoryManager {
private:
    Queue<T> q;  // FIFO queue for inventory items

public:
    InventoryManager(int cap = 20);   // constructor with capacity

    bool isFull() const; // check if inventory is full
    bool isEmpty() const; // check if inventory is empty

    void addStock(T p);  // add item to inventory
    T reduceStock();// remove item (FIFO)
    T peek() const;  // see front item

    void printQueue() const; // display inventory
};

// constrctor
template <typename T>
InventoryManager<T>::InventoryManager(int cap) : q(cap) {}

// Check if queue is full
template <typename T>
bool InventoryManager<T>::isFull() const {
    return q.isFull();
}

// Check if queue is empty
template <typename T>
bool InventoryManager<T>::isEmpty() const {
    return q.isEmpty();
}

// Add product to inventory
template <typename T>
void InventoryManager<T>::addStock(T p) {
    if (q.isFull()) {
        cout << "Inventory is full! sorry mgr can't add\n";
        return;
    }

    q.enqueue(p); // add to queue

    ofstream log("Files/queue_log.txt", ios::app);
    log << "Added Stock: " << p->getId() << " " << p->getName() << "\n";
    log.close();
}
// function to rmv product from inventory (FIFO)
template <typename T>
T InventoryManager<T>::reduceStock() {
    if (q.isEmpty()) {
        cout << "this product has been processed in ordered menu!\n";
        return nullptr;
    }

    T item = q.dequeue();  // rmv frnt item 

    ofstream log("Files/queue_log.txt", ios::app);
    log << "Stock rmved: " << item->getId() << " " << item->getName() << "\n";
    log.close();

    return item;
}
 // peek from front 
template <typename T>
T InventoryManager<T>::peek() const {
    return q.peek();
}
 // print fucntion
template <typename T>
void InventoryManager<T>::printQueue() const {
    cout << "\n--- FIRST IN FIRST OUT BASED INVENTORY (Perishable Items) ---\n";

    if (q.isEmpty()) {
        cout << "SORRY but inventory is empty hehehehhehee\n";
        return;
    }
}

#endif
