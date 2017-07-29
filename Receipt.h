#pragma once
#include <utility>
using namespace std;
#include "Order.h"
#include "Utilities.h"

class Receipt
{
private:
	Order& m_Order;

public:
	Receipt(Order& m_Order);  // constructor

	/* Returns a string with productCode, productName, unitCentPrice,
	* quantity in the order and total price of the product in the order.*/
	string OrderLineToString(Order::OrderLine orderLine);

	/* Returns a string with all products in the order with quantity > 0 :
	* One line stands for each product with productCode, productName, unitCentPrice,
	* quantity and total price of the product in the order.*/
	string GetAllProductsInOrder();

	string GetHeader();
	string GetFinancialTotals();

	// Returns full receipt, consisting of header, all products and totals
	string GetReceipt();
};
