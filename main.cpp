#include <iostream>
#include "Common/UITheme.h"
using namespace std;
using namespace WarehouseTheme;

// ===== Module functions declarations =====
void runWarehouseModule();
int runFleetModule();
void runOrderModule();
void runShipmentGraphModule();

int main() {
    int choice;
    
    // Display warehouse as central hub
    printWarehouseHub();
    cout << WAREHOUSE_GRAY << "  Global Logistics & Smart Supply Chain Center" << RESET << "\n";
    cout << WAREHOUSE_CYAN << "  All operations flow through the Warehouse Central Hub" << RESET << "\n";
    
    do {
        printSection("CENTRAL HUB - MAIN MENU");
        cout << "\n" << WAREHOUSE_BLUE << BOLD << "  WAREHOUSE → PRODUCTS → ORDERS → PAYMENTS → DELIVERY" << RESET << "\n\n";
        
        printMenuOption(1, "Warehouse Management System (Core Hub)");
        printMenuOption(2, "Fleet Management System (Connected via Warehouse)");
        printMenuOption(3, "Order Management System (Connected via Warehouse)");
        printMenuOption(4, "Shipment Tracking System (Connected via Warehouse)");
        printMenuOption(5, "Exit the program");
        
        cout << "\n" << WAREHOUSE_BLUE << BOLD << "Please enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {

            case 1:
                printInfo("Accessing Warehouse Management System (Central Hub)...");
                runWarehouseModule();
                break;

            case 2:
                printInfo("Accessing Fleet Management System via Warehouse...");
                runFleetModule();
                break;

            case 3:
                printInfo("Accessing Order Management System via Warehouse...");
                runOrderModule();
                break;

            case 4:
                printInfo("Accessing Shipment Tracking System via Warehouse...");
                runShipmentGraphModule();
                break;

            case 5:
                printSection("SYSTEM SHUTDOWN");
                printSuccess("Thank you for using the Warehouse Management System!");
                cout << WAREHOUSE_GRAY << "Exiting the system... Goodbye!" << RESET << endl;
                break;

            default:
                printError("Invalid choice. Please try again!");
        }
    } while (choice != 5);
    return 0;
}
