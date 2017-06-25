#pragma once
#include <map>
#include <utility>
using namespace std;
#include "Product.h"
#include "Utilities.h"

class StockDB 
{
private:
	struct StockRecord {
		Product product;
		size_t availableQnt;
		StockRecord(Product product, size_t availableQnt);
	};
	map<size_t, StockRecord> m_ProductsInStock;  // stores productCode as a key, the product itself and available quantity in units or gramms

public:

	/* Adds a new product to the stock with quantity. Returns true if successful. 
	 * If the product with such productCode already extists in the stock, does nothing and returns false.*/
	bool CreateStockRecord(Product product, size_t availableQnt = 0);
	
	/* Checks if the product is in stock */
	bool IsInStock(size_t productCode);

	/* Looks for StockRecord with productCode in the stock and returns it fi successful.
	 * If productCode is not found (product is not in stock), returns StockRecord with dummyProduct where ProductCode == 0 and quantity == 0. */
	StockRecord ReadStockRecord(size_t productCode);

	/* Returns the available quantity of the product or 0 if it's not in stock */
	size_t GetAvailableQnt(size_t productCode); 

	/* Updates StockRecord by changing available quantity of product in the stock by delta. Returns true if successful. */
	bool ChangeAvailableQnt(size_t productCode, long long delta);

	/* Looks for StockRecord with productCode in the stock and deletes it. Returns true if successful. */
	bool DeleteStockRecord(size_t productCode);

	//bool UpdateStockRecord();

	/* Returns a string with productCode, productName and available quantity */
	string GetProductInStock(size_t productCode);

	/* Returns a string with all products available in stock with quantity > 0 :
	 * One line stands for each product with productCode, productName, available quantity. */
	string GetAllProductsInStock(); 
};
