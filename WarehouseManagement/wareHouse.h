#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <fstream>
#include <string>

// all products files
#include "Product.h"
#include "PerishableProduct.h"
#include "DurableProduct.h"
#include "FragileProduct.h"
// Core system modules
#include "ProductCatalog.h"     // BST based product catalog
#include "InventoryManager.h"   // inventory (template based)
#include "StorageBin.h"         // Storage bins + graph connections
#include "CategoryManager.h"    // Product categories
#include "ReplishmentSystem.h"  // Low stock alert system
#include "Delivery.h"           // Delivery scheduling
#include "Notification.h"       // Notifications to users
#include "Payment.h"            // Payment processing

using namespace std;

// Forward declaration to avoid circular dependency
class OrderProcessor;

// warehouse class
class Warehouse {
private:
    ProductCatalog<Product> catalog;           // All products (BST)
    InventoryManager<Product*> inventory;      // Perishable inventory (Queue)
    ReplenishmentSystem replenisher;            // Reorder checker

    StorageBin** bins;                          // Dynamic storage bins
    int binCount;                               // Total bins

    Delivery delivery;                          // Delivery wali class
    Notification notification;                  // Notifications
    Payment payment;                            // Payment class
    OrderProcessor* orderProcessor;             // Central order processing system

    CategoryManager** categories;               // Product categories
    int categoryCount;                          // Total categories

public:
    Warehouse(int numBins = 3);                 // Constructor
    ~Warehouse();                               // Destructor

    // Functions for adding product and search for product
    void addProduct(Product* p, const string& categoryName, int binID = -1);
    Product* searchProduct(int id);

    // Functions to add category, find category and displaying 
    //all available list of categories
    void addCategory(const string& name);
    int findCategory(const string& name);
    void listAllCategories();

    // Funtion to print all bins
    void printAllBins();

    // Functions to add inventory, serve and display inventory 
    void addToInventory(Product* p);
    void serveFromInventory();
    void printInventory();

    // display catalog display functin
    void printCatalog();

    // Replenishment checker fucntion
    void checkReplenishment(int productId);

    // functions to process delivry, notfications and payment
    void processDelivery(Delivery& d, int id1, int distance);
    void processNotification(string customerName);
    void processPayment(Payment& p, int id, int val);

    // functions for stoarage bins 
    void connectBins(int fromBin, int toBin);
    void showBinConnections(int binID);
    void showFullBinGraph();
    
    // Central hub functions - all operations flow through warehouse
    OrderProcessor* getOrderProcessor();        // Get order processor
    bool dispatchProduct(int productId, int orderId);  // Dispatch product from warehouse
    bool processOrderThroughWarehouse(int orderId);    // Process order via warehouse
    void showWarehouseStatus();                 // Show complete warehouse status
    
    // User-based product tracking and stock management
    bool decreaseStock(int productId, int userId);      // Decrease stock when order placed (with user validation)
    bool validateUserProduct(int productId, int userId); // Check if product belongs to user
    void notifyStockChange(int productId, int oldQty, int newQty, const string& activity); // Notify warehouse of stock changes
    void notifyActivity(const string& activity);       // General activity notification to warehouse
};

#endif