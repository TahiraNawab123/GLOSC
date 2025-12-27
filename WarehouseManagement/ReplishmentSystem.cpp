#include "ReplishmentSystem.h"


// constrctor
ReplenishmentSystem::ReplenishmentSystem(ProductCatalog<Product>* cat, int thresh) {
    catalog = cat;
    threshold = thresh;
}

void ReplenishmentSystem::setThreshold(int t) {
    threshold = t;
}

void ReplenishmentSystem::attachCatalog(ProductCatalog<Product>* cat) {
    catalog = cat;
}

// Check if product stock is below threshold
bool ReplenishmentSystem::needsReplenishment(int productId) const {
    if (!catalog) return false;  // catalog not linked

    Product* p = catalog->searchProduct(productId); // find product
    if (!p) return false; // product not found

    return p->getQuantity() <= threshold; // low stock check
}

void ReplenishmentSystem::checkAndAlert(int productId) const {
    if (!catalog) return; // catalog no found

    Product* p = catalog->searchProduct(productId);// search prodyct 

    if (!p) {
        cout << "Product not found.\n";
        return;
    }
    // Alert if quantity is low
    if (p->getQuantity() <= threshold) {
        cout << "ALERT: Product '" << p->getName()
             << "' (ID = " << p->getId()
             << ") needs replenishment! Current Qty = "
             << p->getQuantity()
             << "\n";
    }
}
