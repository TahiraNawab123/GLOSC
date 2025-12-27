#ifndef SHIPMENT_BST_H
#define SHIPMENT_BST_H

#include <iostream>
using namespace std;

// Forward declarations
class Shipment;
template<typename T> class SmartArray;

class BSTNode {
public:
    Shipment* data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Shipment* d);
    ~BSTNode();
};

class shipmentBST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, Shipment* data);
    BSTNode* searchRec(BSTNode* node, string key);
    BSTNode* removeRec(BSTNode* node, string key);
    BSTNode* findMinNode(BSTNode* node);

    void inorderRec(BSTNode* node, SmartArray<Shipment*>& arr);
    int getHeightRec(BSTNode* node);
    int getNodeCountRec(BSTNode* node);

    void destroyTree(BSTNode* node);

    void collectPriorityShipments(BSTNode* node, SmartArray<Shipment*>& arr);
    void collectDelayedShipments(BSTNode* node, SmartArray<Shipment*>& arr);

public:
    shipmentBST();
    ~shipmentBST();

    void insert(Shipment* data);
    Shipment* search(string key);
    void remove(string key);

    SmartArray<Shipment*>* inorderTraversal();

    bool isEmpty();
    int getHeight();
    int getNodeCount();

    Shipment* findMin();
    Shipment* findMax();

    int countPriorityShipments();
    SmartArray<Shipment*>* getPriorityShipments();
    SmartArray<Shipment*>* getDelayedShipments();
};

#endif
