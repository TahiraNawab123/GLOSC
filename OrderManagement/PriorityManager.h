#ifndef PRIORITY_MANAGER_H
#define PRIORITY_MANAGER_H
#include "Order.h"
using namespace std;

// Priority manager Max heap
// manages orders based on priority
class PriorityManager {
private:
    // heap data members
    Order* heapArray;   // dynamic array to store heap elements
    int capacity;       // total allocated capacity
    int size;           // current number of elements in heap

    // helper functions
    // restore heap property after insertion
    void heapifyUp(int index);

    // restore heap property after removal
    void heapifyDown(int index);

    // expand heap array when the capacity is full
    void resize();
public:
    // constructor with initial capacity
    PriorityManager(int cap = 10);

    // destructor to free allocated memory
    ~PriorityManager();

    // public functions
    // insert a new order into the heap
    void push(const Order& order);

    // remove and return highest priority order
    Order pop();

    // check if heap is empty
    bool isEmpty() const;

    // get number of orders currently present in the heap
    int getSize() const;
};

#endif
