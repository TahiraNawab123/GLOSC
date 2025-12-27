#include "OrderBST.h"

// constructor to initialize an empty BST
OrderBST::OrderBST() {
    root = nullptr;
}

// destructor to free all allocated nodes
OrderBST::~OrderBST() {
    freeTree(root);
}

                      // === private helper functions ===
// recursively free all nodes in the tree
void OrderBST::freeTree(Node* root) {
    if (root == nullptr)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// recursively insert an order into the BST
OrderBST::Node* OrderBST::insertHelper(Node* root, const Order& order) {
    // create a new node if tree or subtree is empty
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->data = order;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    // insert in based on order ID
    if (order.id < root->data.id)
        root->left = insertHelper(root->left, order);
    else
        root->right = insertHelper(root->right, order);
    return root;
}

// recursively print BST using in-order traversal
void OrderBST::printInOrderHelper(Node* root) const {
    if (root == nullptr)
        return;
    printInOrderHelper(root->left);
    cout << "ID: " << root->data.id << " | Customer: " << root->data.customerName << endl;

    printInOrderHelper(root->right);
}

// recursively searche for an order by ID
Order* OrderBST::searchHelper(Node* root, int id) {
    if (root == nullptr)
        return nullptr;

    if (root->data.id == id)
        return &root->data;

    if (id < root->data.id)
        return searchHelper(root->left, id);

    return searchHelper(root->right, id);
}

                    // === public functions ===
// insert a new order into the BST
void OrderBST::insert(const Order& order) {
    root = insertHelper(root, order);
}

// print all orders in sorted order
void OrderBST::printInOrder() const {
    cout << "\t === Binary Search Tree ===" << endl;
    printInOrderHelper(root);
}

// search for an order by ID
Order* OrderBST::search(int id) {
    return searchHelper(root, id);
}
