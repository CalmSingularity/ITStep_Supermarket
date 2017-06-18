#include <iostream>
#include <exception>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"
#include "StockDB.h"

int main() {
	try {
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


		StockDB mainStockDB;
		mainStockDB.AddProduct(Cucumbers);
		mainStockDB.AddProduct(CondencedMilk);
		mainStockDB.AddProduct(CondencedMilk);
		mainStockDB.ChangeQuantity(Cucumbers, 12);
		cout << mainStockDB.GetQuantity(Tomatoes) << endl;
		mainStockDB.ChangeQuantity(Tomatoes, 10);
		mainStockDB.AddProduct(Tomatoes);
		mainStockDB.ChangeQuantity(Tomatoes, 5.625);
		mainStockDB.ChangeQuantity(CondencedMilk, -3);
		mainStockDB.ChangeQuantity(CondencedMilk, 80);

		cout << endl;

		cout << mainStockDB.GetAllProductsInStock();

		cout << endl;

		Order testPurchase;

		if (testPurchase.IsClosed()) {
			cout << "Order is closed at " << testPurchase.GetClosedTime() << "\n";
		}
	}
	catch (exception &exception) {
		cerr << "Standard exception: " << exception.what() << '\n';
	}
	
	return 0;
}

