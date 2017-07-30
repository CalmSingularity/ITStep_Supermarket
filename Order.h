#pragma once
#include <ctime>
#include <map>
#include <utility>
using namespace std;
#include <time.h>
#include "Product.h"
#include "StockDB.h"
#include "Utilities.h"


class Order 
{

private:

	struct OrderLine  // one line in the order
	{
		Product product;
		long long qnt;  // quantity added to the order
		long long unitCentPrice;
		OrderLine(Product product, long long qnt, long long unitCentPrice);  // constructor
	};


	/* The following map stores productCode as a map key. No duplicates allowed.
	 * OrderLine as a map value stores the product itself (Product object), 
	 * its quantity added to the order and its unit price. */
	map<size_t, OrderLine> m_ProductsInOrder;
	
	StockDB& m_Stock;    // which stock database the order is connected to

	long long totalCentAmount;   // total price of all products in the order
	long long totalGrossWeight;  // total gross weight of the order
	long long paidCentAmount;
	bool isSubmitted;       // if the order is submitted, no further changes to m_ProductsInOrder are allowed as it's prepared for payment
	bool isClosed;          // if the order is closed, it's submitted and fully paid
	tm createdAt;
	tm submittedAt;
	tm closedAt;

public:

	Order(StockDB& m_Stock);  // constructor
	
	/* Checks if the product quantity in the stock is sufficient and then
	 * a) adds a new product to the order, 
	 * b) or changes its quantity if it's already in the order. 
	 * Does not change available quantity in the stock.*/
	bool AddProduct(size_t productCode, int qntToAdd);

	/* Removes qntToRemove units of the product from the order.
	 * If the product is not in the order or the quantity in the order < qntToRemove,
	 * does nothing and returns false. */
	bool RemoveProduct(size_t productCode, int qntToRemove);

	/* Checks if the product is in the order with the quantity > 0 */
	bool IsInOrder(size_t productCode); 

	/* Looks for OrderLine with productCode in the order and returns it if successful.
	* If productCode is not found (product is not in the order), returns OrderLine with dummyProduct
	* where quantity == 0 and unitPrice == 0. */
	OrderLine ReadOrderLine(size_t productCode);

	/* Looks for OrderLine with productCode in the order and deletes it. Returns true if successful. */
	bool DeleteOrderLine(size_t productCode);

	/* Returns the current number of different products in the order */
	long long GetNumberOfProducts();  

	long long GetTotalAmount();
	long long GetPaidAmount();
	long long GetAmountDue();
	long long GetTotalGrossWeight();

	/* Prepares order for payment: 
	 * Checks once again if the quantity of each product in the order is sufficient in the stock.
	 * If yes, desreases products' available quantity in the stock, submits the order and returns true.
	 * If not, makes no change and returns false. */
	bool SubmitOrder();

	/* Returns true if the order is prepared for payment 
	 * and product contents of it is locked (no further changes to m_ProductsInOrder are allowed) */
	bool IsSubmitted();

	/* Accepts full or partial payment for the order.
	 * Returns true if successful.
	 * paymentAmount includes cents/copeiks. */
	bool Pay(long long paymentAmount);

	/* Returns true if the order is fully paid */
	bool IsPaid();

	/* If the order IsSubmitted and IsPaid, closes the order and returns true if successful */
	bool CloseOrder();
	
	bool IsClosed();

	/* Returns date and time when the order was created in a form of a string */
	tm GetCreationTime();

	/* Returns date and time when the order was submitted in a form of a string */
	tm GetSubmittedTime(); 

	/* Returns date and time when the order was closed in a form of a string */
	tm GetClosedTime();

	friend class Receipt;
};