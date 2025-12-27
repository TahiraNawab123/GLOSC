#ifndef REPLENISHMENTSYSTEM_H
#define REPLENISHMENTSYSTEM_H

#include <iostream>
#include "ProductCatalog.h"
#include "Product.h"
using namespace std;

class ReplenishmentSystem {
private:
    ProductCatalog<Product>* catalog;   // pointer to product catalog
    int threshold;  // min stock limit

public: // constructir 
    ReplenishmentSystem(ProductCatalog<Product>* cat = nullptr, int thresh = 5);
    // setter hai yr
    void setThreshold(int t);
    void attachCatalog(ProductCatalog<Product>* cat); // chngs ctatalog refrnce

    // Check if product quantity is below threshold
    bool needsReplenishment(int productId) const;

    // Checks stock and generate alert
    void checkAndAlert(int productId) const;
};

#endif
