#include <iostream>
#include <exception>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"
#include "StockDB.h"

int main() 
{
	try 
	{
		// Create some products:
		Product Cucumbers(1002577, "Cucumbers", 21055, "OOO Greenhouse", 1000, 1010);
		cout << "New product created:\n" << Cucumbers.GetFullDetails() << endl;

		Product Tomatoes(1002593, "Tomatoes", 33710, "OOO Greenhouse", 1000, 1010);
		cout << "New product created:\n" << Tomatoes.GetFullDetails() << endl;

		Product CondencedMilk(1006608, "Condenced Milk", 11000, "IP Burenka", 250, 265, 50, 100, 50);
		cout << "New product created:\n" << CondencedMilk.GetFullDetails() << endl;

		Product Milk(1005698, "Milk", 4900, "IP Burenka-2", 1000, 1020, 80, 300, 80);
		cout << "New product created:\n" << Milk.GetFullDetails() << endl;

		// Put those products into a new StockDB:
		StockDB mainStockDB;
		mainStockDB.CreateStockRecord(Cucumbers, 25);
		mainStockDB.CreateStockRecord(Milk, 30);
		mainStockDB.CreateStockRecord(CondencedMilk);
		mainStockDB.CreateStockRecord(Tomatoes);
		mainStockDB.ChangeAvailableQnt(Tomatoes.GetCode(), 7);
		mainStockDB.ChangeAvailableQnt(CondencedMilk.GetCode(), 80);
		cout << endl;

		cout << mainStockDB.PrintAllProductsInStock();
		cout << endl;

		mainStockDB.DeleteStockRecord(Cucumbers.GetCode());
		cout << endl;
		cout << mainStockDB.PrintAllProductsInStock();
		cout << endl;

		Order testPurchase(mainStockDB);

		cout << endl;

		testPurchase.AddProduct(CondencedMilk.GetCode(), 2);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";

		testPurchase.AddProduct(Tomatoes.GetCode(), 1);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";

		testPurchase.AddProduct(Milk.GetCode(), 3);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		testPurchase.AddProduct(Milk.GetCode(), 2);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		testPurchase.AddProduct(Milk.GetCode(), 28);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		testPurchase.RemoveProduct(Milk.GetCode(), 4);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		testPurchase.RemoveProduct(Milk.GetCode(), 7);
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		testPurchase.AddProduct(Cucumbers.GetCode(), 3);
		testPurchase.RemoveProduct(Cucumbers.GetCode(), 3);
		testPurchase.DeleteOrderLine(Cucumbers.GetCode());
		testPurchase.DeleteOrderLine(Tomatoes.GetCode());
		cout << testPurchase.PrintAllProductsInOrder() << "\n";

		cout << mainStockDB.PrintAllProductsInStock();
		testPurchase.SubmitOrder();
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
		cout << mainStockDB.PrintAllProductsInStock();

		testPurchase.AddProduct(Milk.GetCode(), 1);
		testPurchase.AddProduct(Milk.GetCode(), 28);
		testPurchase.RemoveProduct(Milk.GetCode(), 4);

		testPurchase.CloseOrder();
		testPurchase.Pay(20000);
		testPurchase.CloseOrder();
		testPurchase.Pay(6900);
		testPurchase.CloseOrder();
		testPurchase.Pay(690);
		testPurchase.CloseOrder();
		cout << testPurchase.PrintAllProductsInOrder() << "\n";
	}
	catch (exception &exception) 
	{
		cerr << "Standard exception: " << exception.what() << '\n';
	}
	
	return 0;
}