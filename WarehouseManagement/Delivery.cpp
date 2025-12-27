#include "Delivery.h"
 // secdhule delivry for order
void Delivery::scheduleDelivery(int orderId, int distance) {
        cout << "[Delivery] Order ID "
             << orderId
             << " scheduled. Distance: "
             << distance << " km" << endl;
    }