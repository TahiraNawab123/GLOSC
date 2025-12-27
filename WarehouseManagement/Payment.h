#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
using namespace std;

class Payment {
public: // process order payment
    void processPayment(int orderId, int amount);
};

#endif