#include "OrderProcessor.h"
#include "../WarehouseManagement/wareHouse.h"
#include <iostream>
using namespace std;

// constructor to initializes all data structures
OrderProcessor::OrderProcessor(int initialCapacity, Warehouse* wh) : queue(20)   // initialize template queue
{
    // ---------------- dynamic array setup ----------------
    arrayCapacity = initialCapacity;
    ordersArray = new Order[arrayCapacity];
    arrayCount = 0;

    // ---------------- core data structures ----------------
    pManager = new PriorityManager(20);        // priority heap
    loader   = new LoadingSystem<Order>(20);   // loading stack

    // ---------------- graph setup ----------------
    totalBays = 6;
    loadingBaysGraph = new Graph<int>(totalBays);
    
    // ---------------- warehouse reference ----------------
    warehouse = wh;

    // warehouse route connections
    loadingBaysGraph->addEdge(0, 1, 4);   // Warehouse -> Station A
    loadingBaysGraph->addEdge(0, 2, 2);   // Warehouse -> Station B
    loadingBaysGraph->addEdge(1, 2, 5);   // Station A -> Station B
    loadingBaysGraph->addEdge(1, 3, 10);  // Station A -> Station C
    loadingBaysGraph->addEdge(2, 4, 3);   // Station B -> Station D
    loadingBaysGraph->addEdge(4, 3, 4);   // Station D -> Station C
    loadingBaysGraph->addEdge(3, 5, 11);  // Station C -> Exit
}

// destructor to free dynamically allocated memory
OrderProcessor::~OrderProcessor() {
    delete[] ordersArray;
    delete pManager;
    delete loader;
    delete loadingBaysGraph;
    // Note: warehouse pointer is not owned by OrderProcessor, so we don't delete it
}

// Set warehouse reference for stock management
void OrderProcessor::setWarehouse(Warehouse* wh) {
    warehouse = wh;
}

// ----------------------------------------------------------------------------------
    // ---------------- inherited function ----------------
// display system information
void OrderProcessor::showInfo() {
    cout << "OrderProcessor which handles order creation, priority, "
         << "loading, BST, routes and receipts." << endl;
}

// ----------------------------------------------------------------------------------
   // ---------------- dynamic array functions ----------------
// ensure dynamic array capacity
void OrderProcessor::ensureCapacity() {
    if (arrayCount < arrayCapacity)
        return;

    int newCapacity = arrayCapacity * 2;
    Order* temp = new Order[newCapacity];
    for (int i = 0; i < arrayCount; i++)
        temp[i] = ordersArray[i];

    delete[] ordersArray;
    ordersArray = temp;
    arrayCapacity = newCapacity;
}

// linear search for order by ID
int OrderProcessor::findOrderByIdLinear(int id) {
    for (int i = 0; i < arrayCount; i++) {
        if (ordersArray[i].id == id)
            return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------------
   // ---------------- order management functions ----------------
// add a new order to the system
void OrderProcessor::addOrder(Order o) {
    // Validate user-product relationship and decrease stock through warehouse
    if (warehouse && o.productId > 0 && o.userId > 0) {
        if (!warehouse->decreaseStock(o.productId, o.userId)) {
            cout << "ERROR: Order cannot be processed. Product stock update failed or user validation failed." << endl;
            return;
        }
    }
    
    ensureCapacity();
    ordersArray[arrayCount++] = o;
    pManager->push(o);     // add to priority heap
    queue.enqueue(o);      // add to queue
    bst.insert(o);         // insert into BST

    // write order to file only once
    DocumentGenerator::getInstance() ->appendOrderToFile(o, "Files/orders.txt");
    cout << "Order has been added successfully!" << endl;
}

// add order to queue
bool OrderProcessor::addOrderToQueue(const Order& order) {
    queue.enqueue(order);
    return true;
}

// ----------------------------------------------------------------------------------
    // ---------------- priority and queue processing functions ----------------
// process highest priority order
void OrderProcessor::processNextByPriority() {
    if (pManager->isEmpty()) {
        cout << "No orders in priority heap." << endl;
        if (warehouse) {
            warehouse->notifyActivity("Order processing attempted but priority queue is empty");
        }
        return;
    }
    Order order = pManager->pop();
    cout << "Processing the highest priority order ID which is: " << order.id << endl;
    loader->push(order);        // push to stack
    history.addRecord(order);  // add to history
    
    // Notify warehouse of order processing
    if (warehouse) {
        warehouse->notifyActivity("Order ID " + to_string(order.id) + " processed (Priority: " + to_string(order.priority) + ", Product ID: " + to_string(order.productId) + ")");
    }
}

// load all orders from queue to loading system
void OrderProcessor::loadFromQueue() {
    if (queue.isEmpty()) {
        cout << "The queue is empty." << endl;
        if (warehouse) {
            warehouse->notifyActivity("Order loading attempted but queue is empty");
        }
        return;
    }
    int loadedCount = 0;
    while (!queue.isEmpty()) {
        Order order = queue.dequeue();
        cout << "Loading order from queue whose ID is: " << order.id << endl;
        loader->push(order);
        loadedCount++;
    }
    // Notify warehouse of batch loading
    if (warehouse) {
        warehouse->notifyActivity("Loaded " + to_string(loadedCount) + " order(s) from queue to loading system");
    }
}

// ----------------------------------------------------------------------------------
    // ---------------- display functions ----------------
// display all orders
void OrderProcessor::listAllOrders() {
    if (arrayCount == 0) {
        cout << "No orders available." << endl;
        return;
    }
    cout << "\t === All orders ===" << endl;
    for (int i = 0; i < arrayCount; i++) {
        cout << "ID: " << ordersArray[i].id
             << " Priority: " << ordersArray[i].priority
             << " Name: " << ordersArray[i].customerName
             << endl;
    }
}

// ----------------------------------------------------------------------------------
    // ---------------- sorting and searching functions ----------------
// sorting menu
void OrderProcessor::sortOrdersMenu() {
    if (arrayCount == 0) {
        cout << "No orders to sort." << endl;
        return;
    }
    cout << "\t === Sort by ===" << endl;
    cout << "1. Priority" << endl;
    cout << "2. Distance" << endl;
    cout << "3. Value" << endl;
    cout << "Please enter your option: ";
    int option;
    cin >> option;

    cout << "\t === Algorithm ===" << endl;
    cout << "1. Selection sort" << endl;
    cout << "2. Quick sort" << endl;
    cout << "3. Counting sort (only for priority)" << endl;
    cout << "Please enter your option: ";
    int algo;
    cin >> algo;

    if (algo == 1) {
        sorter.selectionSort(ordersArray, arrayCount, option);
        displaySortedOrders(option);
    }
    else if (algo == 2) {
        sorter.quickSort(ordersArray, 0, arrayCount - 1, option);
        displaySortedOrders(option);
    }
    else if (algo == 3) {
        if (option != 1) {
            cout << "Count sort only works if you want to sort by priority." << endl;
            return;
        }
        sorter.countingSortByPriority(ordersArray, arrayCount);
        displaySortedOrders(option);
    }
    else {
        cout << "Invalid option. Please try again!" << endl;
    }
}

// display sorted orders
void OrderProcessor::displaySortedOrders(int criteria) {
    cout << "\t === Sorted Orders ===" << endl;
    for (int i = 0; i < arrayCount; i++) {
        cout << "ID: " << ordersArray[i].id << " | ";
        if (criteria == 1)
            cout << "Priority: " << ordersArray[i].priority;
        else if (criteria == 2)
            cout << "Distance: " << ordersArray[i].distance;
        else
            cout << "Value: " << ordersArray[i].value;
        cout << endl;
    }
}

// binary search by ID
int OrderProcessor::findOrderByIdBinarySearch(int id) {
    return sorter.binarySearchById(ordersArray, arrayCount, id);
}

// ----------------------------------------------------------------------------------
   // ---------------- receipt and history functions ----------------
// display receipt for an order meaning no file writing
void OrderProcessor::generateReceiptForOrder(int id) {
    int position = findOrderByIdLinear(id);

    if (position == -1) {
        cout << "Order ID was not found." << endl;
        return;
    }
    cout << "\t === Order Details ===" << endl;
    cout << "Order ID      : " << ordersArray[position].id << endl;
    cout << "Customer name : " << ordersArray[position].customerName << endl;
    cout << "Priority      : " << ordersArray[position].priority << endl;
    cout << "Deadline      : " << ordersArray[position].deadline << endl;
    cout << "Value         : " << ordersArray[position].value << endl;
    cout << "Distance (in km) : " << ordersArray[position].distance << endl;
    cout << "Description   : " << ordersArray[position].description << endl;
}

// display processed order history
void OrderProcessor::showHistory() {
    history.display();
}

// ----------------------------------------------------------------------------------
   // ---------------- BST functions ----------------
// display BST
void OrderProcessor::showBST() {
    bst.printInOrder();
}

// search an order in BST
void OrderProcessor::searchBSTMenu() {
    int id;
    cout << "Please enter order ID to search in BST: ";
    cin >> id;
    Order* result = bst.search(id);
    if (result)
        cout << "Order was found under the customer name: " << result->customerName << endl;
    else
        cout << "Order was not found." << endl;
}

// ----------------------------------------------------------------------------------
   // ---------------- graph and routing functions ----------------
// show shortest route using graph
void OrderProcessor::showShortestRoute(int source, int dest) {
    // input validation
    if (source < 0 || source >= totalBays ||
        dest   < 0 || dest   >= totalBays) {
        cout << "Invalid source or destination." << endl;
        cout << "Valid vertices are from 0 to " << totalBays - 1 << "." << endl;
        return;
        }

    int dist[50];
    int parent[50];
    loadingBaysGraph->dijkstra(source, dist, parent);
    if (dist[dest] >= 999999) {
        cout << "No path exists between " << source << " and " << dest << "." << endl;
        return;
    }

    cout << "Shortest distance is = " << dist[dest] << endl;
    cout << "Path is: ";
    loadingBaysGraph->printPath(dest, parent);
    cout << endl;
}

// display loading bays graph
void OrderProcessor::demoGraph() {
    cout << "\t === Warehouse loading routes graph ===" << endl;
    const char* names[] = {
        "Warehouse",
        "Station A",
        "Station B",
        "Station C",
        "Station D",
        "Exit"
    };
    loadingBaysGraph->displayMatrix(names);
    cout << endl;
    loadingBaysGraph->printAsciiMap(names);
}
