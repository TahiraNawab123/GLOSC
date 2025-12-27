#include "Payment.h"
#include<iostream>
using namespace std;
// Processes payment for given order
 void Payment::processPayment(int orderId, int amount) {
        cout << "Payment processed for Order ID "
             << orderId << ", Amount: " << amount << endl;
    }