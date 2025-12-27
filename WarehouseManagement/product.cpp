#include "Product.h"
#include<iostream>
using namespace std;
// contrutor
Product::Product(int pid, string pname, int qty, int uid) {
    id = pid;
    name = pname;
    quantity = qty;
    userId = uid;
}
// destructor
Product::~Product() {}
 // setters
int Product::getId() const { 
    return id; 
}

string Product::getName() const {
     return name;
}

int Product::getQuantity() const {
     return quantity; 
}

void Product::setQuantity(int q) {
     quantity = q;
}

int Product::getUserId() const {
    return userId;
}

void Product::setUserId(int uid) {
    userId = uid;
}

// print produtct info
void Product::print() const {
    cout << "Product [ ID = " << id << ", Name = " << name << ", Qty = " << quantity 
         << ", Owner User ID = " << userId << " ]";
}
