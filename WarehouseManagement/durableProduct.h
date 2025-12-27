#ifndef DURABLEPRODUCT_H
#define DURABLEPRODUCT_H

#include "Product.h"

class DurableProduct : public Product {
public:  // construtor
    DurableProduct(int id, const char* name, int qty);
    // getters 
    int getType() const override { return 2; }
    int getExpiry() const override { return -1; }
     // display
    void print() const override;
};

#endif
