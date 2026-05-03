#include <iostream>
#include "product.h"
using namespace std;


int main() {

    Book b1(1,"'intro to datascience'", 400.75, 35, "Harry", 450  ),
    b2(2,"'cs course'", 500, 300, "Ahmed",600);
    // b1.display_details();
    // Product::printTotalProducts();
    // more_expensive(b1,b2);

    // vector<Product*> v1;
    // v1.push_back(&b1);
    // v1.push_back(&b2);
    // Product* x = highest_price(v1);
    // cout << x->getPrice() << endl;

    // swapItems(b1,b2);
    // b2.display_details();
    return 0;
}

