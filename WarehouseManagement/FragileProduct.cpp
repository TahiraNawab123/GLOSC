#include "FragileProduct.h"
#include <iostream>
// consttutor 
FragileProduct::FragileProduct(int pid, string pname, int qty)
    : Product(pid, pname, qty) {}
// display fucntin
void FragileProduct::print() const {
    Product::print();
    cout << " (Fragile) ";
}
