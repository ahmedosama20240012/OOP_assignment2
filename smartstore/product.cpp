#include "product.h"
#include <iostream>
using namespace std;

Product::Product(int id, string name, double price, int available_quantity) :
productId(id), name(name), price(price), available_quantity(available_quantity) {

}

Book::Book(int id, string name, double price, int available_quantity, string author, int number_of_pages):
Product(id, name, price, available_quantity), author(author), number_of_pages(number_of_pages) {

}

Electronic_device::Electronic_device(int id, string name, double price, int available_quantity, string brand, int warranty):
Product(id, name, price, available_quantity), brand(brand), warranty(warranty) {

}

Office_supply::Office_supply(int id, string name, double price, int available_quantity, string category, string material):
Product(id, name, price, available_quantity), category(category), material(material) {

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


