#include "product.h"
#include <iostream>
using namespace std;

int Product::totalProducts = 0;
Product::Product(){}
Product::Product(int id, string name, double price, int available_quantity) :
productId(id), name(name), price(price), available_quantity(available_quantity) {

    totalProducts++;
}
double Product::getPrice() {
    return price;
}

Book::Book(){}
Book::Book(int id, string name, double price, int available_quantity, string author, int number_of_pages):
Product(id, name, price, available_quantity), author(author), number_of_pages(number_of_pages) {

}

Electronic_device::Electronic_device(){}
Electronic_device::Electronic_device(int id, string name, double price, int available_quantity, string brand, int warranty):
Product(id, name, price, available_quantity), brand(brand), warranty(warranty) {

}

Office_supply::Office_supply(){}
Office_supply::Office_supply(int id, string name, double price, int available_quantity, string category, string material):
Product(id, name, price, available_quantity), category(category), material(material) {

}

void Product::printTotalProducts() {

    cout << " Total Products in Store: " << totalProducts <<endl;

}

void Product::display_details() {
    cout << "Product's ID: " << productId << endl;
    cout << "Product's Name: " << name << endl;
    cout << "Product's Price: " << price << endl;
    cout << "Product's Available Quantity: " << available_quantity << endl;
}

void Book::display_details() {
    Product::display_details();

    cout << "Author: " << author << endl;
    cout << "Number of Pages: " << number_of_pages << endl;
}

void Electronic_device::display_details() {
    Product::display_details();
    cout << "Brand: " << brand << endl;
    cout << "Warranty: " << warranty << endl;
}

void Office_supply::display_details() {
    Product::display_details();
    cout << "category: " << category << endl;
    cout << "material: " << material << endl;
}

void more_expensive(Product p1, Product p2) {
    if (p1.price > p2.price) {
        cout << p1.name << " is greater than " << p2.name << endl;
    }
    else {
        cout << p2.name << " is greater than " << p1.name << endl;
    }

}

