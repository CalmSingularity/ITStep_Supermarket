#include <iostream>
#include <exception>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"
#include "StockDB.h"
#include "CashDeskConsole.h"

int main() 
{
	try 
	{
		// Create some products:
		Product milk(111, "Milk", 7600, "Parmalat", 1000, 1020, 80, 300, 80);
		Product cheese(121, "Cheese", 21980, "Lactalis", 200, 210);
		Product cottageCheese(131, "Cottage cheese", 11900, "IP Burenka", 200, 210);
		Product yoghurt(141, "Yoghurt", 4700, "Danone", 310, 320);
		Product condencedMilk(181, "Condenced Milk", 14500, "IP Burenka", 650, 655, 50, 200, 100);
		Product bananas(211, "Bananas", 4990, "OOO Greenhouse", 1000, 1000);
		Product apples(212, "Apples", 15500, "OOO Greenhouse", 1000, 1000);
		Product pears(213, "Pears", 12900, "OOO Greenhouse", 1000, 1000);
		Product oranges(214, "Oranges", 10500, "Turkey", 1000, 1000);
		Product melon(217, "Melon \'Torpeda\'", 15300, "Uzbekistan", 3000, 3000);
		Product potatoes(221, "Potatoes", 4100, "OOO Greenhouse", 1000, 1010);
		Product cucumbers(222, "Cucumbers", 5250, "OOO Greenhouse", 1000, 1010);
		Product tomatoes(223, "Tomatoes", 18500, "OOO Greenhouse", 1000, 1010);
		Product onions(223, "Onions", 4100, "OOO Greenhouse", 1000, 1010);
		Product carrots(224, "Carrots", 4900, "OOO Greenhouse", 1000, 1010);
		Product cabbage(225, "Cabbage", 8200, "OOO Greenhouse", 2000, 2000);
		Product eggplants(228, "Eggplants", 14500, "Agrokombinat", 650, 658);
		
		// Put those products into a new StockDB:
		StockDB mainStockDB;
		mainStockDB.CreateStockRecord(milk, 25);
		mainStockDB.DeleteStockRecord(milk.GetCode());
		mainStockDB.CreateStockRecord(milk, 40);
		mainStockDB.CreateStockRecord(milk, 40);
		mainStockDB.CreateStockRecord(cheese);
		mainStockDB.CreateStockRecord(yoghurt);
		mainStockDB.ChangeAvailableQnt(cheese.GetCode(), 7);
		mainStockDB.ChangeAvailableQnt(yoghurt.GetCode(), 17);
		mainStockDB.CreateStockRecord(cottageCheese, 20);
		mainStockDB.CreateStockRecord(condencedMilk, 10);
		mainStockDB.CreateStockRecord(bananas, 15);
		mainStockDB.CreateStockRecord(apples, 20);
		mainStockDB.CreateStockRecord(pears, 10);
		mainStockDB.CreateStockRecord(oranges, 15);
		mainStockDB.CreateStockRecord(melon, 5);
		mainStockDB.CreateStockRecord(potatoes, 40);
		mainStockDB.CreateStockRecord(cucumbers, 30);
		mainStockDB.CreateStockRecord(tomatoes, 30);
		mainStockDB.CreateStockRecord(onions, 10);
		mainStockDB.CreateStockRecord(carrots, 20);
		mainStockDB.CreateStockRecord(cabbage, 10);
		mainStockDB.CreateStockRecord(eggplants, 8);
		
		cout << endl << endl;

		CashDeskConsole cashDesk(mainStockDB);
		cashDesk.RunConsole();

	}
	catch (exception &exception) 
	{
		cerr << "Standard exception: " << exception.what() << '\n';
	}
	
	return 0;
}