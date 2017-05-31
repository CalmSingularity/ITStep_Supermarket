#include <iostream>
using namespace std;
#include "Product.h"
#include "Order.h"
#include "Utilities.h"

int main() {
	Product Cucumbers(1002577, "Cucumbers", 21055, 1000, true);
	Cucumbers.setManufacturer("OOO Greenhouse");
	Cucumbers.setProductionDate(25, 5, 2017);
	Cucumbers.setExpirationDate(01, 6, 2017);
	cout << "New product added:\n" << Cucumbers.getFullDetails() << endl;
	
	Product Tomatoes(1002593, "Tomatoes", 33710, 1000, true);
	Tomatoes.setManufacturer("OOO Greenhouse");
	Tomatoes.setProductionDate(25, 5, 2017);
	Tomatoes.setExpirationDate(31, 5, 2017);
	cout << "New product added:\n" << Tomatoes.getFullDetails() << endl;

	Product CondencedMilk(1006608, "Condenced Milk", 11000, 250, false);
	CondencedMilk.setManufacturer("IP Burenka");
	CondencedMilk.setWeightGross(265);
	CondencedMilk.setProductionDate(1, 4, 2017);
	CondencedMilk.setExpirationDate(31, 3, 2018);
	CondencedMilk.setDimensions(100, 150, 100);
	cout << "New product added:\n" << CondencedMilk.getFullDetails() << endl;


	Order test_purchase;




	if (test_purchase.isClosed()) {
		cout << "Order is closed at " << test_purchase.getClosedTime() << "\n";
	}

	return 0;
}

