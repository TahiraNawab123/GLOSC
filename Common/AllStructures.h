#ifndef ALLSTRUCTURES_H
#define ALLSTRUCTURES_H
#include <iostream>
using namespace std;

// ==================== Implemented by Fleet Management & shipment tracking====================
// ---------------- Common functions ----------------
// swap function
template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// max function
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

// ----------------------------------------------------------------------------------
// ---------------- Template dynamic array  ----------------

template <typename T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

    void expand() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    // default constructor
    DynamicArray(int initialCap = 10) {
        capacity = initialCap;
        size = 0;
        arr = new T[capacity];
    }

    // destructor
    ~DynamicArray() {
        delete[] arr;
    }

    // add at end
    void push(const T& value) {
        if (size == capacity)
            expand();
        arr[size++] = value;
    }

    // insert at index
    void insertAt(int index, const T& value) {
        if (index < 0 || index > size)
            return;
        if (size == capacity)
            expand();
        for (int i = size; i > index; i--)
            arr[i] = arr[i - 1];
        arr[index] = value;
        size++;
    }

    // remove by index
    void removeAt(int index) {
        if (index < 0 || index >= size)
            return;
        for (int i = index; i < size - 1; i++)
            arr[i] = arr[i + 1];
        size--;
    }

    // get element
    T get(int index) const {
        if (index < 0 || index >= size)
            return T();
        return arr[index];
    }

    // set element
    void set(int index, const T& value) {
        if (index < 0 || index >= size)
            return;
        arr[index] = value;
    }

    // helpers
    int getSize() const {
        return size;
    }
    bool isEmpty() const {
        return size == 0;
    }
    void clear() {
        size = 0;
    }
    // raw pointer access which is needed for sorting
    T* rawArray() {
      return arr;
    }
};

// ==================== Implemented by warehouse management & Order Processing ====================
// ----------------------------------------------------------------------------------
// ---------------- Template queue  ----------------
// used in InventoryManager and OrderQueue

template <typename T>
class Queue {
private:
    T* arr;
    int front;
    int rear;
    int count;
    int capacity;

public:
    // constructor
    Queue(int cap = 20) {
        capacity = (cap <= 0) ? 20 : cap;
        arr = new T[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }
    // destructor
    ~Queue() {
        delete[] arr;
    }
    // is empty function
    bool isEmpty() const {
        return count == 0;
    }
    // is full function
    bool isFull() const {
        return count == capacity;
    }
    // size function
    int size() const {
        return count;
    }
    // enqueue function
    void enqueue(const T& value) {
        if (isFull())
            return;
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        count++;
    }
    // dequeue function
    T dequeue() {
        if (isEmpty())
            return T();
        T value = arr[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }
    // peek function
    T peek() const {
        if (isEmpty())
            return T();
        return arr[front];
    }
    // clear queue function
    void clear() {
        front = 0;
        rear = -1;
        count = 0;
    }
};

// ==================== Implemented by shipment tracking====================
// ----------------------------------------------------------------------------------
// ---------------- Template binary search tree  ----------------
// used in orders, products, shipments

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& d) {
            data = d;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    // insert recursively
    Node* insertRec(Node* node, const T& value) {
        if (!node)
            return new Node(value);

        if (value < node->data)
            node->left = insertRec(node->left, value);
        else if (value > node->data)
            node->right = insertRec(node->right, value);

        return node;
    }
    // search recursively
    Node* searchRec(Node* node, const T& key) const {
        if (!node)
            return nullptr;

        if (node->data == key)
            return node;

        if (key < node->data)
            return searchRec(node->left, key);

        return searchRec(node->right, key);
    }
    // find minimum node
    Node* findMinNode(Node* node) const {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }
    // delete recursively
    Node* deleteRec(Node* node, const T& key) {
        if (!node)
            return nullptr;

        if (key < node->data) {
            node->left = deleteRec(node->left, key);
        }
        else if (key > node->data) {
            node->right = deleteRec(node->right, key);
        }
        else {
            // node found

            // Case 1: no left child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2: no right child
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children
            else {
                Node* succ = findMinNode(node->right);
                node->data = succ->data;
                node->right = deleteRec(node->right, succ->data);
            }
        }
        return node;
    }
    // in order traversal recursively
    void inorderRec(Node* node, DynamicArray<T>& arr) const {
        if (!node)
            return;
        inorderRec(node->left, arr);
        arr.push(node->data);
        inorderRec(node->right, arr);
    }
    // height recursively
    int heightRec(Node* node) const {
        if (!node)
            return -1;
        return 1 + maxValue(heightRec(node->left),
                             heightRec(node->right));
    }
    // count recursively
    int countRec(Node* node) const {
        if (!node)
            return 0;
        return 1 + countRec(node->left) + countRec(node->right);
    }
    // destroy function
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
public:
    // constructor
    BinarySearchTree() {
        root = nullptr;
    }
    // destructor
    ~BinarySearchTree() {
        destroy(root);
    }
    // is empty function
    bool isEmpty() const {
        return root == nullptr;
    }
    // insert in tree
    void insert(const T& value) {
        root = insertRec(root, value);
    }
    // search in tree
    bool search(const T& key) const {
        return (searchRec(root, key) != nullptr);
    }
    // remove from tree
    void remove(const T& key) {
        root = deleteRec(root, key);
    }
    // get height function
    int getHeight() const {
        return heightRec(root);
    }
    // get node count function
    int getNodeCount() const {
        return countRec(root);
    }
    // in order traversal function
    DynamicArray<T> inorderTraversal() const {
        DynamicArray<T> result;
        inorderRec(root, result);
        return result;
    }
    // find minimum function
    T findMin() const {
        Node* n = findMinNode(root);
        return n ? n->data : T();
    }
    // find max function
    T findMax() const {
        Node* current = root;
        if (!current) return T();
        while (current->right)
            current = current->right;
        return current->data;
    }
};

// ==================== Implemented by Fleet Management & Order Processing ====================
// ----------------------------------------------------------------------------------
// ---------------- Template graph  ----------------
// used in city map, routes, loading stations

template <typename T>
class Graph {
private:
    int V;              // number of vertices
    T** adj;            // adjacency matrix
    // validate vertices
    bool isValidVertex(int v) const {
        return (v >= 0 && v < V);
    }
public:
    // constructor
    Graph(int vertices = 5) {
        V = vertices;
        adj = new T*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new T[V];
            for (int j = 0; j < V; j++)
                adj[i][j] = 0;
        }
    }
    // destructor
    ~Graph() {
        for (int i = 0; i < V; i++)
            delete[] adj[i];
        delete[] adj;
    }
    // get vertex count function
    int getVertexCount() const {
        return V;
    }
    // edge functions
    // add an edge
    void addEdge(int src, int dest, T weight) {
        if (!isValidVertex(src) || !isValidVertex(dest))
            return;
        adj[src][dest] = weight;
        adj[dest][src] = weight;
    }
    // delete an edge
    void deleteEdge(int src, int dest) {
        if (!isValidVertex(src) || !isValidVertex(dest))
            return;
        adj[src][dest] = 0;
        adj[dest][src] = 0;
    }
    // update an edge
    void updateEdge(int oldSrc, int oldDest, int newSrc, int newDest, T newWeight) {
        deleteEdge(oldSrc, oldDest);
        addEdge(newSrc, newDest, newWeight);
    }
    // check if there is an edge or not
    bool hasEdge(int src, int dest) const {
        if (!isValidVertex(src) || !isValidVertex(dest))
            return false;
        return adj[src][dest] != 0;
    }
    // get degree
    int getDegree(int vertex) const {
        if (!isValidVertex(vertex))
            return -1;
        int count = 0;
        for (int i = 0; i < V; i++)
            if (adj[vertex][i] != 0)
                count++;
        return count;
    }
    // display functions
    // display matrix
    void displayMatrix(const char* names[] = nullptr) const {
        cout << "\t ===== Graph Adjacency Matrix =====" << endl;
        for (int j = 0; j < V; j++)
            cout << j << " ";
        cout << endl;

        for (int i = 0; i < V; i++) {
            cout << i << " ";
            for (int j = 0; j < V; j++)
                cout << adj[i][j] << " ";
            if (names)
                cout << "  <-- " << names[i];
            cout << endl;
        }
    }
    // print ASCII map
    void printAsciiMap(const char* names[]) const {
        cout << "\t ===== ASCII Map =====" << endl;
        for (int i = 0; i < V; i++)
            cout << "[" << i << "] " << names[i] << endl;

        cout << "Roads:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adj[i][j] != 0) {
                    cout << " " << names[i] << " (" << i << ") <-> "
                         << names[j] << " (" << j << ") : "
                         << adj[i][j] << " km" << endl;
                }
            }
        }
    }
    // Dijkstra array based implementatioon
    void dijkstra(int src, T dist[], int parent[]) const {
        const T INF = (T)999999;
        bool visited[128];   // upper bound

        for (int i = 0; i < V; i++) {
            dist[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }
        dist[src] = 0;
        for (int count = 0; count < V; count++) {
            T minDist = INF;
            int u = -1;

            for (int i = 0; i < V; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            if (u == -1)
                break;
            visited[u] = true;
            for (int v = 0; v < V; v++) {
                if (adj[u][v] > 0 && !visited[v]) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }
    // print path
    void printPath(int dest, int parent[]) const {
        if (dest == -1)
            return;
        if (parent[dest] == -1) {
            cout << dest;
            return;
        }
        printPath(parent[dest], parent);
        cout << " -> " << dest;
    }
};
// ==================== Implemented by Tahira Nawab ====================
// ----------------------------------------------------------------------------------
// ---------------- Template genral tree  ----------------

template <typename T>
class GeneralTree {
private:
    struct Node {
        T data;
        Node** children;
        int childCount;
        int capacity;

        Node(T val) {
            data = val;
            childCount = 0;
            capacity = 2;
            children = new Node*[capacity];
        }

        ~Node() {
            delete[] children;
        }
        // add child
        void addChild(Node* node) {
            if (childCount == capacity) {
                capacity *= 2;
                Node** temp = new Node*[capacity];
                for (int i = 0; i < childCount; i++)
                    temp[i] = children[i];
                delete[] children;
                children = temp;
            }
            children[childCount++] = node;
        }
    };
    Node* root;
    // helper functions
    // find node
    Node* findNode(Node* current, const T& value) const {
        if (!current) return nullptr;
        if (current->data == value)
            return current;

        for (int i = 0; i < current->childCount; i++) {
            Node* found = findNode(current->children[i], value);
            if (found) return found;
        }
        return nullptr;
    }
    // height function
    int height(Node* node) const {
        if (!node) return -1;
        if (node->childCount == 0) return 0;

        int maxH = 0;
        for (int i = 0; i < node->childCount; i++) {
            int h = height(node->children[i]);
            if (h > maxH)
                maxH = h;
        }
        return maxH + 1;
    }
    // print function
    void print(Node* node) const {
        if (!node) return;
        cout << node->data << " ";
        for (int i = 0; i < node->childCount; i++)
            print(node->children[i]);
    }
    // destroy function
    void destroy(Node* node) {
        if (!node) return;
        for (int i = 0; i < node->childCount; i++)
            destroy(node->children[i]);
        delete node;
    }
public:
    // constructor
    GeneralTree() {
        root = nullptr;
    }
    // destructor
    ~GeneralTree() {
        destroy(root);
    }
    // insert node
    void insertNode(const T& parentData, const T& value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* parent = findNode(root, parentData);
        if (!parent)
             return;
        parent->addChild(new Node(value));
    }
    // get height
    int getHeight(const T& value) const {
        Node* node = findNode(root, value);
        if (!node) return -1;
        return height(node);
    }
    // get degree
    int getDegree(const T& value) const {
        Node* node = findNode(root, value);
        if (!node) return -1;
        return node->childCount;
    }
    // print tree
    void printTree() const {
        print(root);
        cout << endl;
    }
};

// ==================== Implemented by Order Procesisng ====================
// ----------------------------------------------------------------------------------
// ---------------- Template stack for loading system ----------------

template <typename T>
class LoadingSystem {
private:
    T* arr;
    int capacity;
    int topIndex;

    void resize() {
        int newCap = capacity * 2;
        T* newArr = new T[newCap];
        for (int i = 0; i <= topIndex; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }
public:
    // constructor
    LoadingSystem(int cap = 10) {
        capacity = (cap <= 0) ? 10 : cap;
        arr = new T[capacity];
        topIndex = -1;
    }
    // destructor
    ~LoadingSystem() {
        delete[] arr;
    }
    // push function
    void push(const T& item) {
        if (topIndex + 1 == capacity)
            resize();
        arr[++topIndex] = item;
    }
    // pop function
    T pop() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex--];
    }
    // is empty function
    bool isEmpty() const {
        return topIndex == -1;
    }
    // size function
    int size() const {
        return topIndex + 1;
    }
    // print stack function
    void printStack() const {
        cout << "\t ===== Stack =====" << endl;
        for (int i = topIndex; i >= 0; i--) {
            cout << "ID: " << arr[i].id
                 << " Priority: " << arr[i].priority
                 << " Customer: " << arr[i].customerName << endl;
        }
    }
};

// ----------------------------------------------------------------------------------
// ---------------- Template linked list node  ----------------
// used in history

template <typename T>
struct HistoryNode {
    T data;
    HistoryNode* next;

    HistoryNode(const T& d) {
        data = d;
        next = nullptr;
    }
};

// ----------------------------------------------------------------------------------
// ---------------- Template linked list node  ----------------
// used in history list

template <typename T>
class HistoryList {
private:
    HistoryNode<T>* head;
public:
    // constructor
    HistoryList() {
        head = nullptr;
    }
    // destructor
    ~HistoryList() {
        HistoryNode<T>* current = head;
        while (current != nullptr) {
            HistoryNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    // add a record
    void addRecord(const T& item) {
        HistoryNode<T>* newNode = new HistoryNode<T>(item);

        if (head == nullptr) {
            head = newNode;
        } else {
            HistoryNode<T>* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }
    }
    // is empty function
    bool isEmpty() const {
        return head == nullptr;
    }
    // display function
    void display() const {
        if (head == nullptr) {
            cout << "No history available." << endl;
            return;
        }
        cout << "\t ===== Processed Order History =====" << endl;
        HistoryNode<T>* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->data.id
                 << " Priority: " << temp->data.priority
                 << " Customer: " << temp->data.customerName
                 << endl;
            temp = temp->next;
        }
    }
};

// Not used
// ----------------------------------------------------------------------------------
// ---------------- Template sorting algorithms  ----------------

// selection sort
template <typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        swapValues(arr[i], arr[minIdx]);
    }
}

// heap sort
template <typename T>
void heapify(T arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swapValues(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(T arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swapValues(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

#endif
