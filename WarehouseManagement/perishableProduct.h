#ifndef PERISHABLEPRODUCT_H
#define PERISHABLEPRODUCT_H

#include "Product.h"
// inheritance
class PerishableProduct : public Product {
private:
    int expiryDays;

public:  // construtor
    PerishableProduct(int id, const char* name, int qty, int exp);

    bool isPerishable() const override { 
        return true; 
    }
    // getter
    int getExpiry() const override {
         return expiryDays; 
    }
    int getType() const override {
         return 1; 
    }

    void print() const override;
};

#endif
