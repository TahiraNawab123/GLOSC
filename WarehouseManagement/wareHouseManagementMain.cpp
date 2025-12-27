#include <iostream>
#include <string>
#include "Warehouse.h"
#include "PerishableProduct.h"
#include "DurableProduct.h"
#include "FragileProduct.h"
#include "../Common/UITheme.h"
using namespace std;
using namespace WarehouseTheme;

void runWarehouseModule() {
    Warehouse warehouse(3);

    int choice;

    do {
        printHeader("WAREHOUSE MANAGEMENT SYSTEM - CENTRAL HUB");
        cout << WAREHOUSE_CYAN << "  All products, orders, payments, and deliveries originate from here" << RESET << "\n";
        
        printSection("PRODUCT MANAGEMENT");
        printMenuOption(1, "Add Product to Warehouse");
        printMenuOption(2, "Search Product in Warehouse");
        printMenuOption(3, "Print Product Catalog (BST)");
        printMenuOption(4, "Print All Storage Bins");
        printMenuOption(5, "Add New Category");
        printMenuOption(6, "Show All Categories");
        
        printSection("INVENTORY MANAGEMENT");
        printMenuOption(7, "Print Inventory Queue (Perishables)");
        printMenuOption(8, "Serve Next Perishable Item");
        printMenuOption(9, "Check Replenishment Alert");
        
        printSection("ORDER & PAYMENT PROCESSING");
        printMenuOption(10, "Process Delivery (via Warehouse)");
        printMenuOption(11, "Send Notifications");
        printMenuOption(12, "Process Payment (via Warehouse)");
        
        printSection("WAREHOUSE INFRASTRUCTURE");
        printMenuOption(13, "Connect Two Storage Bins");
        printMenuOption(14, "Show Bin Connections");
        printMenuOption(15, "Show Adjacency Matrix");
        printMenuOption(16, "Show Warehouse Status");
        printMenuOption(17, "Exit to Main Menu");
        
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {

        case 1: {
            int id, qty, type, userId;
            char name[64];
            char category[32];
            int expiry;

            printSection("ADD PRODUCT TO WAREHOUSE");
            cout << WAREHOUSE_CYAN << "Enter User ID (Product Owner): " << RESET;
            cin >> userId;
            
            cout << WAREHOUSE_CYAN << "Enter Product ID: " << RESET;
            cin >> id;

            cout << WAREHOUSE_CYAN << "Product Name: " << RESET;
            cin >> name;

            cout << WAREHOUSE_CYAN << "Quantity: " << RESET;
            cin >> qty;

            cout << WAREHOUSE_CYAN << "Category: " << RESET;
            cin >> category;

            cout << "\nSelect Product Type:\n";
            printMenuOption(1, "Perishable");
            printMenuOption(2, "Durable");
            printMenuOption(3, "Fragile");
            printPrompt("Choice:");
            cin >> type;

            Product* p = nullptr;

            if (type == 1) {
                cout << "Expiry days: ";
                cin >> expiry;
                p = new PerishableProduct(id, name, qty, expiry);
            }
            else if (type == 2) {
                p = new DurableProduct(id, name, qty);
            }
            else {
                p = new FragileProduct(id, name, qty);
            }
            
            // Set user ID for product ownership
            p->setUserId(userId);

            warehouse.addProduct(p, category);
            warehouse.notifyActivity("Product ID " + to_string(id) + " added by User ID " + to_string(userId) + " - Quantity: " + to_string(qty));
            printSuccess("Product Added Successfully to Warehouse!");
            break;
        }

        case 2: {
            int id;
            printSection("SEARCH PRODUCT IN WAREHOUSE");
            cout << "\nEnter Product ID to search: ";
            cin >> id;

            Product* p = warehouse.searchProduct(id);
            if (p) {
                printSuccess("Product Found in Warehouse!");
                p->print();
            } else {
                printError("Product Not Found in Warehouse.");
            }
            break;
        }

        case 3:
            warehouse.printCatalog();
            break;

        case 4:
            warehouse.printAllBins();
            break;

        case 5: {
            char cat[32];
            cout << "\nEnter New Category Name: ";
            cin >> cat;
            warehouse.addCategory(cat);
            cout << "Category Added.\n";
            break;
        }

        case 6:
            warehouse.listAllCategories();
            break;

        case 7:
            warehouse.printInventory();
            break;

        case 8:
            warehouse.serveFromInventory();
            break;

        case 9: {
            int pid;
            cout << "\nEnter Product ID to check alert: ";
            cin >> pid;
            warehouse.checkReplenishment(pid);
            break;
        }

        case 10: {
            Delivery d;
            int id, dist;

            printSection("PROCESS DELIVERY VIA WAREHOUSE");
            cout << WAREHOUSE_CYAN << "Enter Product ID: " << RESET;
            cin >> id;

            cout << "Enter distance covered: ";
            cin >> dist;

            warehouse.processDelivery(d, id, dist);
            printSuccess("Delivery scheduled through Warehouse!");
            break;
        }

        case 11: {
            string msg;
            cin.ignore();
            printSection("SEND NOTIFICATION");
            cout << WAREHOUSE_CYAN << "Enter customer name to send notification: " << RESET;
            getline(cin, msg);

            warehouse.processNotification(msg);
            printSuccess("Notification sent successfully!");
            break;
        }

        case 12: {
            int orderId, amount;
            Payment p;

            printSection("PROCESS PAYMENT VIA WAREHOUSE");
            cout << WAREHOUSE_CYAN << "Enter Order ID: " << RESET;
            cin >> orderId;

            cout << WAREHOUSE_CYAN << "Enter Amount: " << RESET;
            cin >> amount;

            warehouse.processPayment(p, orderId, amount);
            printSuccess("Payment processed successfully through Warehouse!");
            break;
        }

        case 13: {
            int bin1, bin2;
            cout << "Enter first bin ID: ";
            cin >> bin1;
            cout << "Enter second bin ID: ";
            cin >> bin2;
            warehouse.connectBins(bin1, bin2);
            cout << "Bins connected successfully.\n";
            break;
        }

        case 14: {
            int sourceBin, targetBin;

            cout << "Enter bin ID whose connections you want to manage: ";
            cin >> sourceBin;

            cout << "Enter bin ID to connect Bin " << sourceBin << " with: ";
            cin >> targetBin;

            warehouse.connectBins(sourceBin, targetBin);
            cout << "Bins connected successfully!\n";

            warehouse.showBinConnections(sourceBin);
        }
        case 15:{
            printSection("WAREHOUSE BIN GRAPH");
            warehouse.showFullBinGraph();
            break;
        }
        case 16:
            printSection("WAREHOUSE STATUS");
            warehouse.showWarehouseStatus();
            break;
        case 17:
            printInfo("Returning to Main Menu...");
            break;

        default:
            printError("Invalid option. Please try again.");
        }

    } while (choice != 17);
}