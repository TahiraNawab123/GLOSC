#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
using namespace std;

class Product {
protected:
    int id;  // unique product ID
    string name;  // product name
    int quantity;   // available quantity
    int userId;     // ID of user who created/owns this product

public:
    Product(int pid = 0, string pname = "", int qty = 0, int uid = 0);
    // constructor
    virtual ~Product();   // virtual destructor
    // getters
    int getId() const;
    string getName() const;
    int getQuantity() const;
    int getUserId() const;  // Get user ID who owns this product
    void setQuantity(int q);
    void setUserId(int uid);  // Set user ID for product ownership

    // Product type 
    virtual int getType() const = 0;   // 1=Perishable, 2=Durable, 3=Fragile

    // Expiry info (only for perishables)
    virtual int getExpiry() const { return -1; }
    virtual bool isPerishable() const { return false; }

    // Print product details
    virtual void print() const;
};

#endif
