#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include <iostream>
#include <fstream>
#include "../Common/AllStructures.h"

using namespace std;

// ProductCatalog uses BST from AllStructures
template <typename T>
class ProductCatalog {
private:
    BinarySearchTree<T*> bst;   // BST storing product pointers

public:
    // Constructor
    ProductCatalog() {}

    // Destructor
    ~ProductCatalog() {}

    // Add product to catalog
    void addProduct(T* item) {
        bst.insert(item);
    }

    // Search product by ID
    T* searchProduct(int id) {
        DynamicArray<T*> products = bst.inorderTraversal();

        for (int i = 0; i < products.getSize(); i++) {
            if (products.get(i)->getId() == id)
                return products.get(i);
        }
        return nullptr;
    }

    // Print all products (sorted by ID)
    void printAllProducts() {
        cout << "\n--- Product Catalog (Inorder BST Traversal) ---\n";

        DynamicArray<T*> products = bst.inorderTraversal();
        for (int i = 0; i < products.getSize(); i++) {
            products.get(i)->print();
            cout << "\n";
        }
    }

    // Export catalog to file
    void exportToFile() {
        ofstream file("catalog_export.txt");

        DynamicArray<T*> products = bst.inorderTraversal();
        for (int i = 0; i < products.getSize(); i++) {
            file << products.get(i)->getId() << " "
                 << products.get(i)->getName() << " "
                 << products.get(i)->getQuantity() << "\n";
        }

        file.close();
    }
};

#endif
