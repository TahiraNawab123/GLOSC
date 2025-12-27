#include "shipmentGraph.h"

GraphNode::GraphNode(string n, int traffic) {
    cityName=n;
    trafficLevel=traffic;
}

RouteNetwork::Edge::Edge(GraphNode* d, int dist, int t) {
    dest=d;
    distance=dist;
    travelTime=t;
    next=nullptr;
}

RouteNetwork::Vertex::Vertex(GraphNode* c) {
    city=c;
    edgeList=nullptr;
    next=nullptr;
}

RouteNetwork::Queue::Queue(int cap) {
    capacity = cap;
    arr = new Vertex*[capacity];
    front = rear = 0;
}

RouteNetwork::Queue::~Queue() {
    delete[] arr;
}

bool RouteNetwork::Queue::isEmpty() {
    return front == rear;
}

void RouteNetwork::Queue::enqueue(Vertex* v) {
    arr[rear++] = v;
}

RouteNetwork::Vertex* RouteNetwork::Queue::dequeue() {
    return arr[front++];
}

RouteNetwork::Stack::Stack(int cap) {
    capacity = cap;
    arr = new Vertex*[capacity];
    top = -1;
}

RouteNetwork::Stack::~Stack() {
    delete[] arr;
}

bool RouteNetwork::Stack::isEmpty() {
    return top == -1;
}

void RouteNetwork::Stack::push(Vertex* v) {
    arr[++top] = v;
}

RouteNetwork::Vertex* RouteNetwork::Stack::pop() {
    return arr[top--];
}

RouteNetwork::RouteNetwork() {
    vertices=nullptr;
    vertexCount=0;
}

RouteNetwork::~RouteNetwork() {
    //start with the first vertex in the vertices linked list
    Vertex* cur=vertices;

    //Outer loop: process each vertex (city) in the graph
    while (cur) {
        Vertex* tmp=cur; //store current vertex in temp
        cur=cur->next;   //move cur to the next vertex (prevents losing track of the next vertex)

        //get the edge list (routes) of current vertex (city)
        Edge* e=tmp->edgeList;
        //Inner loop: processes & deletes all edges connected to this vertex
        while (e) {
            Edge* te=e;
            e=e->next;
            delete te;
        }
        //check if vertex has a city object (GraphNode) attached
        //safety check to avoid deleting nullptr
        if (tmp->city) {
            //delete the GraphNode object which stores city information

            //includes city name and traffic level
            delete tmp->city;
            tmp->city=nullptr;
        }
        //delete the Vertex structure itself
        delete tmp;
    }
    vertices=nullptr;
    vertexCount=0;
}

RouteNetwork::Vertex* RouteNetwork::findVertex(string name) {
    Vertex* curr = vertices; // initialize curr pointer graph ke pehle city se
    // jab tak curr nullptr nhi hota
    while (curr) {
        // check if name matches with current vertex ke city ka name
        if (curr->city->cityName == name) {
            return curr; // if yes, return it
        }
        curr = curr->next; // if no, move to the next vertex
    }
    return nullptr; // if vertex (city) does not exist in graph
}

int RouteNetwork::indexOf(Vertex* v) {
    Vertex* cur=vertices;
    int idx=0;
    while (cur) {
        if (cur == v) { return idx; }
        cur = cur->next;
        idx++;
    }
    return -1;
}

void RouteNetwork::addCity(string name, int traffic) {
    if (findVertex(name) != nullptr) {
        return; //a vertex (city) with this name already exists
    }

    GraphNode* newCity=new GraphNode(name, traffic);
    Vertex* v=new Vertex(newCity);

    //if graph is empty
    if (!vertices) { //vertices exist nhi krte
        vertices=v; //new vertex hi graph ka first vertex ban jayega
    } else {
        //graph mai pehle se vertices hain
        Vertex* curr=vertices;

        //jab tak curr->next nullptr nhi hota, keep moving it forward
        while (curr->next) {
            curr=curr->next;
        }
        curr->next=v; //newly added city ko last pe rakhdo
    }
    vertexCount++;
}

void RouteNetwork::addRoute(string from, string to, int distance, int time) { //from=source city, to=destination city
    Vertex* f = findVertex(from); //store the "from" city's vertex object in f
    Vertex* t = findVertex(to);
    //check if both cities exist in graph
    if (!f || !t)  { return; } //return if any one does not exist
    //create a new edge (route) to the destination city
    Edge* e = new Edge(t->city, distance, time);
    e->next = f->edgeList; //inserts the new edge (route) at the beginning of routes wali list (source city ki)
    f->edgeList = e;   //make the newly added edge (route), the head of edgeList
}

void RouteNetwork::displayGraph() {
    if (!vertices) { //no vertices exist
        cout<<"Graph is empty."<<endl;
        return;
    }
    cout<<"=== ROUTE NETWORK ==="<<endl;
    Vertex* cur = vertices; //cur points at the first vertex (city)
    //jab tak L.L mai vertices (cities) hain
    while (cur) {
        cout << cur->city->cityName << " (Traffic: " << cur->city->trafficLevel << ")" << endl;
        Edge* e = cur->edgeList; //e points at the first edge (route)
        //prints detail of each connection 
        while (e) {
            cout << "  → " << e->dest->cityName << " (" << e->distance << "km, " << e->travelTime << "min)" << endl;
            e = e->next;  //move to edge
        }
        cout << endl;
        cur = cur->next; //move to next vertex
    }
}

GraphNode* RouteNetwork::findCity(string name) {
    Vertex* v = findVertex(name);
    //if city exists, return the city name else return nullptr
    return v ? v->city : nullptr;
}

int RouteNetwork::getCityCount() {
    return vertexCount;
}

void RouteNetwork::BFS(string startCity) {
    Vertex* start = findVertex(startCity);
    if (!start) { return; }

    bool* visited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
       
    Queue q(vertexCount);
    q.enqueue(start);
    visited[indexOf(start)]=true;

    cout<<"BFS: ";

    while (!q.isEmpty()) {
        Vertex* cur = q.dequeue();
        cout << cur->city->cityName << " ";

        Edge* e = cur->edgeList;
        while (e) {
            Vertex* next = findVertex(e->dest->cityName);
            int idx = indexOf(next);
            if (idx != -1 && !visited[idx]) {
                visited[idx] = true;
                q.enqueue(next);
            }
            e = e->next;
        }
    }
    cout << endl;
    delete[] visited;
}

void RouteNetwork::DFS(string startCity) {
    Vertex* start = findVertex(startCity);
    if (!start) return;

    bool* visited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
        
    Stack s(vertexCount);
    s.push(start);

    cout << "DFS: ";

    while (!s.isEmpty()) {
        Vertex* cur = s.pop();
        int idx = indexOf(cur);

        if (visited[idx]) { continue; }

        visited[idx] = true;
        cout << cur->city->cityName << " ";

        Edge* e = cur->edgeList;
        while (e) {
            Vertex* next = findVertex(e->dest->cityName);
            int nidx = indexOf(next);
            if (nidx != -1 && !visited[nidx]) {
                s.push(next);
            }
            e = e->next;
        }
    }
    cout << endl;
    delete[] visited;
}

