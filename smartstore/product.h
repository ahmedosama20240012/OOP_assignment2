#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Product {
private:
    static int totalProducts;
    int productId;
    string name;
    double price;
    int available_quantity;

public:
    Product();
    Product(int id, string name, double price, int available_quantity);
    double getPrice();
    static void printTotalProducts();
    virtual void display_details();
    friend void more_expensive(Product p1, Product p2);

};

class Book : public Product {
private:
    string author;
    int number_of_pages;

    public:
    Book();
    Book(int id, string name, double price, int available_quantity, string author, int number_of_pages);
    void display_details() override;

};

class Electronic_device : public Product {
private:
    string brand;
    int warranty;

    public:
    Electronic_device();
    Electronic_device(int id, string name, double price, int available_quantity, string brand, int warranty);
    void display_details() override;

};

class Office_supply : public Product {
private:
    string category;
    string material;

    public:
    Office_supply();
    Office_supply(int id, string name, double price, int available_quantity, string category, string material);
    void display_details() override;

};

template<typename T>
T highest_price(const vector<T>& P) {

    T highest_price = P[0];
    for (int i = 1; i < P.size(); i++) {
        if (P[i]->getPrice() > highest_price->getPrice()) {
            highest_price = P[i];
        }
    }
    return highest_price;

}

template <typename T>
void swapItems(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


#endif //PRODUCT_H
