#ifndef DOCUMENT_GENERATOR_H
#define DOCUMENT_GENERATOR_H
#include <string>
#include "Order.h"
using namespace std;

// Document generator singleton
// handles file based order documentation

class DocumentGenerator {
private:
    // singleton instance which means only one object is allowed
    static DocumentGenerator* instance;

    // private constructor to prevent direct object creation
    DocumentGenerator();
public:
    //  singleton function
    // return the single instance of DocumentGenerator
    static DocumentGenerator* getInstance();

    // file handling functions
    // append an order record to a file
    void appendOrderToFile(const Order& order, const string& filename);
};

#endif
