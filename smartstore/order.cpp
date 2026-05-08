#include "order.h"
#include "product.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ─── regularCustomer ────────────────────────────────────────────────────────

void regularCustomer::displayInfo() {
    cout << "Customer: " << name << " (Regular)";
}

double regularCustomer::calculateDiscount(double subtotal) {
    (void)subtotal;
    return 0.0;
}

// ─── PremiumCustomer ────────────────────────────────────────────────────────

void PremiumCustomer::displayInfo() {
    cout << "Customer: " << name
         << " (Premium, " << discountRate << "% discount)";
}

double PremiumCustomer::calculateDiscount(double subtotal) {
    return subtotal * (discountRate / 100.0);
}

// ─── CashPayment ────────────────────────────────────────────────────────────

void CashPayment::pay() {
    cout << fixed << setprecision(2);
    cout << "  Payment: $" << amount << " paid by CASH\n";
}

// ─── CardPayment ────────────────────────────────────────────────────────────

CardPayment::CardPayment(int id, string card) : Payment(id), cardNumber(card) {
    if (card.length() != 16)
        throw invalid_argument("Card number must be exactly 16 digits.");
}

void CardPayment::pay() {
    cout << fixed << setprecision(2);
    cout << "  Payment: $" << amount
         << " paid by CARD (ending " << cardNumber.substr(12) << ")\n";
}

// ─── Delivery ───────────────────────────────────────────────────────────────

Delivery::Delivery(int id, string addr, double fee, string driver)
    : deliveryId(id), address(addr), driverName(driver)
{
    if (fee < 0)
        throw invalid_argument("Delivery fee cannot be negative.");
    deliveryFee = fee;
}

double Delivery::getFee() const {
    return deliveryFee;
}

void Delivery::displayDeliveryInfo() const {
    cout << fixed << setprecision(2);
    cout << "  Delivery to     : " << address     << "\n";
    cout << "  Driver          : " << driverName  << "\n";
    cout << "  Delivery Fee    : $" << deliveryFee << "\n";
}

// ─── OrderItem ──────────────────────────────────────────────────────────────

double OrderItem::calculateItemTotal() const {
    return quantity * unitPriceAtPurchase;
}

// ─── Order ──────────────────────────────────────────────────────────────────

Order::Order(int id, string date, Customer* cust)
    : orderId(id), orderDate(date), customer(cust),
      payment(nullptr), delivery(nullptr) {}

void Order::addItem(Product* p, int q) {
    p->purchase(q);
    items.push_back({ p, q, p->getPrice() });
}

void Order::setPayment(Payment* p)  { payment  = p; }
void Order::setDelivery(Delivery* d){ delivery = d; }

double Order::calculateSubtotal() const {
    double sub = 0;
    for (const auto& item : items)
        sub += item.calculateItemTotal();
    return sub;
}

double Order::calculateFinalTotal() const {
    double sub      = calculateSubtotal();
    double discount = customer->calculateDiscount(sub);
    double fee      = delivery ? delivery->getFee() : 0.0;
    return sub - discount + fee;
}

void Order::printInvoice() const {
    cout << fixed << setprecision(2);
    double sub      = calculateSubtotal();
    double discount = customer->calculateDiscount(sub);
    double fee      = delivery ? delivery->getFee() : 0.0;
    double total    = sub - discount + fee;

    cout << "\n=========================================\n";
    cout << "               INVOICE\n";
    cout << "=========================================\n";
    cout << "  Order ID        : " << orderId   << "\n";
    cout << "  Date            : " << orderDate << "\n";
    cout << "  ";
    customer->displayInfo();
    cout << "\n-----------------------------------------\n";

    for (const auto& item : items) {
        cout << "  " << item.product->getName()
             << " x" << item.quantity
             << "  @$" << item.unitPriceAtPurchase
             << "  =  $" << item.calculateItemTotal() << "\n";
    }

    cout << "-----------------------------------------\n";
    cout << "  Subtotal        : $" << sub      << "\n";
    cout << "  Discount        : $" << discount << "\n";

    if (delivery)
        delivery->displayDeliveryInfo();
    else
        cout << "  Delivery        : Pickup (no fee)\n";

    cout << "  FINAL TOTAL     : $" << total << "\n";

    if (payment) {
        payment->setAmount(total);
        payment->pay();
    }
    cout << "=========================================\n";
}

// ─── Store ──────────────────────────────────────────────────────────────────

Store::Store(string name) : storeName(name) {}

void Store::addProduct(Product* p)   { products.push_back(p);   }
void Store::addCustomer(Customer* c) { customers.push_back(c);  }
void Store::addOrder(Order* o)       { orders.push_back(o);     }

void Store::displayStoreSummary() const {
    cout << "\n========= Store Summary: " << storeName << " =========\n";
    cout << "  Total product types : " << products.size()  << "\n";
    cout << "  Total customers     : " << customers.size() << "\n";
    cout << "  Total orders placed : " << orders.size()    << "\n";
    cout << "=================================================\n";
}