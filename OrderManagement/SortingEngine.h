#ifndef SORTING_ENGINE_H
#define SORTING_ENGINE_H
#include "Order.h"
using namespace std;

// Sorting engine
// provides sorting and searching algorithms for orders
class SortingEngine {
public:
    // sorting algorithms
    // selection sort
    void selectionSort(Order* arr, int n, int option);

    // quick sort
    void quickSort(Order* arr, int low, int high, int option);

    // counting sort specifically for priority
    void countingSortByPriority(Order* arr, int n);

    // searching algorithm
    // binary search to search an order by ID
    int binarySearchById(Order* arr, int n, int id);
private:
    // compare two orders based on selected option
    bool compare(const Order& a, const Order& b, int option);
};

#endif
