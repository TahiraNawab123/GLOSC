#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include "AllStructures.h"

// Forward declaration for template instantiation
class Shipment;

template <typename T>
class SmartArray {
private:
    DynamicArray<T> data;   

public:
    SmartArray();
    SmartArray(int initialSize);

    void push(T value);
    void insertAt(int index, T value);
    void removeAt(int index);

    T get(int index);
    int getSize();
    bool isEmpty();
    void clear(); 
};

#endif