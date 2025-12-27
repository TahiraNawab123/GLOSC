#include "DocumentGenerator.h"
#include <fstream>
#include <iostream>
using namespace std;

//  static member initialization
// initialize singleton instance to null
DocumentGenerator* DocumentGenerator::instance = nullptr;

// private constructor of singleton pattern
DocumentGenerator::DocumentGenerator() {
    // means nothing to initialize
}
// singleton function
// returns the single instance of DocumentGenerator
DocumentGenerator* DocumentGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new DocumentGenerator();
    }
    return instance;
}

// file handling functions
// append the details of an order to the given file
void DocumentGenerator::appendOrderToFile(const Order& order, const string& filename) {
    // open file in append mode so previous records are preserved
    ofstream fout(filename.c_str(), ios::app);

    if (!fout) {
        cout << "Error! Could not open the order file." << endl;
        return;
    }
    fout << "=============================" << endl;
    fout << "Order ID      : " << order.id << endl;
    fout << "Customer Name : " << order.customerName << endl;
    fout << "Priority      : " << order.priority << endl;
    fout << "Deadline      : " << order.deadline << endl;
    fout << "Value         : " << order.value << endl;
    fout << "Distance (km) : " << order.distance << endl;
    fout << "Description   : " << order.description << endl;
    fout << "=============================" << endl;
    // close the file
    fout.close();
}
