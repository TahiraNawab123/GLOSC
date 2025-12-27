#include "PriorityManager.h"
#include <iostream>
using namespace std;

// constructor to initializes heap with given capacity
PriorityManager::PriorityManager(int cap) {
    capacity = (cap <= 0) ? 10 : cap;
    heapArray = new Order[capacity];
    size = 0;
}

// destructor to free dynamically allocated memory
PriorityManager::~PriorityManager() {
    delete[] heapArray;
}

// check whether heap is empty
bool PriorityManager::isEmpty() const {
    return size == 0;
}

// return current number of elements in heap
int PriorityManager::getSize() const {
    return size;
}

// resize heap array when capacity is reached
void PriorityManager::resize() {
    int newCapacity = capacity * 2;
    Order* newArray = new Order[newCapacity];
    // copy existing elements
    for (int i = 0; i < size; i++) {
        newArray[i] = heapArray[i];
    }
    delete[] heapArray;
    heapArray = newArray;
    capacity = newCapacity;
}

// heap helper functions
// restore max heap property upward after insertion
void PriorityManager::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heapArray[parent].priority < heapArray[index].priority) {
            // swap parent and current node
            Order temp = heapArray[parent];
            heapArray[parent] = heapArray[index];
            heapArray[index] = temp;
            index = parent;  // move upward
        } else {
            break;    // heapfying is done
        }
    }
}

// restore max heap property downward after removal
void PriorityManager::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size &&
            heapArray[left].priority > heapArray[largest].priority) {
            largest = left;
        }

        if (right < size &&
            heapArray[right].priority > heapArray[largest].priority) {
            largest = right;
        }

        if (largest != index) {
            // swap current node with largest child
            Order temp = heapArray[index];
            heapArray[index] = heapArray[largest];
            heapArray[largest] = temp;

            index = largest;   // continue heapifying
        } else {
            break;    // heap restored
        }
    }
}

// public functions
// insert a new order into the heap
void PriorityManager::push(const Order& order) {
    if (size == capacity) {
        resize();   // expand heap if it is full
    }
    heapArray[size] = order;
    heapifyUp(size);
    size++;
}

// remove and return highest priority order
Order PriorityManager::pop() {
    if (size == 0) {
        // return default order if heap is empty
        return Order();
    }
    Order top = heapArray[0];
    heapArray[0] = heapArray[size - 1];
    size--;
    heapifyDown(0);
    return top;
}
