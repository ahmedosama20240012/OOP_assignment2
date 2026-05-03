#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
using namespace std;

class Product {
private:
    int productId;
    string name;
    double price;
    int available_quantity;

public:
    Product();
    Product(int id, string name, double price, int available_quantity);
    virtual void display_details();

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

#endif //PRODUCT_H
