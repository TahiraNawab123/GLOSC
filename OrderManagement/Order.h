#ifndef ORDER_H
#define ORDER_H
#include <string>
using namespace std;

// Order struct to hold order data
struct Order {
    int id;                 // unique order id
    int priority;           // priority from 0 to 100; lower= less urgent, higher = more urgent
    string deadline;      // format: YYYY-MM-DD
    int value;              // price
    int distance;           // delivery distance in km
    string customerName;    // customer name
    string description;     // short description
    int productId;          // ID of product being ordered
    int userId;             // ID of user placing the order (must match product owner)

    // default constructor
    Order() {
        id = priority = value = distance = productId = userId = 0;
        customerName = description = deadline = "";
    }

    // parametrized constructor
    Order(int _id, int _priority, const string &_deadline, int _value, int _distance,
          const string &_name, const string &_description, int _productId = 0, int _userId = 0) {
        id = _id;
        priority = _priority;
        deadline = _deadline;
        value = _value;
        distance = _distance;
        customerName = _name;
        description = _description;
        productId = _productId;
        userId = _userId;
    }
};

#endif
