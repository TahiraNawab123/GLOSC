#include "StorageBin.h"
#include <iostream>
using namespace std;

// static members
int** StorageBin::adjacency = nullptr;
int StorageBin::totalBins = 0;

// initialize graph once
void StorageBin::initializeGraph(int bins) {
    totalBins = bins;

    adjacency = new int*[bins];
    for (int i = 0; i < bins; i++) {
        adjacency[i] = new int[bins];
        for (int j = 0; j < bins; j++)
            adjacency[i][j] = 0;
    }
}

// constructor
StorageBin::StorageBin(int id, int cap) {
    binId = id;               // 0-based index
    capacity = cap;
    used = 0;

    slots = new Product*[capacity];
    for (int i = 0; i < capacity; i++)
        slots[i] = nullptr;
}

// destructor
StorageBin::~StorageBin() {
    delete[] slots;
}

// add product
bool StorageBin::addProduct(Product* p) {
    if (used >= capacity) return false;
    slots[used++] = p;
    return true;
}

// remove product
bool StorageBin::removeProduct(int productId) {
    for (int i = 0; i < used; i++) {
        if (slots[i]->getId() == productId) {
            for (int j = i; j < used - 1; j++)
                slots[j] = slots[j + 1];
            slots[--used] = nullptr;
            return true;
        }
    }
    return false;
}

// getters
int StorageBin::getUsed() const { return used; }
int StorageBin::getCapacity() const { return capacity; }
int StorageBin::getId() const { return binId; }

// print bin
void StorageBin::printBin() const {
    cout << "\n--- Storage Bin " << binId
         << " (" << used << "/" << capacity << ") ---\n";

    if (used == 0) {
        cout << "Empty.\n";
        return;
    }

    for (int i = 0; i < used; i++) {
        slots[i]->print();
        cout << "\n";
    }
}

// connect bins (undirected graph)
void StorageBin::connectBin(int from, int to) {
    if (from >= 0 && from < totalBins && to >= 0 && to < totalBins) {
        adjacency[from][to] = 1;
        adjacency[to][from] = 1;
    }
}

// show connections of THIS bin
void StorageBin::showConnections() const {

    // checks  if bin existence
    if (binId < 0 || binId >= totalBins) {
        cout << "This bin does not exist.\n";
        return;
    }

    cout << "\nGraph Connections for Bin " << (binId + 1) << ":\n";

    bool hasConnection = false;

    // checks connections with all other bins
    for (int i = 0; i < totalBins; i++) {

        if (adjacency[binId][i] == 1) {
            cout << "Bin " << (binId + 1)
                 << " is connected to Bin " << (i + 1) << endl;
            hasConnection = true;
        }
    }

    // If no connections found
    if (!hasConnection) {
        cout << "No connections found for this bin.\n";
    }
}

void StorageBin::showAdjacencyMatrix() {
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < totalBins; i++) {
        for (int j = 0; j < totalBins; j++) {
            cout << adjacency[i][j] << " ";
        }
        cout << endl;
    }
}