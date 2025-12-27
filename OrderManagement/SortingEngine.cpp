#include "SortingEngine.h"
using namespace std;

// Comparison based on selected sorting option
// option = 1 → Priority (higher first)
// option = 2 → Distance (smaller first)
// option = 3 → Value (higher first)
bool SortingEngine::compare(const Order& a, const Order& b, int option) {
    if (option == 1)
        return a.priority > b.priority;

    if (option == 2)
        return a.distance < b.distance;

    // default is to sort by value
    return a.value > b.value;
}

// selection sort, time complexity: O(n²)
void SortingEngine::selectionSort(Order* arr, int n, int option) {
    for (int i = 0; i < n - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (!compare(arr[bestIndex], arr[j], option)) {
                bestIndex = j;
            }
        }
        if (bestIndex != i) {
            Order temp = arr[i];
            arr[i] = arr[bestIndex];
            arr[bestIndex] = temp;
        }
    }
}

// quick sort, average time complexity: O(n log n)
void SortingEngine::quickSort(Order* arr, int low, int high, int option) {
    if (low >= high)
        return;
    Order pivot = arr[(low + high) / 2];
    int i = low;
    int j = high;
    while (i <= j) {
        while (compare(arr[i], pivot, option))
            i++;
        while (compare(pivot, arr[j], option))
            j--;
        if (i <= j) {
            Order temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (low < j)
        quickSort(arr, low, j, option);
    if (i < high)
        quickSort(arr, i, high, option);
}

// counting sort for priority only, time complexity: O(n)
void SortingEngine::countingSortByPriority(Order* arr, int n) {
    int count[101];   // assuming priority range is from 0 to 100
    // initialize count array
    for (int i = 0; i <= 100; i++) {
        count[i] = 0;
    }
    // count the frequency of each priority
    for (int i = 0; i < n; i++) {
        count[arr[i].priority]++;
    }
    // sum up final count in which higher priority is first
    for (int i = 99; i >= 0; i--) {
        count[i] += count[i + 1];
    }
    Order* output = new Order[n];
    // build a sorted output
    for (int i = n - 1; i >= 0; i--) {
        int p = arr[i].priority;
        count[p]--;
        output[count[p]] = arr[i];
    }
    // copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    delete[] output;
}

// binary search, time complexity: O(log n)
// binary search to find an order by ID
int SortingEngine::binarySearchById(Order* arr, int n, int id) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].id == id)
            return mid;
        if (arr[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;   // not found
}
