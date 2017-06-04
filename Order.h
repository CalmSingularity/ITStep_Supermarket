#pragma once
#include <ctime>
#include <map>
#include <utility>
using namespace std;
#include <time.h>
#include "Product.h"

class Order 
{
private:
	map<size_t, pair<Product, double>> m_ProductsInOrder;  // stores product_id as a key and pair of product itself and its ordered quantity
	tm created_at;
	size_t total_weight;
	size_t total_amount;
	size_t paid_amount;
	bool is_closed;
	tm closed_at;
public:
	Order();  // constructor
	size_t GetNumberOfProducts();  // returns the current number of products in the order
	size_t getTotalAmount();
	size_t getPaidAmount();
	size_t getAmountDue();
	size_t getTotalWeight();
	string GetCreationTime();     // returns date and time when the order was created in a form of a string
	bool IsClosed();
	string GetClosedTime();       // returns date and time when the order was closed in a form of a string
	bool addProduct(Product product, size_t quantity);  // adds a new product, returns true if successful
	bool pay(size_t payment);     // accepts full or partial payment for the order *100 (including cents/copeiks), returns true if successful
	bool closeOrder();            // closes the order (checks out), returns true if successful
};