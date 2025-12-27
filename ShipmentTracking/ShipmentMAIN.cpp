#include <iostream>
#include "analyticsEngine.h"
#include "shipment.h"
#include "../Common/smartArray.h"
#include "../Common/UITheme.h"
using namespace WarehouseTheme;

void showMenu() {
    printHeader("SHIPMENT TRACKING SYSTEM");
    cout << WAREHOUSE_CYAN << "  Connected to Warehouse Central Hub" << RESET << "\n";
    cout << WAREHOUSE_GRAY << "  All shipments originate from Warehouse" << RESET << "\n";
    
    printSection("SHIPMENT OPERATIONS");
    printMenuOption(1, "Add a Shipment (from Warehouse)");
    printMenuOption(2, "Remove a Shipment");
    printMenuOption(3, "Find a Shipment");
    printMenuOption(4, "Display All Shipments");
    printMenuOption(5, "Add Tracking Event");
    printMenuOption(6, "Display Shipment History");
    printMenuOption(7, "Add City to Network");
    printMenuOption(8, "Add Route to Network");
    printMenuOption(9, "Display Route Network");
    printMenuOption(10, "Sort Shipments by Weight (Bubble Sort)");
    printMenuOption(11, "Sort Shipments by Status (Counting Sort)");
    printMenuOption(12, "Display Delayed Shipments");
    printMenuOption(13, "BFS Traversal of Route Network");
    printMenuOption(14, "DFS Traversal of Route Network");
    printMenuOption(15, "Escalate All Priority Shipments");
    printMenuOption(16, "Calculate Success Rate");
    printMenuOption(17, "Exit to Main Menu");
    
    cout << "\nEnter your choice: ";
}

void runShipmentGraphModule() {
    AnalyticsEngine engine;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {

        case 1: {
            string id, dest;
            double weight;
            int priorityChoice;

            cout<<"Enter shipment ID: ";
            cin>>id;
            cout<<"Enter destination: ";
            cin>>dest;
            cout<<"Enter weight: ";
            cin>>weight;
            cout<<"Is this a priority shipment? (1=Yes, 0=No): ";
            cin>>priorityChoice;

            if (priorityChoice == 1) {
                int level;
                string handling;
                cout<<"Enter priority level (1-5): ";
                cin>>level;
                cout<<"Enter special handling: ";
                cin>>handling;

                PriorityShipment* ps =
                    new PriorityShipment(id, dest, weight, level, handling);
                engine.addShipment(ps);
            } else {
                Shipment* s = new Shipment(id, dest, weight);
                engine.addShipment(s);
            }
            printSuccess("Shipment added! Originated from Warehouse.");
            break;
        }

        case 2: {
            string id;
            cout<<"Enter shipment ID to remove: ";
            cin>>id;
            engine.removeShipment(id);
            cout<<"Shipment removed if it existed."<<endl;
            break;
        }

        case 3: {
            string id;
            cout<<"Enter shipment ID to find: ";
            cin>>id;
            Shipment* s = engine.findShipment(id);
            if (s)
                cout<<"Found: "<<s->getDetails()<<endl;
            else
                cout<<"Shipment not found."<<endl;
            break;
        }

        case 4:
            engine.displayAllShipments();
            break;

        case 5: {
            string id, type, loc;
            cout<<"Enter shipment ID: ";
            cin>>id;
            cout<<"Enter event type: ";
            cin>>type;
            cout<<"Enter location: ";
            cin>>loc;
            engine.addTrackingEvent(id, type, loc);
            break;
        }

        case 6: {
            string id;
            cout<<"Enter shipment ID: ";
            cin>>id;
            engine.displayShipmentHistory(id);
            break;
        }

        case 7: {
            string name;
            int traffic;
            cout<<"Enter city name: ";
            cin>>name;
            cout<<"Enter traffic level (1-10): ";
            cin>>traffic;
            engine.addCity(name, traffic);
            break;
        }

        case 8: {
            string from, to;
            int dist, time;
            cout<<"Enter source city: ";
            cin>>from;
            cout<<"Enter destination city: ";
            cin>>to;
            cout<<"Enter distance (km): ";
            cin>>dist;
            cout<<"Enter travel time (hrs): ";
            cin>>time;
            engine.addRoute(from, to, dist, time);
            break;
        }

        case 9:
            engine.displayRouteNetwork();
            break;

        case 10:
            engine.bubbleSortByWeight();
            break;

        case 11:
            engine.countingSortByStatus();
            break;

        case 12: {
            engine.displayAlerts();
            break;
        }

        case 13: {
            string startCity;
            cout<<"Enter starting city for BFS: ";
            cin>>startCity;
            engine.BFSTraversal(startCity);
            break;
        }

        case 14: {
            string startCity;
            cout<<"Enter starting city for DFS: ";
            cin>>startCity;
            engine.DFSTraversal(startCity);
            break;
        }

        case 15:
            engine.escalateAllPriority();
            break;

        case 16:
            engine.calculateSuccessRate();
            break;

        case 17:
            printInfo("Returning to Main Menu...");
            break;

        default:
            printError("Invalid choice!");
            break;
        }

    } while (choice != 17);
}
