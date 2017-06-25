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
		size_t qnt;
		size_t price;
		OrderLine(Product product, size_t qnt, size_t price);
	};
	map<size_t, OrderLine> m_ProductsInOrder;  // stores productCode as a key, the product itself and its quantity added to the order
	tm createdAt;
	size_t totalWeight;
	size_t totalCentAmount;
	size_t paidCentAmount;
	bool isSubmitted; // if the order is submitted, no further changes to m_ProductsInOrder are allowed as it's prepared for payment
	bool isClosed;    // if the order is closed, it's submitted and fully paid
	tm closedAt;
public:
	Order();  // constructor
	
	/* Checks if the product quantity in the stock is sufficient and then
	 * a) adds a new product to the order 
	 * b) or changes its quantity if it's already in the order */
	bool AddProduct(size_t productCode, size_t qntToAdd);

	/* Checks if the product is in the order with the quantity > 0 */
	bool IsInOrder(size_t productCode); 

	/* Returns the current number of different products in the order */
	size_t GetNumberOfProducts();  

	size_t GetTotalAmount();
	size_t GetPaidAmount();
	size_t GetAmountDue();
	size_t GetTotalWeight();

	/* Prepares order for payment: checks once again and desreases products' available quantity in stock */
	bool SubmitOrder();

	bool IsSubmitted();       // returns true if order is prepared for payment and product contents of it is locked
	bool Pay(size_t payment); // accepts full or partial payment for the order *100 (including cents/copeiks), returns true if successful
	bool CloseOrder();        // closes the order (checks out), returns true if successful
	bool IsClosed();
	string GetCreationTime(); // returns date and time when the order was created in a form of a string
	string GetClosedTime();       // returns date and time when the order was closed in a form of a string
};