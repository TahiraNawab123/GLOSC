#ifndef ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_H
#include <iostream>
#include "Order.h"
#include "PriorityManager.h"
#include "SortingEngine.h"
#include "DocumentGenerator.h"
#include "OrderBST.h"
#include "../Common/AllStructures.h"
using namespace std;

// Base class to show inheritance
class SystemBase {
public:
    // virtual function to show inheritance
    virtual void showInfo() {
        cout << "System base is a general system for warehouse operations." << endl;
    }
    // Virtual destructor to prevent undefined behavior when deleting through base pointer
    virtual ~SystemBase() = default;
};
// ----------------------------------------------------------------------------------

// Forward declaration to avoid circular dependency
class Warehouse;

// Order processor
// central controller for order processing system
class OrderProcessor : public SystemBase {
private:
    // ---------------- Dynamic array for orders ----------------
    Order* ordersArray;      // dynamic array storing orders
    int arrayCapacity;       // total allocated capacity
    int arrayCount;          // current number of orders

    // ensure dynamic array capacity when full
    void ensureCapacity();
    // ---------------- Core data structures showing composition ----------------
    PriorityManager* pManager;          // max heap for priority handling
    LoadingSystem<Order>* loader;        // stack for loading system
    Queue<Order> queue;                  // queue for order loading
    SortingEngine sorter;                // sorting algorithms
    Graph<int>* loadingBaysGraph;        // graph for route calculation
    int totalBays;                       // number of locations in graph

    // ---------------- supporting structures showing aggregation ----------------
    HistoryList<Order> history;          // processed order history
    OrderBST bst;                        // BST for searching orders by ID
    
    // Warehouse reference for stock management
    Warehouse* warehouse;                // Pointer to warehouse for stock updates

public:
    // constructor with initial array capacity
    OrderProcessor(int initialCapacity = 50, Warehouse* wh = nullptr);

    // destructor to free dynamically allocated memory
    ~OrderProcessor();
    
    // Set warehouse reference for stock management
    void setWarehouse(Warehouse* wh);
// ----------------------------------------------------------------------------------
    // ---------------- order management functions ----------------
    // add a new order to the system
    void addOrder(Order o);

    // add order to processing queue
    bool addOrderToQueue(const Order& order);

    // linear search for order by ID
    int findOrderByIdLinear(int id);

    // process highest priority order
    void processNextByPriority();

    // load orders from queue into loading system
    void loadFromQueue();

    // display all orders
    void listAllOrders();
// ----------------------------------------------------------------------------------
    // ---------------- sorting and searching functions ----------------
    // display sorting menu
    void sortOrdersMenu();

    // display sorted orders based on criteria
    void displaySortedOrders(int criteria);

    // binary search for order by ID
    int findOrderByIdBinarySearch(int id);
// ----------------------------------------------------------------------------------
    // ---------------- file and receipt handling functions ----------------
    // generate receipt for a specific order
    void generateReceiptForOrder(int id);
// ----------------------------------------------------------------------------------
    // ---------------- graph and route functions ----------------
    // show shortest route between two points
    void showShortestRoute(int source, int dest);

    // display loading bays graph
    void demoGraph();
// ----------------------------------------------------------------------------------
    // ---------------- history and BST functions ----------------
   // show processed order history
    void showHistory();

    // display BST
    void showBST();

    // search an order in BST
    void searchBSTMenu();
// ----------------------------------------------------------------------------------
    // ---------------- inherited function override ----------------
    // display system information
    void showInfo() override;
};

#endif
