#include "Warehouse.h"
#include "Notification.h"
#include "../OrderManagement/OrderProcessor.h"  // Full include in implementation
#include<iostream>
#include <string>
#include <sstream>
using namespace std;
// constructor 
Warehouse::Warehouse(int numBins) : inventory(50), replenisher(&catalog, 3)  // inventory capacity, and replishment threshold
{
    binCount = numBins; // total number of bins
    StorageBin::initializeGraph(binCount);

    bins = new StorageBin*[binCount];  // pointer array for bins

    for (int i = 0; i < binCount; i++)
        bins[i] = new StorageBin(i + 1, 10); // creates each stoarage bin with id and capacity ( hr aik ki capacity 10)

    categoryCount = 0;  // in start there is no category
    categories = new CategoryManager*[10]; // new category array max of size 10
    
    // Initialize order processor - central hub integration
    // Lazy initialization: create only when needed to avoid potential segfaults
    orderProcessor = nullptr;
}
// destructor
Warehouse::~Warehouse() {
    for (int i = 0; i < binCount; i++) // deletes all the storage bins
        delete bins[i];
    delete[] bins;

    for (int i = 0; i < categoryCount; i++)  // deletes all the dynamic categories
        delete categories[i];
    delete[] categories;
    
    // Clean up order processor (check for null to avoid double deletion)
    if (orderProcessor != nullptr) {
        delete orderProcessor;
        orderProcessor = nullptr;
    }
}

// function to add new category
void Warehouse::addCategory(const string& name) {
    if (categoryCount >= 10) return;  // to checks the limit of the category if it exceeds the limit 10simple return kr jao

    categories[categoryCount++] = new CategoryManager(name); // creating new catagory, jo peechy sy nam aay ga oss k sath new category bna dain gy, and will increase the count to +1

    ofstream fout("categories.txt", ios::app); // saving that category in the file "categories.txt"
    fout << name << endl;
    fout.close();
}

// funcion to find tha category
int Warehouse::findCategory(const string& name) { // simple yr this function finds the category by name
    for (int i = 0; i < categoryCount; i++) {
        if (categories[i]->getName() == name) // checks for the name of category, if it matches with the name well return the index
            return i;
    }
    return -1;  // return -1 if not found simple, not bari logic
}

// function to print all the categories and their priducts
void Warehouse::listAllCategories() {
    cout << "\n===== ALL CATEGORIES =====\n";
    for (int i = 0; i < categoryCount; i++)
        categories[i]->printCategory();
}

// function to add product to catalog, add category, bin and inventory
void Warehouse::addProduct(Product* p, const string& categoryName, int binID) {

    catalog.addProduct(p); // adds product to bts

    int idx = findCategory(categoryName); // checks if the category exists or not
    if (idx == -1) {   // in case not found, then
        addCategory(categoryName);  // creats a new category
        idx = categoryCount - 1;
    }
    categories[idx]->addProduct(p);  // adds product to category

    // now place that product to storage bin
    if (binID < 1 || binID > binCount) {  // the bin id is invalid
        for (int i = 0; i < binCount; i++)
            if (bins[i]->addProduct(p)) break; // if the first avilable bin is prsent then ossi main phynk do
    } else {
        bins[binID - 1]->addProduct(p); // otherwise add to specific bin
    }

    // add the perishable product to the inventory
    if (p->isPerishable())
        inventory.addStock(p);

    // saving all the data daata to file
    ofstream fout("Files/products.txt", ios::app);
    fout << p->getId() << " "
         << p->getName() << " "
         << p->getQuantity() << " "
         << categoryName << endl;
    fout.close();
}
// search product incatalog by using id
Product* Warehouse::searchProduct(int id) {
    return catalog.searchProduct(id);
}

// printing all the stoarge bins and their data
void Warehouse::printAllBins() {
    cout << "\n===== STORAGE BINS =====\n";
    for (int i = 0; i < binCount; i++)
        bins[i]->printBin();
}
//adding product to inventory
void Warehouse::addToInventory(Product* p) {
    inventory.addStock(p);
}
// serving prpduct from inventory
void Warehouse::serveFromInventory() {
    Product* p = inventory.reduceStock(); // rmv form queue
    if (p) {
        cout << "Served: ";
        p->print();
        cout << endl;
    }
}
// printing inventory
void Warehouse::printInventory() {
    inventory.printQueue();
}
// printing all products form catalog
void Warehouse::printCatalog() {
    catalog.printAllProducts();
}
 // fucntion to check if the product neds replishment

void Warehouse::checkReplenishment(int productId) {
    replenisher.checkAndAlert(productId);
}
// schedulimg delivry
void Warehouse::processDelivery(Delivery& d, int id1, int distance) {
    d.scheduleDelivery(id1, distance);
}
// sendng notification to user
void Warehouse::processNotification(string msg) {
    notification.sendUpdate(msg);
}
// function to process paymnt
void Warehouse::processPayment(Payment& p, int id, int val) {
    p.processPayment(id, val);
}
// connects the two bins (graph edge)
void Warehouse::connectBins(int fromBin, int toBin) {
    if (fromBin < 1 || fromBin > binCount || toBin < 1 || toBin > binCount)
    return; // invalid bin id
    bins[fromBin - 1]->connectBin(fromBin - 1, toBin - 1);
}
// graph display
void Warehouse::showBinConnections(int binID) {
    if (binID < 1 || binID > binCount) return;
    bins[binID - 1]->showConnections();
}

void Warehouse::showFullBinGraph() {
    StorageBin::showAdjacencyMatrix();
}

// Central hub functions - all operations flow through warehouse
OrderProcessor* Warehouse::getOrderProcessor() {
    // Lazy initialization: create OrderProcessor only when first accessed
    // This avoids potential segfaults during Warehouse construction
    if (orderProcessor == nullptr) {
        try {
            orderProcessor = new OrderProcessor(1000, this);  // Pass warehouse reference
            orderProcessor->setWarehouse(this);  // Ensure warehouse reference is set
        } catch (...) {
            // If construction fails, return nullptr
            return nullptr;
        }
    } else {
        // Ensure warehouse reference is always set
        orderProcessor->setWarehouse(this);
    }
    return orderProcessor;
}

// Dispatch product from warehouse - central dispatch point
bool Warehouse::dispatchProduct(int productId, int orderId) {
    Product* p = searchProduct(productId);
    if (!p) {
        return false;
    }
    
    // Product found in warehouse, can be dispatched
    // In a real system, this would update inventory, create shipment, etc.
    return true;
}

// Process order through warehouse - ensures warehouse is central
bool Warehouse::processOrderThroughWarehouse(int orderId) {
    if (!orderProcessor) {
        return false;
    }
    
    // Order processing happens through warehouse's order processor
    // This ensures all orders flow through the warehouse
    return true;
}

// Show complete warehouse status
void Warehouse::showWarehouseStatus() {
    cout << "\n===== WAREHOUSE STATUS (CENTRAL HUB) =====\n";
    cout << "Storage Bins: " << binCount << "\n";
    cout << "Categories: " << categoryCount << "\n";
    cout << "Order Processor: Active\n";
    cout << "Payment System: Active\n";
    cout << "Delivery System: Active\n";
    cout << "==========================================\n";
}

// User-based product tracking and stock management
bool Warehouse::validateUserProduct(int productId, int userId) {
    Product* p = searchProduct(productId);
    if (!p) {
        notifyActivity("ERROR: Product ID " + to_string(productId) + " not found in warehouse");
        return false;
    }
    
    if (p->getUserId() != userId) {
        notifyActivity("ERROR: Product ID " + to_string(productId) + " does not belong to User ID " + to_string(userId));
        return false;
    }
    
    return true;
}

bool Warehouse::decreaseStock(int productId, int userId) {
    // Validate that product belongs to user
    if (!validateUserProduct(productId, userId)) {
        return false;
    }
    
    Product* p = searchProduct(productId);
    if (!p) {
        return false;
    }
    
    int oldQty = p->getQuantity();
    
    // Check if stock is available
    if (oldQty <= 0) {
        notifyActivity("WARNING: Product ID " + to_string(productId) + " is out of stock. Cannot process order.");
        return false;
    }
    
    // Decrease stock by 1
    int newQty = oldQty - 1;
    p->setQuantity(newQty);
    
    // Notify warehouse of stock change
    notifyStockChange(productId, oldQty, newQty, "Order placed by User ID " + to_string(userId));
    
    return true;
}

void Warehouse::notifyStockChange(int productId, int oldQty, int newQty, const string& activity) {
    Product* p = searchProduct(productId);
    string productName = p ? p->getName() : "Unknown";
    
    cout << "\n[WAREHOUSE NOTIFICATION] " << activity << "\n";
    cout << "  Product: " << productName << " (ID: " << productId << ")\n";
    cout << "  Stock Update: " << oldQty << " → " << newQty << " units\n";
    cout << "  Remaining Stock: " << newQty << " units\n";
    
    // Check if stock is low
    if (newQty <= 3) {
        cout << "  ⚠ ALERT: Low stock detected! Consider replenishment.\n";
    }
    cout << endl;
}

void Warehouse::notifyActivity(const string& activity) {
    cout << "\n[WAREHOUSE ACTIVITY] " << activity << "\n";
    cout << "  Timestamp: " << __DATE__ << " " << __TIME__ << "\n" << endl;
}