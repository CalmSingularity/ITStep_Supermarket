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
	struct OrderLine {
		Product product;
		double quantity;
		OrderLine(Product product, double quantity);
	};
	map<size_t, OrderLine> m_ProductsInOrder;  // stores productCode as a key, the product itself and its quantity in the order
	tm createdAt;
	size_t totalWeight;
	size_t totalCentAmount;
	size_t paidCentAmount;
	bool isClosed;
	tm closedAt;
public:
	Order();  // constructor
	bool AddProduct(Product product, size_t quantityToAdd);  // adds a new product or changes its quantity if it's already in the order
	bool IsInOrder(Product product); // checks if the product is in order with the quantity > 0
	size_t GetNumberOfProducts();    // returns the current number of products in the order
	size_t GetTotalAmount();
	size_t GetPaidAmount();
	size_t GetAmountDue();
	size_t GetTotalWeight();
	string GetCreationTime();     // returns date and time when the order was created in a form of a string
	bool IsClosed();
	string GetClosedTime();       // returns date and time when the order was closed in a form of a string
	bool Pay(size_t payment);     // accepts full or partial payment for the order *100 (including cents/copeiks), returns true if successful
	bool CloseOrder();            // closes the order (checks out), returns true if successful
};