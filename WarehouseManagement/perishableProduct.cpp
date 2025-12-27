#include "PerishableProduct.h"
#include <iostream>
// constructor
PerishableProduct::PerishableProduct(int pid, const char* pname, int qty, int days)
    : Product(pid, pname, qty), expiryDays(days) {}
// displaying details
void PerishableProduct::print() const {
    Product::print();
    cout << " ( Perishable, Expiry = " << expiryDays << " days)";
}
