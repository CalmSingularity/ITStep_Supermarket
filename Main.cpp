#include <iostream>
#include <exception>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"
#include "StockDB.h"

int main() {
	try {
		Product Cucumbers(1002577, "Cucumbers", 21055, "OOO Greenhouse", 1000, 1010);
		cout << "New product created:\n" << Cucumbers.GetFullDetails() << endl;

		Product Tomatoes(1002593, "Tomatoes", 33710, "OOO Greenhouse", 1000, 1010);
		cout << "New product created:\n" << Tomatoes.GetFullDetails() << endl;

		Product CondencedMilk(1006608, "Condenced Milk", 11000, "IP Burenka", 250, 265, 50, 100, 50);
		cout << "New product created:\n" << CondencedMilk.GetFullDetails() << endl;

		StockDB mainStockDB;
		mainStockDB.CreateStockRecord(Cucumbers, 12000);
		mainStockDB.CreateStockRecord(CondencedMilk);
		mainStockDB.CreateStockRecord(CondencedMilk);
		mainStockDB.ChangeAvailableQnt(Tomatoes.GetCode(), 10);
		mainStockDB.CreateStockRecord(Tomatoes);
		mainStockDB.ChangeAvailableQnt(Tomatoes.GetCode(), 5625);
		mainStockDB.ChangeAvailableQnt(CondencedMilk.GetCode(), -3);
		mainStockDB.ChangeAvailableQnt(CondencedMilk.GetCode(), 80);
		cout << endl;

		cout << mainStockDB.GetAllProductsInStock();
		cout << endl;

		mainStockDB.DeleteStockRecord(Cucumbers.GetCode());
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

