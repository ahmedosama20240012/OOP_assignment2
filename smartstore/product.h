#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

//  Custom Exceptions
class NegativePriceException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Price cannot be negative!";
    }
};

class NegativeQuantityException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Quantity cannot be negative!";
    }
};

class InsufficientStockException : public exception {
    int requested, available;
public:
    InsufficientStockException(int req, int avail)
        : requested(req), available(avail) {}
    const char* what() const noexcept override {
        return "Error: Insufficient stock for purchase!";
    }
    int getRequested()  const { return requested; }
    int getAvailable()  const { return available; }
};

class FileException : public exception {
    string msg;
public:
    FileException(const string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// Base Class
class Product {
private:
    static int totalProducts;

protected:
    int    productId;
    string name;
    double price;
    int    available_quantity;

public:
    Product();
    Product(int id, string name, double price, int available_quantity);
    virtual ~Product() {}

    // Getters
    double getPrice()    const;
    string getName()     const;
    int    getId()       const;
    int    getQuantity() const;

    // Static
    static void printTotalProducts();
    static int  getTotalProducts();

    // Purchase operation
    void purchase(int qty);

    // Operator overloads
    Product& operator+(int qty);          // add stock
    bool     operator==(const Product& other) const;  // compare by price
    friend ostream& operator<<(ostream& os, const Product& p);

    // Virtual
    virtual void display_details() const;
    virtual string getType() const { return "Product"; }

    // File I/O
    virtual void saveToFile(ofstream& ofs) const;

    // Friend function
    friend void more_expensive(const Product& p1, const Product& p2);
};

// Book
class Book : public Product {
private:
    string author;
    int    number_of_pages;

public:
    Book();
    Book(int id, string name, double price, int available_quantity,
         string author, int number_of_pages);

    void   display_details() const override;
    string getType()         const override { return "Book"; }
    void   saveToFile(ofstream& ofs) const override;
};

// Electronic_device
class Electronic_device : public Product {
private:
    string brand;
    int    warranty;

public:
    Electronic_device();
    Electronic_device(int id, string name, double price, int available_quantity,
                      string brand, int warranty);

    void   display_details() const override;
    string getType()         const override { return "Electronic"; }
    void   saveToFile(ofstream& ofs) const override;
};

// Office_supply
class Office_supply : public Product {
private:
    string category;
    string material;

public:
    Office_supply();
    Office_supply(int id, string name, double price, int available_quantity,
                  string category, string material);

    void   display_details() const override;
    string getType()         const override { return "OfficeSupply"; }
    void   saveToFile(ofstream& ofs) const override;
};

// Template: highest_price
template<typename T>
T highest_price(const vector<T>& P) {
    if (P.empty()) throw runtime_error("Error: Empty product list!");
    T highest = P[0];
    for (size_t i = 1; i < P.size(); i++) {
        if (P[i]->getPrice() > highest->getPrice())
            highest = P[i];
    }
    return highest;
}

// Template: swapItems─
template <typename T>
void swapItems(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// File I/O helpers
void saveAllProducts(const vector<Product*>& products, const string& filename);
void loadAndPrintProducts(const string& filename);

#endif