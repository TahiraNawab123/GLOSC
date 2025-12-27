#include "smartArray.h"
#include "AllStructures.h"
#include "../ShipmentTracking/shipment.h"

// Default constructor
template<typename T>
SmartArray<T>::SmartArray() : data(10) {}

// Parameterized constructor
template<typename T>
SmartArray<T>::SmartArray(int initialSize) : data(initialSize) {}

// Add at end
template<typename T>
void SmartArray<T>::push(T value) {
    data.push(value);
}

// Insert at index
template<typename T>
void SmartArray<T>::insertAt(int index, T value) {
    data.insertAt(index, value);
}

// Remove by index
template<typename T>
void SmartArray<T>::removeAt(int index) {
    data.removeAt(index);
}

// Get element
template<typename T>
T SmartArray<T>::get(int index) {
    return data.get(index);
}

// Size
template<typename T>
int SmartArray<T>::getSize() {
    return data.getSize();
}

// Empty check
template<typename T>
bool SmartArray<T>::isEmpty() {
    return data.isEmpty();
}

// Clear array
template<typename T>
void SmartArray<T>::clear() {
    data.clear();
}

// Explicit template instantiations for commonly used types
template class SmartArray<Shipment*>;
template class SmartArray<int>;
template class SmartArray<string>;

