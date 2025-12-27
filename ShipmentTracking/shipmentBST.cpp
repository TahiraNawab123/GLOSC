#include "shipmentBST.h"
#include "../Common/smartArray.h"
#include "shipment.h"  
#include <iostream>
using namespace std;

BSTNode::BSTNode(Shipment* d) {
    data=d;
    left=nullptr;
    right=nullptr;
}

BSTNode::~BSTNode() {
    if (data) {
        delete data;
        data=nullptr;
    }
}

shipmentBST::shipmentBST() {
    root=nullptr;
}

void shipmentBST::destroyTree(BSTNode* node) {
    if (!node) { return; } //agar node nahi hai to wapas aao
    destroyTree(node->left); //pehle left subtree ko recursively delete krro
    destroyTree(node->right); //phir right subtree ko recursively delete krro
    delete node;  //current node delete karo
   //////////BSTNode destructor khud hi Shipment* data ko delete karta hai
}

shipmentBST::~shipmentBST() {
    destroyTree(root);
}

//also sorts the IDs alphabetically
BSTNode* shipmentBST::insertRec(BSTNode* node, Shipment* data) {
    if (!node) {
        return new BSTNode(data); //agar jagah khaali hai, naya node banao
    }

    if (data->getID() < node->data->getID()) {
        node->left=insertRec(node->left, data); //if nayi shipment ki ID choti hai, go left
    } else if (data->getID() > node->data->getID()) {
        node->right=insertRec(node->right, data); //if nayi shipment ki ID bari hai, go right
    } else {
        return node; //in case of duplicate id ignore insert (as tracking ids are unique) & return the existing node
    }

    return node;
}

void shipmentBST::insert(Shipment* data) {
    root=insertRec(root, data);  //root se insert krna sharu krro
}

BSTNode* shipmentBST::searchRec(BSTNode* node, string key) {
    if (!node) {
        return nullptr; //base case: node nhi milla
    }
    if (node->data->getID()==key) {
        return node; //mil gya
    }
    if (key < node->data->getID()) {
        return searchRec(node->left, key);  //left mein dhoondo
    }
    return searchRec(node->right, key); //right mai dhoondo
}

Shipment* shipmentBST::search(string key) {
    BSTNode* found=searchRec(root, key);  //root se search shuru karo
    return found ? found->data : nullptr;
}

BSTNode* shipmentBST::findMinNode(BSTNode* node) {
    BSTNode* current=node;             //current node se shuru karo
    while (current && current->left) { //jab tak left child hai
        current=current->left;         //left mein jate raho
    }
    return current;                    //sabse chota node return karo
}

BSTNode* shipmentBST::removeRec(BSTNode* node, string key) {
    if (!node) {
        return node; //node nahi mila
    }

    if (key < node->data->getID()) {
        node->left = removeRec(node->left, key);    //left mein dhoondo
    } else if (key > node->data->getID()) {
        node->right = removeRec(node->right, key);  //right mein dhoondo
    } else {
        //node mil gaya ab delete karna hai

        //Case 1: No left child
        if (!node->left) {
            BSTNode* temp = node->right;
            node->left = node->right = nullptr;  //connections tod do
            delete node;                         //node delete karo
            return temp;                         //right child ko return karo
        } 
        //Case 2: No right child
        else if (!node->right) {
            BSTNode* temp = node->left;
            node->left = node->right = nullptr;
            delete node;
            return temp;                         //left child ko return karo
        } 
        //Case 3: Two children 
        else {
            //step 1: find the inorder successor (minimum in right subtree)
            BSTNode* succ = findMinNode(node->right);

            //step 2: copy successor's data
            Shipment* succData = succ->data;
            string succID = succData->getID();

            //step 3: current node ke data ko successor se replace karo
            delete node->data;    //purana data delete
            node->data = succData; //naya data (successor ka) daalo
            
            //step 4: successor ka data pointer null karo
            succ->data = nullptr;  
            
            //step 5: Successor node ko entirely delete karo
            node->right = removeRec(node->right, succID);
        }

    }
    return node;
}

void shipmentBST::remove(string key) {
    root = removeRec(root, key);
}

void shipmentBST::inorderRec(BSTNode* node, SmartArray<Shipment*>& arr) {
    if (!node) { return; }          //agar node nahi hai, wapas aao
    inorderRec(node->left, arr);    //pehle left sub-tree visit krroo
    if (node->data) {
        arr.push(node->data);       //current node ka data array mein daalo
    }
    inorderRec(node->right, arr);   //phir right subtree visit karo
}

SmartArray<Shipment*>* shipmentBST::inorderTraversal() {
    SmartArray<Shipment*>* result = new SmartArray<Shipment*>();  //new array banao
    inorderRec(root, *result);  //root se shuru karke data collect karo
    return result;              //array return karo
}

bool shipmentBST::isEmpty() {
    return (root==nullptr);
}

int shipmentBST::getHeightRec(BSTNode* node) {
    if (!node) { return -1; }                   
    int leftH = getHeightRec(node->left);     
    int rightH = getHeightRec(node->right);   
    return 1 + (leftH > rightH ? leftH : rightH);        
}

int shipmentBST::getHeight() {
    return getHeightRec(root); 
}

int shipmentBST::getNodeCountRec(BSTNode* node) {
    if (!node) {
        return 0;
    }
    return 1 + getNodeCountRec(node->left) + getNodeCountRec(node->right);
}

int shipmentBST::getNodeCount() {
    return getNodeCountRec(root);  
}

Shipment* shipmentBST::findMin() {
    BSTNode* n = findMinNode(root);  //root se sabse chota node dhoondo
    return (n ? n->data : nullptr);    //agar node mila tou uska data, warna null
}


Shipment* shipmentBST::findMax() {
    BSTNode* current=root;        //start with root
    if (!current) {
        return nullptr;           //agar tree khaali hai
     }

    while (current && current->right) {      //jab tak right child hai
        current=current->right;   // right mein jate raho
    }

    return current->data;  //sbse right wala node ka data
}

void shipmentBST::collectPriorityShipments(BSTNode* node, SmartArray<Shipment*>& arr) {
    if (!node) { return; } //node is null
    //traversal is inorder
    collectPriorityShipments(node->left, arr); //collect in left
    if(node->data && node->data->isPriority()) { //if it is a priority shipment
        arr.push(node->data); //place it in array
    }
    collectPriorityShipments(node->right, arr); //collect in right
}

int shipmentBST::countPriorityShipments() {
    SmartArray<Shipment*> result;            //make a temporary array 
    collectPriorityShipments(root, result);  //collect priority shipments  
    return result.getSize();                 //array size = count
}

SmartArray<Shipment*>* shipmentBST::getPriorityShipments() {
    SmartArray<Shipment*>* result=new SmartArray<Shipment*>();  //new array
    collectPriorityShipments(root, *result);  //collect data
    return result;                            //return data
}

void shipmentBST::collectDelayedShipments(BSTNode* node, SmartArray<Shipment*>& arr) {
    if (!node) { return; }                             //node null hai
    collectDelayedShipments(node->left, arr);          //left mein check karo
    if (node->data) {                                  //agar data hai
        string st=node->data->getStatus();           //status dekho
        if (st=="DELAYED")     //agar delayed 
            arr.push(node->data);                      //array mein daalo
    }
    collectDelayedShipments(node->right, arr);         //right mein check karo
}

SmartArray<Shipment*>* shipmentBST::getDelayedShipments() {
    SmartArray<Shipment*>* result=new SmartArray<Shipment*>();  //new array
    collectDelayedShipments(root, *result);  //collect delayed shipments 
    return result;                           //return array 
}


