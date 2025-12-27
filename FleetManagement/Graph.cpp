#include "Graph.h"
#include "Vehicle.h"
#include "Driver.h"
#include "VehicleLL.h"
#include "VehicleBST.h"
#include <iostream>
#include <string>
 
 
 CityGraph::CityGraph(){//deafult constructor
      V=5;//total number of vertices
      adjacency_matrix=new int*[V];//array of row pointers
      for(int i=0;i<V;i++){
        adjacency_matrix[i]=new int[V];//allocate memory for each row
      }
      //intialize all edges
      for(int e=0;e<V;e++){
        for(int f=0;f<V;f++){
            adjacency_matrix[e][f]=0;
        }
      }
    }
//parametrized constructor
   CityGraph::CityGraph(int initial_number_of_vertices){//parameterized constructor

    V=initial_number_of_vertices;//number of vertices
    adjacency_matrix=new int*[V];//allocation of row pointers

    for(int a=0;a< V;a++){//allaocation of memoery for each row
      adjacency_matrix[a]=new int[V];
   }

    for(int b=0;b<V;b++)
    {//intialize all the ege with zero
    for(int c=0;c<V;c++){

        adjacency_matrix[b][c]=0;
    }
   }


    } 

CityGraph:: ~CityGraph(){

   for(int i=0;i<V;i++){
    delete[] adjacency_matrix[i];//delete each Row firstly
   }
   delete[] adjacency_matrix;//then delete the row pointer
    
}
  int CityGraph::getV()const {
    return V;
   }

    bool CityGraph::isValidVertex(int vertex_index) const{
    return (vertex_index>=0 && vertex_index<V);//check the vertex must be within range

    }
   void CityGraph:: addEdge(int source, int dest,int weight){
if(!isValidVertex(source) || !isValidVertex(dest)){//check if the index is valid or not
    cout<<"Invalid Index\n";
    return;
  }
  //add edge in both direction
  adjacency_matrix[source][dest]=weight; //from source to dest
  adjacency_matrix[dest][source]=weight; //from dest to source
  }

  void CityGraph::deleteEdge(int source, int dest){
if(!isValidVertex(source) || !isValidVertex(dest)){//check if the index is valid or not
    cout<<"Invalid Index\n";
    return;
  }
  adjacency_matrix[source][dest]=0; //from source to dest
  adjacency_matrix[dest][source]=0; //from dest to source
  }
void CityGraph::updateEdge(int old_source, int old_destination, int new_source, int new_destination,int newWeight){
 
   deleteEdge( old_source, old_destination );
    addEdge( new_source, new_destination,newWeight );
    cout<<"Edge Updated\n";

}
 bool CityGraph::checkEdgeStatus(int source, int dest){
if(!isValidVertex(source) || !isValidVertex(dest)){//check if the index is valid or not
    cout<<"Invalid Index\n";
    return false;
  }
  return adjacency_matrix[source][dest]!=0;
}

int CityGraph::getDegree(int vertex_index){
if(!isValidVertex(vertex_index)){//check if the index is valid or not
    cout<<"Invalid Index\n";
    return -1;
  }

  int index_Count=0;//if index valid then intialize count
   for(int d=0 ;d< V;d++){
    if(adjacency_matrix[vertex_index][d]!=0){
    index_Count++;//increment
    }
}
 return index_Count;//return the count

}
void CityGraph::displayGraph(const char* names[]) {
    cout << "\n===== CITY MAP (Adjacency Matrix) =====\n   ";
    for (int j = 0; j < V; j++)
          cout << j << " ";
          cout << "\n";

    for (int i = 0; i < V; i++) {//print matrix with city names
           cout <<i <<" ";
        for (int j = 0; j < V; j++) {
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << "<--- " << names[i];
        cout << "\n";
    }
}

void CityGraph::printPath(int dest, int parent[]) {
        if (dest == -1)
         return;//base case for recursion
        if (parent[dest] == -1) {
             cout << dest; 
             return;
             }
        printPath(parent[dest], parent);//print parent first the print current node
        cout << " -> " << dest;
    }

void CityGraph::printAsciiMap(const char *names[]) {
        cout << "\n== SIMPLE ASCII MAPP ==\n";
        
        for (int i = 0; i < V; i++) {//print thr city list
            cout << "[" << i << "] " << names[i] << "\n";
        }
        cout << "Roads: \n";//print all road
        for (int i = 0; i < V; i++) {
            for (int j = i+1; j < V; j++) {
                if (adjacency_matrix[i][j]!= 0) {
               cout << " " << names[i] << " (" << i << ") <-> " << names[j] << " (" << j << ") : " << adjacency_matrix[i][j] << " km\n";
                }
            }
        }
    }

Driver* pickFreeDriver(Driver drivers[], int driverCount) {

    for (int i = 0; i < driverCount; i++) {//loop run through all drivers
        if (drivers[i].isAvailable)//if any driver is avaiable 
            return &drivers[i];//the return the address of that driver
    }
    return nullptr; //if no driver available then return nullptr
}

//this functions checks whether a vehicle has eough fuel or not
bool hasEnoughFuel(Vehicle* v, int distanceKm) {

    int required = v->fuelConsumptionrate * distanceKm;//calculate fuel consumption
    return (required <= v->fuel);

}

void freeAfterTrip(Driver* d, Vehicle* v) {

 if (d != nullptr) //ccheck if the driver pointer is not null
    d->FreeDriver();//then driver available

    if (v != nullptr) //check if vehicle pointer is not NULL
    v->isVehicleavaible = true;

}


void CityGraph::dijkstra(int src, int outDistance[], int parent[]) {
        const int INF= 999999;
        int n= V;//Total number of vertices
        bool visited[128]; // V <= 128
        for (int i = 0; i < n; i++)
         {
             outDistance[i] = INF;//intially set distance to all vertices zero
             visited[i] = false;//no vertice visited at the start
              parent[i] = -1; //stores path information
        }
         outDistance[src] =0;//distance of source from itself
        for (int b = 0; b < n; b++) {
             int bestD= INF;//store minimum distance founded till yet
            int best= -1;//store vertex index with minimum distance
            for (int i= 0; i< n;i++) {//find unvisited vertex having smallest distance
                if (!visited[i] && outDistance[i] < bestD) { 
                    bestD = outDistance[i];
                     best = i; }
            }
            if (best == -1) 
            break;//if no reachable vertex is found then stop the algorithm

            visited[best] = true;

            for (int v = 0; v < n; v++) {
                if (adjacency_matrix[best][v] > 0 && !visited[v]) {
                    int d = outDistance[best] + adjacency_matrix[best][v];//calculate new distance by finding best vertex
                    if (d < outDistance[v]) {//if the founded new index is smaller then update it
                         outDistance[v] = d;//update the shortest distance
                          parent[v] = best;//store the path information
                         }
                }
            }
        }
    }

