#pragma once
#include <vector>
using namespace std;
#include "Product.h"

class Stock 
{
private:
	struct StockPosition {
		Product product;
		double quantity;
	};
	struct Reservation {
		size_t id;
		Product product;
		double quantity;
	};
	vector<StockPosition> productsInStock;
	vector<Reservation> reservations;

public:
	bool add(Product product, double quantity);  // adds quantity of product to stock; adds the product to stock if necessary
	bool isInStock(Product product);  // checks if the product is in stock with the quantity > 0
	bool isAvailableEnough(Product product, double quantity);  // checks if there is sufficient quantity of product in stock
	size_t reserve(Product product, double quantity); // reserves the specified quantity of product (usually prior to release from stock); returns id of the reservation or 0 if not successful
	bool cancelReservation(size_t reservation_id); // cancels the reservation, doesn't affect the stock
	bool releaseProduct(Product product, double quantity);	// releases the specified quantity of product from stock (for sale, disposal, etc.)
	bool releaseReservation(size_t reserve); // releases the specified reserve from stock (usually for sale and dispatch)

};
