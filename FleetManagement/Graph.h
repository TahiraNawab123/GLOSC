#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include "Vehicle.h"
#include "Driver.h"
#include "VehicleLL.h"
#include "VehicleBST.h"

class CityGraph
{
    int V;
    int **adjacency_matrix;

public:
    CityGraph();
    CityGraph(int initial_number_of_vertices);
    ~CityGraph();
    int getV()const;
    void addEdge(int source, int dest, int weight);
    bool isValidVertex(int vertex_index) const;
    void deleteEdge(int source, int dest);
    void updateEdge(int old_source, int old_destination, int new_source, int new_destination, int newWeight);
    bool checkEdgeStatus(int source, int dest);
    int getDegree(int vertex_index);
    void displayGraph(const char* names[]);
    void printPath(int v, int parent[]);
    
    void dijkstra(int src, int outDistance[], int parent[]);
    void printAsciiMap(const char *names[]);
};

// Template function for choosing best vehicle
template <typename T>
Vehicle* chooseBestVehicleForDistance(VehicleBST &bst, VehicleList<T> &vlist, int distanceKm) {
    VehicleNodeLL<T>* current = vlist.head;
    Vehicle* best = nullptr;
    int bestRemaining = -999999;
    int bestSpeed = -1;
    while (current != nullptr) {
        Vehicle* v = current->vehicle;
        if (v->isVehicleavaible) {
            int fuelNeeded = distanceKm * v->fuelConsumptionrate;
            if (fuelNeeded <= v->fuel) {
                int remaining = v->fuel - fuelNeeded;
                if (remaining > bestRemaining || (remaining == bestRemaining && v->speed > bestSpeed)) {
                    best = v; 
                    bestRemaining = remaining; 
                    bestSpeed = v->speed;
                }
            }
        }
        current = current->next;
    }
    return best;
}
Driver* pickFreeDriver(Driver drivers[], int driverCount);
void freeAfterTrip(Driver* d, Vehicle* v);
bool hasEnoughFuel(Vehicle* v, int distanceKm);

#endif