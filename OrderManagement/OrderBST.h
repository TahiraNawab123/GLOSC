#ifndef ORDER_BST_H
#define ORDER_BST_H
#include <iostream>
#include "Order.h"
using namespace std;

// Order binary search tree (BST)
// which stores orders sorted by Order ID
class OrderBST {
private:
    struct Node {
        Order data;     // order stored in the node
        Node* left;     // left child
        Node* right;    // right child
    };

    Node* root;         // root of the BST

    //  helper functions (recursive)
    // insert a new order into the BST
    Node* insertHelper(Node* root, const Order& order);

    // print the BST in sorted order which is in-order traversal
    void printInOrderHelper(Node* root) const;

    // searche for an order by ID
    Order* searchHelper(Node* root, int id);

    // frees all nodes of the BST (used in destructor)
    void freeTree(Node* root);
public:
    // default constructor
    OrderBST();

    // destructor to free memory
    ~OrderBST();

    // functions
    // insert a new order into the BST
    void insert(const Order& order);

    // display all orders in sorted order by ID
    void printInOrder() const;

    // search for an order by ID
    Order* search(int id);
};

#endif
