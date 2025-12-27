#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <iostream>
#include "Product.h"
using namespace std;
class CatagoryNode {
public:
     Product* product;  // product pointer
     CatagoryNode* next; // next node
    // contrutor
        CatagoryNode(Product* p) {
            product = p;
            next = nullptr;
        }
};


class CategoryManager {
private:
    string categoryName; // category name
    CatagoryNode* head; // linked list head

public:
     CategoryManager(string name = "Default"); // constructor
    ~CategoryManager(); // destructor

    void addProduct(Product* p);  // add product to category
    void printCategory() const; // display category
    string getName() const;  // return category name
};

#endif
