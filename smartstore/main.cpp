#include <iostream>
#include <vector>
#include "product.h"
using namespace std;

// Helper to print section headers
void section(const string& title) {
    cout << "\n" << string(55, '=') << endl;
    cout << "  " << title << endl;
    cout << string(55, '=') << endl;
}

int main() {

    //  Create at least 4 products
    section("1. Creating Products (at least 4)");

    Book             b1(1, "Harry Potter",  400.0,  35, "J.K. Rowling", 450);
    Book             b2(2, "Clean Code",    500.0, 300, "Robert Martin", 600);
    Electronic_device e1(3, "Laptop",      1500.0,  10, "Dell",          2);
    Electronic_device e2(4, "Headphones",   200.0,  50, "Sony",          1);
    Office_supply    o1(5, "Stapler",        15.0, 100, "Fasteners",  "Metal");
    Office_supply    o2(6, "Notebook",       25.0, 200, "Stationery", "Paper");

    cout << "  Created 6 products successfully." << endl;

    //  base class pointers + overridden display_details
    section("2. Polymorphism & Overridden display_details()");

    vector<Product*> store;
    store.push_back(&b1);
    store.push_back(&b2);
    store.push_back(&e1);
    store.push_back(&e2);
    store.push_back(&o1);
    store.push_back(&o2);

    for (Product* p : store)
        p->display_details();

    // Static function
    section("3. Static Function: printTotalProducts()");
    Product::printTotalProducts();

    // Friend function: more_expensive
    section("4. Friend Function: more_expensive()");
    cout << "  b1 vs b2: ";    more_expensive(b1, b2);
    cout << "  e1 vs e2: ";    more_expensive(e1, e2);
    cout << "  o1 vs o2: ";    more_expensive(o1, o2);

    // Template function: highest_price
    section("5. Template Function: highest_price()");
    Product* most_expensive = highest_price(store);
    cout << "  Most expensive product: " << *most_expensive << endl;

    // Template function: swapItem
    section("6. Template Function: swapItems()");
    cout << "  Before swap:" << endl;
    cout << "    b1: " << b1 << endl;
    cout << "    b2: " << b2 << endl;
    swapItems(b1, b2);
    cout << "  After swap:" << endl;
    cout << "    b1: " << b1 << endl;
    cout << "    b2: " << b2 << endl;

    // Operator Overloading
    section("7. Operator Overloading");

    // operator+ : add stock
    cout << "  [+] Adding 20 units to e1 (Laptop)..." << endl;
    cout << "    Before: " << e1 << endl;
    e1 + 20;
    cout << "    After:  " << e1 << endl;

    // operator== : compare by price
    cout << "\n  [==] Comparing products by price:" << endl;
    cout << "    b1 == b2 ? " << (b1 == b2 ? "Yes (same price)" : "No (different prices)") << endl;
    cout << "    o1 == o2 ? " << (o1 == o2 ? "Yes (same price)" : "No (different prices)") << endl;

    // operator<< : stream output
    cout << "\n  [<<] Streaming products with operator<<:" << endl;
    for (Product* p : store)
        cout << "    " << *p << endl;

    // Purchase operation
    section("8. Purchase Operations");
    cout << "  Purchasing 5 units of Headphones (stock=" << e2.getQuantity() << "):" << endl;
    e2.purchase(5);
    cout << "  Purchasing 10 units of Stapler   (stock=" << o1.getQuantity() << "):" << endl;
    o1.purchase(10);

    // File I/O
    section("9. File I/O: Save & Read");
    const string filename = "products.txt";

    try {
        saveAllProducts(store, filename);
        loadAndPrintProducts(filename);
    }
    catch (const FileException& e) {
        cerr << "  FILE ERROR: " << e.what() << endl;
    }

    // Exception Handling
    section("10. Exception Handling");

    // Case 1: Negative price
    cout << "  [Test 1] Creating product with negative price (-50):" << endl;
    try {
        Book bad1(99, "BadBook", -50.0, 10, "Nobody", 100);
    }
    catch (const NegativePriceException& e) {
        cout << "    CAUGHT -> " << e.what() << endl;
    }

    // Case 2: Negative quantity
    cout << "\n  [Test 2] Creating product with negative quantity (-5):" << endl;
    try {
        Electronic_device bad2(98, "BadDevice", 200.0, -5, "NoName", 1);
    }
    catch (const NegativeQuantityException& e) {
        cout << "    CAUGHT -> " << e.what() << endl;
    }

    // Case 3: Purchasing more than available stock
    cout << "\n  [Test 3] Purchasing 9999 units of Laptop (stock=" << e1.getQuantity() << "):" << endl;
    try {
        e1.purchase(9999);
    }
    catch (const InsufficientStockException& e) {
        cout << "    CAUGHT -> " << e.what()
             << " (Requested: " << e.getRequested()
             << ", Available: " << e.getAvailable() << ")" << endl;
    }

    // Case 4: File error
    cout << "\n  [Test 4] Reading from a non-existent file:" << endl;
    try {
        loadAndPrintProducts("ghost_file_xyz.txt");
    }
    catch (const FileException& e) {
        cout << "    CAUGHT -> " << e.what() << endl;
    }

    section("All Tests Completed Successfully!");

    return 0;
}