#ifndef STORAGEBIN_H
#define STORAGEBIN_H

#include <iostream>
#include "Product.h"
using namespace std;

class StorageBin {
private:
    int binId;                // unique bin ID (0-based)
    int capacity;             // max products
    int used;                 // current used slots
    Product** slots;          // product storage

    // -------- GRAPH (SHARED AMONG ALL BINS) --------
    static int** adjacency;   // adjacency matrix
    static int totalBins;     // total number of bins

public:
    // constructor (totalBins passed once from Warehouse)
    StorageBin(int id = 0, int cap = 10);
    ~StorageBin();

    // product functions
    bool addProduct(Product* p);
    bool removeProduct(int productId);

    // getters
    int getUsed() const;
    int getCapacity() const;
    int getId() const;

    // display
    void printBin() const;

    // graph functions
    static void initializeGraph(int bins);   // create NxN graph
    void connectBin(int from, int to);        // add edge
    void showConnections() const;             // show edges
    static void showAdjacencyMatrix();
};

#endif