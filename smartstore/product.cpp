#include "product.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int Product::totalProducts = 0;

Product::Product() : productId(0), name(""), price(0.0), available_quantity(0) {}

Product::Product(int id, string name, double price, int available_quantity)
    : productId(id), name(name), price(price), available_quantity(available_quantity)
{
    if (price < 0)               throw NegativePriceException();
    if (available_quantity < 0)  throw NegativeQuantityException();
    totalProducts++;
}

double Product::getPrice()    const { return price; }
string Product::getName()     const { return name; }
int    Product::getId()       const { return productId; }
int    Product::getQuantity() const { return available_quantity; }

void Product::printTotalProducts() {
    cout << "\n Total Products in Store: " << totalProducts << "\n";
}

int Product::getTotalProducts() { return totalProducts; }

void Product::purchase(int qty) {
    if (qty < 0)                  throw NegativeQuantityException();
    if (qty > available_quantity) throw InsufficientStockException(qty, available_quantity);
    available_quantity -= qty;
    cout << "  Purchased " << qty << " unit(s) of \"" << name
         << "\". Remaining stock: " << available_quantity << "\n";
}

Product Product::operator+(int qty) {
    if (qty < 0) throw NegativeQuantityException();
    available_quantity += qty;
    return *this;
}

bool Product::operator==(const Product& other) const {
    return price == other.price;
}

ostream& operator<<(ostream& os, const Product& p) {
    os << fixed << setprecision(2);
    os << "[" << p.getType() << "] ID=" << p.productId
       << " | Name: " << p.name
       << " | Price: $" << p.price
       << " | Qty: " << p.available_quantity;
    return os;
}

void Product::display_details() const {
    cout << fixed << setprecision(2);
    cout << "\n";
    cout << "  Product ID       : " << productId          << "\n";
    cout << "  Name             : " << name               << "\n";
    cout << "  Price            : $" << price             << "\n";
    cout << "  Available Stock  : " << available_quantity << "\n";
}

void Product::saveToFile(ofstream& ofs) const {
    ofs << getType()            << "\n"
        << productId            << "\n"
        << name                 << "\n"
        << price                << "\n"
        << available_quantity   << "\n";
}

void more_expensive(const Product& p1, const Product& p2) {
    cout << fixed << setprecision(2);
    if (p1.price > p2.price)
        cout << "  \"" << p1.name << "\" ($" << p1.price
             << ") is more expensive than \"" << p2.name << "\" ($" << p2.price << ")\n";
    else if (p2.price > p1.price)
        cout << "  \"" << p2.name << "\" ($" << p2.price
             << ") is more expensive than \"" << p1.name << "\" ($" << p1.price << ")\n";
    else
        cout << "  \"" << p1.name << "\" and \"" << p2.name << "\" have the same price.\n";
}

Book::Book() : author(""), number_of_pages(0) {}

Book::Book(int id, string name, double price, int available_quantity,
           string author, int number_of_pages)
    : Product(id, name, price, available_quantity),
      author(author), number_of_pages(number_of_pages) {}

void Book::display_details() const {
    Product::display_details();
    cout << "  Author           : " << author          << "\n";
    cout << "  Number of Pages  : " << number_of_pages << "\n";
}

void Book::saveToFile(ofstream& ofs) const {
    Product::saveToFile(ofs);
    ofs << author << "\n" << number_of_pages << "\n";
}

Electronic_device::Electronic_device() : brand(""), warranty(0) {}

Electronic_device::Electronic_device(int id, string name, double price,
    int available_quantity, string brand, int warranty)
    : Product(id, name, price, available_quantity), brand(brand), warranty(warranty) {}

void Electronic_device::display_details() const {
    Product::display_details();
    cout << "  Brand            : " << brand   << "\n";
    cout << "  Warranty         : " << warranty << " year(s)\n";
}

void Electronic_device::saveToFile(ofstream& ofs) const {
    Product::saveToFile(ofs);
    ofs << brand << "\n" << warranty << "\n";
}

Office_supply::Office_supply() : category(""), material("") {}

Office_supply::Office_supply(int id, string name, double price,
    int available_quantity, string category, string material)
    : Product(id, name, price, available_quantity), category(category), material(material) {}

void Office_supply::display_details() const {
    Product::display_details();
    cout << "  Category         : " << category << "\n";
    cout << "  Material         : " << material  << "\n";
}

void Office_supply::saveToFile(ofstream& ofs) const {
    Product::saveToFile(ofs);
    ofs << category << "\n" << material << "\n";
}

void saveAllProducts(const vector<Product*>& products, const string& filename) {
    ofstream ofs(filename);
    if (!ofs.is_open())
        throw FileException("Error: Cannot open file \"" + filename + "\" for writing!");
    ofs << products.size() << "\n";
    for (const auto* p : products)
        p->saveToFile(ofs);
    ofs.close();
    cout << "  Saved " << products.size() << " product(s) to \"" << filename << "\"\n";
}

void loadAndPrintProducts(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open())
        throw FileException("Error: Cannot open file \"" + filename + "\" for reading!");

    int count;
    ifs >> count;
    ifs.ignore();

    cout << "\n  --- Products loaded from \"" << filename << "\" ---\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < count; i++) {
        string type;
        getline(ifs, type);
        int id, qty;
        string name;
        double price;
        ifs >> id; ifs.ignore();
        getline(ifs, name);
        ifs >> price; ifs.ignore();
        ifs >> qty;   ifs.ignore();

        if (type == "Book") {
            string author;
            int pages;
            getline(ifs, author);
            ifs >> pages; ifs.ignore();
            cout << "  Book        : " << name << " | Author: " << author
                 << " | Pages: " << pages << " | Price: $" << price << " | Qty: " << qty << "\n";
        }
        else if (type == "Electronic") {
            string brand;
            int warranty;
            getline(ifs, brand);
            ifs >> warranty; ifs.ignore();
            cout << "  Electronic  : " << name << " | Brand: " << brand
                 << " | Warranty: " << warranty << "yr | Price: $" << price << " | Qty: " << qty << "\n";
        }
        else if (type == "OfficeSupply") {
            string category, material;
            getline(ifs, category);
            getline(ifs, material);
            cout << "  OfficeSupply: " << name << " | Cat: " << category
                 << " | Material: " << material << " | Price: $" << price << " | Qty: " << qty << "\n";
        }
    }
    ifs.close();
}
