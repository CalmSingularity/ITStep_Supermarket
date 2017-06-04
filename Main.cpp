#include <iostream>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"
#include "Stock.h"

int main() {
	Product Cucumbers(1002577, "Cucumbers", 21055, 1000, true);
	Cucumbers.SetManufacturer("OOO Greenhouse");
	Cucumbers.SetProductionDate(25, 5, 2017);
	Cucumbers.SetExpirationDate(01, 6, 2017);
	cout << "New product added:\n" << Cucumbers.GetFullDetails() << endl;
	
	Product Tomatoes(1002593, "Tomatoes", 33710, 1000, true);
	Tomatoes.SetManufacturer("OOO Greenhouse");
	Tomatoes.SetProductionDate(25, 5, 2017);
	Tomatoes.SetExpirationDate(31, 5, 2017);
	cout << "New product added:\n" << Tomatoes.GetFullDetails() << endl;

	Product CondencedMilk(1006608, "Condenced Milk", 11000, 250, false);
	CondencedMilk.SetManufacturer("IP Burenka");
	CondencedMilk.SetWeightGross(265);
	CondencedMilk.SetProductionDate(1, 4, 2017);
	CondencedMilk.SetExpirationDate(31, 3, 2018);
	CondencedMilk.SetDimensions(100, 150, 100);
	cout << "New product added:\n" << CondencedMilk.GetFullDetails() << endl;


	Stock main_stock;
	main_stock.AddProduct(Cucumbers);
	main_stock.AddProduct(CondencedMilk);
	main_stock.AddProduct(CondencedMilk);

	cout << endl;

	main_stock.ChangeQuantity(Cucumbers, 12);
	main_stock.ChangeQuantity(Tomatoes, 10);
	main_stock.AddProduct(Tomatoes);
	main_stock.ChangeQuantity(Tomatoes, 5.625);
	main_stock.ChangeQuantity(CondencedMilk, -3);
	main_stock.ChangeQuantity(CondencedMilk, 80);

	cout << endl;

	cout << main_stock.GetAllProductsInStock();

	cout << endl;

	Order test_purchase;

	if (test_purchase.IsClosed()) {
		cout << "Order is closed at " << test_purchase.GetClosedTime() << "\n";
	}

	return 0;
}

