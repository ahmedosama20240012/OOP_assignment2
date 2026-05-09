#include <iostream>
#include <vector>
#include "product.h"
#include "order.h"
using namespace std;

void separator(const string& title) {
    cout << "\n\n>>> " << title << "\n";
    cout << string(50, '-') << "\n";
}

int main() {

    separator("PART 1 - Product Management");

    separator("1. Creating Products");
    Book             b1(1, "Brain Storming",  150.0,  5, "Ahmed Osama",   800);
    Book             b2(2, "OOP Level 2",      50.0, 20, "Sultan Ali",    400);
    Electronic_device e1(3, "Laptop",         1200.0,  3, "HP",             2);
    Electronic_device e2(4, "Wireless Mouse",   35.0, 15, "Logitech",       1);
    Office_supply    o1(5, "Table",            300.0, 10, "Equipment",   "Wood");
    Office_supply    o2(6, "Notebook",          20.0, 50, "Stationery",  "Paper");
    cout << "  6 products created successfully.\n";

    separator("2. Static Function - Total Products");
    Product::printTotalProducts();

    separator("3. Polymorphism - display_details() via base pointer");
    vector<Product*> store_products = { &b1, &b2, &e1, &e2, &o1, &o2 };
    for (Product* p : store_products)
        p->display_details();

    separator("4. Friend Function - more_expensive()");
    more_expensive(b1, e1);
    more_expensive(b2, o2);
    more_expensive(e1, o1);

    separator("5. Template Function - highest_price()");
    Product* expensive = highest_price(store_products);
    cout << "  Most expensive: " << *expensive << "\n";

    separator("6. Template Function - swapItems()");
    cout << "  Before swap:\n";
    cout << "    b1: " << b1 << "\n";
    cout << "    b2: " << b2 << "\n";
    swapItems(b1, b2);
    cout << "  After swap:\n";
    cout << "    b1: " << b1 << "\n";
    cout << "    b2: " << b2 << "\n";
    swapItems(b1, b2);

    separator("7. Operator Overloading");
    cout << "  [+]  Adding 10 units to Wireless Mouse stock:\n";
    cout << "    Before: " << e2 << "\n";
    e2 + 10;
    cout << "    After : " << e2 << "\n";

    cout << "\n  [==] Compare products by price:\n";
    cout << "    b1 == b2 ? " << (b1 == b2 ? "YES (same price)" : "NO (different price)") << "\n";
    cout << "    e1 == o1 ? " << (e1 == o1 ? "YES (same price)" : "NO (different price)") << "\n";

    cout << "\n  [<<] Stream all products:\n";
    for (Product* p : store_products)
        cout << "    " << *p << "\n";

    separator("8. File I/O - Save and Load");
    try {
        saveAllProducts(store_products, "products.txt");
        loadAndPrintProducts("products.txt");
    }
    catch (const FileException& e) {
        cout << "  FILE ERROR: " << e.what() << "\n";
    }

    separator("9. Exception Handling");

    cout << "  [Case 1] Negative price:\n";
    try {
        Book bad(999, "Bad Book", -100.0, 5, "Nobody", 10);
    }
    catch (const NegativePriceException& e) {
        cout << "  CAUGHT -> " << e.what() << "\n";
    }

    cout << "\n  [Case 2] Negative quantity:\n";
    try {
        Electronic_device bad(998, "Bad Device", 200.0, -3, "Brand", 1);
    }
    catch (const NegativeQuantityException& e) {
        cout << "  CAUGHT -> " << e.what() << "\n";
    }

    cout << "\n  [Case 3] Purchase more than available stock:\n";
    try {
        b1.purchase(9999);
    }
    catch (const InsufficientStockException& e) {
        cout << "  CAUGHT -> " << e.what()
             << " (Requested: " << e.getRequested()
             << ", Available: " << e.getAvailable() << ")\n";
    }

    cout << "\n  [Case 4] Read from non-existent file:\n";
    try {
        loadAndPrintProducts("missing_file.txt");
    }
    catch (const FileException& e) {
        cout << "  CAUGHT -> " << e.what() << "\n";
    }

    separator("PART 2 - Orders, Payments & Delivery");

    separator("10. Creating Customers");
    regularCustomer cust1(1, "Ahmed",    "01123311123");
    PremiumCustomer cust2(2, "Abdullah", "01023234110", 15.0);
    cout << "  Regular customer and Premium customer created.\n";

    separator("11. Order 1 - Regular Customer, Cash, with Delivery");
    Order ord1(5001, "2026-05-04", &cust1);
    ord1.addItem(&b1, 1);
    ord1.addItem(&o1, 2);

    CashPayment pay1(9001);
    Delivery    del1(7001, "Cairo, Street 10", 10.0, "Ali");

    ord1.setPayment(&pay1);
    ord1.setDelivery(&del1);
    ord1.printInvoice();

    separator("12. Order 2 - Premium Customer, Card, Pickup (no delivery)");
    Order ord2(5002, "2026-05-04", &cust2);
    ord2.addItem(&e1, 1);
    ord2.addItem(&b2, 3);

    CardPayment pay2(9002, "1234123412341234");
    ord2.setPayment(&pay2);
    ord2.printInvoice();

    separator("13. Exception - Insufficient Stock in Order");
    try {
        ord2.addItem(&e1, 10);
    }
    catch (const InsufficientStockException& e) {
        cout << "  CAUGHT -> " << e.what()
             << " (Requested: " << e.getRequested()
             << ", Available: " << e.getAvailable() << ")\n";
    }

    separator("14. Exception - Invalid Card Number");
    try {
        CardPayment badCard(9003, "123");
    }
    catch (const invalid_argument& e) {
        cout << "  CAUGHT -> " << e.what() << "\n";
    }

    separator("15. Exception - Negative Delivery Fee");
    try {
        Delivery badDel(7002, "Unknown", -5.0, "Nobody");
    }
    catch (const invalid_argument& e) {
        cout << "  CAUGHT -> " << e.what() << "\n";
    }

    separator("16. Store Summary");
    Store smartStore("Smart Store Cairo");
    for (Product* p : store_products) smartStore.addProduct(p);
    smartStore.addCustomer(&cust1);
    smartStore.addCustomer(&cust2);
    smartStore.addOrder(&ord1);
    smartStore.addOrder(&ord2);
    smartStore.displayStoreSummary();
    return 0;
}
