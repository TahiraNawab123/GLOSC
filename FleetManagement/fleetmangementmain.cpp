#include "Vehicle.h"
#include "Driver.h"
#include "VehicleLL.h"
#include "VehicleBST.h"
#include "Graph.h"
#include "../Common/UITheme.h"
#include <iostream>
using namespace std;
using namespace WarehouseTheme;

void runFleetModule() {

    VehicleBST vehicleTree;
    VehicleList<Vehicle*> vehicleList;
    Driver drivers[20];
    int driverCount = 0;

    CityGraph graph(5);
    const char *cityNames[5] =
        { "Warehouse", "ZoneA", "Checkpoint", "Factory", "Highway" };

    int choice = 0;
    do {
        printHeader("FLEET MANAGEMENT SYSTEM");
        cout << WAREHOUSE_CYAN << "  Connected to Warehouse Central Hub" << RESET << "\n";
        cout << WAREHOUSE_GRAY << "  Vehicles dispatch from Warehouse for deliveries" << RESET << "\n";
        
        printSection("FLEET OPERATIONS");
        printMenuOption(1, "Vehicle Management");
        printMenuOption(2, "Driver Management");
        printMenuOption(3, "Assign / Free Driver");
        printMenuOption(4, "Linked List Vehicle Operations");
        printMenuOption(5, "Graph Operations (map)");
        printMenuOption(6, "Dijkstra Shortest Path & Simulate");
        printMenuOption(7, "Exit to Main Menu");
        
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            int vehicleChoice;
            cout << "\n====== Vehicle Menu ======\n";
            cout << "1. Add Vehicle\n";
            cout << "2. Display All Vehicles (BST)\n";
            cout << "3. Search Vehicle by ID\n";
            cout << "Enter your choice: ";
            cin >> vehicleChoice;

            if (vehicleChoice == 1) {
                int type;
                cout << "Select Vehicle Type: 1-Truck 2-Van 3-Bike: ";
                cin >> type;

                int id, cap, spd, fuelQ, cons;
                cout << "Enter Vehicle ID: ";
                cin >> id;

                if (vehicleTree.searchVehicle(id) != nullptr) {
                    cout << "Vehicle ID exists!\n";
                    continue;
                }

                cout << "Enter Capacity: ";
                cin >> cap;
                cout << "Enter Speed: ";
                cin >> spd;
                cout << "Enter Fuel (units): ";
                cin >> fuelQ;
                cout << "Enter Fuel consumption (fuel per km): ";
                cin >> cons;

                Vehicle *v = nullptr;
                if (type == 1)
                    v = new Truck(id, cap, fuelQ, spd, cons);
                else if (type == 2)
                    v = new Van(id, cap, fuelQ, spd, cons);
                else if (type == 3)
                    v = new Bike(id, cap, fuelQ, spd, cons);
                else {
                    cout << "Invalid type!\n";
                    continue;
                }

                vehicleTree.insertVehicle(v);
                vehicleList.addVehicle(v);
                printSuccess("Vehicle Added Successfully to Fleet!");
            }
            else if (vehicleChoice == 2) {
                vehicleTree.display();
            }
            else if (vehicleChoice == 3) {
                int id;
                cout << "Enter Vehicle ID: ";
                cin >> id;
                Vehicle *v = vehicleTree.searchVehicle(id);
                if (!v)
                    cout << "Vehicle not found!\n";
                else
                    v->displayVehiclesInfo();
            }
        }

        else if (choice == 2) {
            int driverChoice;
            cout << "\n====== Driver Menu ======\n";
            cout << "1. Add Driver\n";
            cout << "2. Display All Drivers\n";
            cout << "Enter choice: ";
            cin >> driverChoice;

            if (driverChoice == 1) {
                if (driverCount >= 20) {
                    cout << "Driver list full!\n";
                    continue;
                }
                int id;
                string name;
                cout << "Enter Driver ID: ";
                cin >> id;
                cout << "Enter Driver Name: ";
                cin >> name;

                drivers[driverCount++] = Driver(id, name);
                cout << "Driver Added Successfully!!!\n";
            }
            else if (driverChoice == 2) {
                if (driverCount == 0)
                    cout << "No drivers added!\n";
                for (int i = 0; i < driverCount; i++)
                    drivers[i].displayDriverInfo();
            }
        }

        else if (choice == 3) {
            int assignChoice;
            cout << "\n====== Assignment Menu ======\n";
            cout << "1.Assign Driver to Vehicle\n";
            cout << "2. Free Driver\n";
            cout << "Enter choice: ";
            cin >> assignChoice;

            if (assignChoice == 1) {
                int driverId, vehicleId;
                cout << "Enter Driver ID: ";
                cin >> driverId;
                cout << "Enter Vehicle ID: ";
                cin >> vehicleId;

                Driver *d = findDriverById(drivers, driverCount, driverId);
                if (!d) { cout << "Driver not found!\n"; continue; }

                Vehicle *v = vehicleTree.searchVehicle(vehicleId);
                if (!v) { cout << "Vehicle not found!\n"; continue; }

                if (!d->isAvailable || !v->isVehicleavaible) {
                    cout << "Driver or vehicle unavailable!\n";
                    continue;
                }

                d->assignVehicle(vehicleId);
                v->isVehicleavaible = false;
                cout << "Driver assigned successfully!\n";
            }
            else if (assignChoice == 2) {
                int driverId;
                cout << "Enter Driver ID to free: ";
                cin >> driverId;

                Driver *d = findDriverById(drivers, driverCount, driverId);
                if (!d || d->assignedVehicleId == -1) {
                    cout << "Invalid driver state!\n";
                    continue;
                }

                Vehicle *v = vehicleTree.searchVehicle(d->assignedVehicleId);
                d->FreeDriver();
                if (v) v->isVehicleavaible = true;

                cout << "Driver and vehicle free!\n";
            }
        }

        else if (choice == 4) {
            int listChoice;
            cout << "\n====== Linked List Menu ======\n";
            cout << "1. Display Linked List\n";
            cout << "2. Sort Vehicles by Capacity\n";
            cout << "3. Delete Vehicle\n";
            cout << "Enter choice: ";
            cin >> listChoice;

            if (listChoice == 1)
                vehicleList.display();
            else if (listChoice == 2)
                vehicleList.insertionSortByCapacity();
            else if (listChoice == 3) {
                int id;
                cout << "Enter Vehicle ID to delete: ";
                cin >> id;
                vehicleList.deleteVehicle(id);
            }
        }

        else if (choice == 5) {
            int graphChoice;
            cout << "\n====== Graph Menu ======\n";
            cout << "1. Add Road\n";
            cout << "2. Remove Road\n";
            cout << "3. Display Graph\n";
            cout << "Enter choice: ";
            cin >> graphChoice;

            if (graphChoice == 1) {
                int a, b, w;
                cin >> a >> b >> w;
                graph.addEdge(a, b, w);
            }
            else if (graphChoice == 2) {
                int a, b;
                cin >> a >> b;
                graph.deleteEdge(a, b);
            }
            else if (graphChoice == 3)
                graph.displayGraph(cityNames);
        }

        else if (choice == 6) {
            int src, dest;
            cin >> src >> dest;

            int distArr[128], parent[128];
            graph.dijkstra(src, distArr, parent);

            if (distArr[dest] == 999999) {
                cout << "No route found!\n";
                continue;
            }

            cout << "Shortest distance: " << distArr[dest] << "\n";
            graph.printPath(dest, parent);
            cout << endl;
        }

        else if (choice == 7) {
            printInfo("Returning to Main Menu...");
        }

    } while (choice != 7);
}
