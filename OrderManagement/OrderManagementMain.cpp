#include <iostream>
#include <string>
#include "OrderProcessor.h"
#include "../Common/UITheme.h"
using namespace std;
using namespace WarehouseTheme;

// date format validating function
bool isValidDate(const string &date) {
    // check the format which should be YYYY-MM-DD
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7)
            continue;

        if (date[i] < '0' || date[i] > '9')
            return false;
    }
    return true;
}

void runOrderModule() {

    OrderProcessor processor(1000);
    processor.showInfo();
    int choice;
    
    printHeader("ORDER MANAGEMENT SYSTEM");
    cout << WAREHOUSE_CYAN << "  Connected to Warehouse Central Hub" << RESET << "\n";
    cout << WAREHOUSE_GRAY << "  Flow: Warehouse → Products → Orders → Payments → Delivery" << RESET << "\n";

    do {
        printSection("ORDER PROCESSING MENU");
        
        printMenuOption(1, "Add a new order (via Warehouse)");
        printMenuOption(2, "List all orders");
        printMenuOption(3, "Process next priority order");
        printMenuOption(4, "Load all orders from the queue");
        printMenuOption(5, "Sorting menu");
        printMenuOption(6, "Generate receipt by ID");
        printMenuOption(7, "Show loading stations graph");
        printMenuOption(8, "Show processed history");
        printMenuOption(9, "Show binary search tree");
        printMenuOption(10, "Search in binary search tree");
        printMenuOption(11, "Show shortest route");
        printMenuOption(12, "Exit to Main Menu");
        
        cout << "\nPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority, value, distance, productId, userId;
                string deadline;
                string name, description;

                printSection("ADD NEW ORDER VIA WAREHOUSE");
                cout << "Please enter Order ID: ";
                cin >> id;
                
                cout << "Please enter User ID (must match product owner): ";
                cin >> userId;
                
                cout << "Please enter Product ID: ";
                cin >> productId;

                cout << "Please enter priority: ";
                cin >> priority;
                do {
                    cout << "Please enter deadline (YYYY-MM-DD): ";
                    cin >> deadline;

                    if (!isValidDate(deadline)) {
                        printError("Invalid date format. Please try again!");
                    }
                } while (!isValidDate(deadline));

                cout << "Please enter value (price): ";
                cin >> value;

                cout << "Please enter distance (Km): ";
                cin >> distance;
                cin.ignore();

                cout << "Please enter customer name: ";
                getline(cin, name);

                cout << "Please enter the description: ";
                getline(cin, description);

                Order order(id, priority, deadline, value, distance, name, description, productId, userId);
                processor.addOrder(order);
                printSuccess("Order added successfully! Will be processed through Warehouse.");
                break;
            }
            case 2:
                processor.listAllOrders();
                break;
            case 3:
                processor.processNextByPriority();
                break;
            case 4:
                processor.loadFromQueue();
                break;
            case 5:
                processor.sortOrdersMenu();
                break;
            case 6: {
                int id;
                cout << "Please enter the ID: ";
                cin >> id;
                processor.generateReceiptForOrder(id);
                break;
            }
            case 7:
                processor.demoGraph();
                break;
            case 8:
                processor.showHistory();
                break;
            case 9:
                processor.showBST();
                break;
            case 10:
                processor.searchBSTMenu();
                break;
            case 11:
                int s, d;
                cout << "Enter the source vertex: ";
                cin >> s;
                cout << "Enter the destination vertex: ";
                cin >> d;
                processor.showShortestRoute(s, d);
                break;
            case 12:
                printInfo("Returning to Main Menu...");
                break;
            default:
                printError("Invalid option. Please try again!");
        }
    } while (choice != 12);
}
