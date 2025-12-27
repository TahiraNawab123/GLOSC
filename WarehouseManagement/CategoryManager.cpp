#include "CategoryManager.h"
// constructor
CategoryManager::CategoryManager(string name) {
    categoryName = name;
    categoryName[31] = '\0';
    head = nullptr;
}
// destrctor
CategoryManager::~CategoryManager() {
    CatagoryNode* cur = head;
    while (cur) {
        CatagoryNode* temp = cur;
        cur = cur->next;
        delete temp;  // product is NOT deleted (catalog owns it)
    }
}
// Add product to category list
void CategoryManager::addProduct(Product* p) {
    CatagoryNode* node = new CatagoryNode(p);
    node->next = head; // insert at front
    head = node;
}

// Print category and its products
void CategoryManager::printCategory() const {
    cout << "\n=== Category: " << categoryName << " ===\n";
    CatagoryNode* cur = head;

    if (!cur) {
        cout << "No products.\n";
        return;
    }

    while (cur) {
        cur->product->print();
        cout << "\n";
        cur = cur->next;
    }
}
// Return category name
string CategoryManager::getName() const {
    return categoryName;
}