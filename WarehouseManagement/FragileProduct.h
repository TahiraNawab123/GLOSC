#ifndef FRAGILEPRODUCT_H
#define FRAGILEPRODUCT_H

#include "Product.h"

class FragileProduct : public Product {
public:  //constrctor
    FragileProduct(int id, string name, int qty);
    // getters 
    int getType() const override { return 3; }
    int getExpiry() const override { return -1; }
    // display function
    void print() const override;
};

#endif
