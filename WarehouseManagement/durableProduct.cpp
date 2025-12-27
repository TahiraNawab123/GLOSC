#include "DurableProduct.h"
#include <iostream>
// constructor 
DurableProduct::DurableProduct(int pid, const char* pname, int qty)
    : Product(pid, pname, qty) {}
// display fuction
void DurableProduct::print() const {
    Product::print();
    cout << " (Durable)";
}
