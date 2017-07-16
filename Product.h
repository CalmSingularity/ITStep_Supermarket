#pragma once
#include <ctime>
#include <string>
#include <iostream>
using namespace std;
#include "Utilities.h"

class Product 
{
private:
	size_t productCode;
	string productName;
	long long unitCentPrice; // price of one item of the product WITH cents/copeiks (*100)
	string manufacturer;  // name of the manufacturer of the product
	long long weightNet;     // net weight of one item of the product in grams
	long long weightGross;   // gross weight of one item of the product in grams
	long long width, height, length;   // dimensions in millimiters

/* The following functionality is removed	
	//bool soldByWeight;    // shows if the product is sold by weight (without fixed package)
	//tm productionDate;    // date of manufacturing
	//tm expirationDate;    // expiry date
*/

public:
	// Constructor
	Product(
		size_t productCode,
		string productName,
		long long unitCentPrice,
		string manufacturer = "",
		long long weightNet = 0,
		long long weightGross = 0,
		long long width = 0,
		long long height = 0, 
		long long length = 0
		);

	size_t GetCode();
	string GetName();
	long long GetNetWeight();
	long long GetGrossWeight();
	long long GetWidth();
	long long GetHeight();
	long long GetLength();
	long long GetUnitCentPrice();

	// Returns productCode and productName as a string looking like '(code) "name"'
	string GetCodeAndName(); 

	// Returns all fields of an object (full details of a product) as a string
	string GetFullDetails();


/* The following functionality is removed	
	//void SetManufacturer(string manufacturer);
	//void SetWeightGross(long long weightGross);
	//void SetDimensions(long long width, long long height, long long length);
	//void SetProductionDate(int prod_mday, int prod_month, int prod_year); // takes: day of month from 1 to 31, month of year from 1 to 12, year
	//void SetExpirationDate(int exp_mday, int exp_mon, int exp_year); // takes: day of month from 1 to 31, month of year from 1 to 12, year
	//string GetProductionDate();  // returns a string "DD/MM/YYYY"
	//string GetExpirationDate();  // returns a string "DD/MM/YYYY"
	//bool IsExpired();
*/

	friend class StockDB;
};