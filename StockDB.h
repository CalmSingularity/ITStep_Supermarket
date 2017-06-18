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
		double available;
		StockRecord(Product product, double quantity);
	};
	map<size_t, StockRecord> m_ProductsInStock;  // stores productCode as a key, the product itself and available quantity 

public:
	bool AddProduct(Product new_product); // adds a new product to the stock with 0 quantity
	bool IsInStock(Product product);      // checks if the product is in stock with the quantity > 0
	double GetQuantity(Product product);  // returns the available quantity of the product
	bool ChangeQuantity(Product product, double delta);  // change available quantity of product in stock by delta

	string GetProductInStock(Product product);   // returns a string with product_id, product_name, available quantity
	string GetAllProductsInStock(); // returns a string for all products available in stock with quantity > 0
						            // one line for each product with product_id, product_name, available quantity

	//bool IsAvailableEnough(Product product, double quantity); // checks if there is sufficient quantity of product in stock which is not reserved
	//size_t Reserve(Product product, double quantity); // reserves the specified quantity of product (usually prior to release from stock); returns id of the reservation or 0 if not successful
	//bool CancelReservation(size_t reservationId);     // cancels the reservation, doesn't affect the stock
	//bool ReleaseProduct(Product product, double quantity);  // releases the specified quantity of product from stock (for sale, disposal, etc.)
	//bool ReleaseReservation(size_t reserve);  // releases the specified reserve from stock (usually for sale and dispatch)

};
