#include "Notification.h"
// sends msg
void Notification::sendUpdate(string customerName) {
        cout << "[Notification] Dear "
             << customerName
             << ", your order has been processed."
             << endl;
    }