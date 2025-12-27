#ifndef SHIPMENT_GRAPH_H
#define SHIPMENT_GRAPH_H

#include <iostream>
using namespace std;

class GraphNode {
public:
    string cityName;
    int trafficLevel;

    GraphNode(string n, int traffic);
};


class RouteNetwork {
private:
    //represents one route from a city to another city
    struct Edge {
        GraphNode* dest; //points to the city where this road leads to (destination of the edge)
        int distance;    //the length of route
        int travelTime;  
        Edge* next;     //linked list of routes

        Edge(GraphNode* d, int dist, int t);
    };

    //represents a city
    struct Vertex {
        GraphNode* city;
        Edge* edgeList;       //points to the first route (edge) of city
        Vertex* next;         //linked list of cities

        Vertex(GraphNode* c);
    };

    struct Queue {
        Vertex** arr;
        int front, rear, capacity;

        Queue(int cap);
        ~Queue();
        bool isEmpty();
        void enqueue(Vertex* v);
        Vertex* dequeue();
    };

    struct Stack {
        Vertex** arr;
        int top, capacity;

        Stack(int cap);
        ~Stack();
        bool isEmpty();
        void push(Vertex* v);
        Vertex* pop();
    };

    Vertex* vertices;   //points to the head city 
    int vertexCount;    //number of cities

    Vertex* findVertex(string name);
    int indexOf(Vertex* v);

public:
    RouteNetwork();
    ~RouteNetwork();

    void addCity(string name, int traffic = 0);
    void addRoute(string from, string to, int distance, int time);
    void displayGraph();

    GraphNode* findCity(string name);
    int getCityCount();

    void BFS(string startCity);
    void DFS(string startCity);
};

#endif
