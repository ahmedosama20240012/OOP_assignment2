#pragma once
#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include <iomanip>

class Customer {
protected:
    int    customerId;
    string name;
    string phone;
public:
    Customer(int id, string n, string p) : customerId(id), name(n), phone(p) {}
    virtual void   displayInfo()                      = 0;
    virtual double calculateDiscount(double subtotal) = 0;
    virtual ~Customer() {}
};

class regularCustomer : public Customer {
public:
    regularCustomer(int id, string n, string p) : Customer(id, n, p) {}
    void   displayInfo()                      override;
    double calculateDiscount(double subtotal) override;
};

class PremiumCustomer : public Customer {
private:
    double discountRate;
public:
    PremiumCustomer(int id, string n, string p, double rate)
        : Customer(id, n, p), discountRate(rate) {}
    void   displayInfo()                      override;
    double calculateDiscount(double subtotal) override;
};

class Payment {
protected:
    int    paymentId;
    double amount;
public:
    Payment(int id) : paymentId(id), amount(0) {}
    void setAmount(double a) { amount = a; }
    virtual void pay()  = 0;
    virtual ~Payment() {}
};

class CashPayment : public Payment {
public:
    CashPayment(int id) : Payment(id) {}
    void pay() override;
};

class CardPayment : public Payment {
private:
    string cardNumber;
public:
    CardPayment(int id, string card);
    void pay() override;
};

class Delivery {
private:
    int    deliveryId;
    string address;
    double deliveryFee;
    string driverName;
public:
    Delivery(int id, string addr, double fee, string driver);
    double getFee()              const;
    void   displayDeliveryInfo() const;
};

struct OrderItem {
    Product* product;
    int      quantity;
    double   unitPriceAtPurchase;
    double   calculateItemTotal() const;
};

class Order {
private:
    int               orderId;
    string            orderDate;
    Customer*         customer;
    Payment*          payment;
    Delivery*         delivery;
    vector<OrderItem> items;
public:
    Order(int id, string date, Customer* cust);
    void   addItem(Product* p, int q);
    void   setPayment(Payment* p);
    void   setDelivery(Delivery* d);
    double calculateSubtotal()    const;
    double calculateFinalTotal()  const;
    void   printInvoice()         const;
};

class Store {
private:
    string            storeName;
    vector<Product*>  products;
    vector<Customer*> customers;
    vector<Order*>    orders;
public:
    Store(string name);
    void addProduct(Product* p);
    void addCustomer(Customer* c);
    void addOrder(Order* o);
    void displayStoreSummary() const;
};

#endif