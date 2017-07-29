#include "Product.h"

Product::Product(
	size_t productCode,
	string productName,
	long long unitCentPrice,
	string manufacturer,
	long long weightNet,
	long long weightGross,
	long long width,
	long long height,
	long long length)
	:
	productCode(productCode),
	productName(productName),
	unitCentPrice(unitCentPrice),
	manufacturer(manufacturer),
	weightNet(weightNet),
	weightGross(weightGross),
	width(width),
	height(height),
	length(length)
{
/*
	clog << "New product added:\n" << 
		"Code:           " << to_string(productCode) << "\n" <<
		"Name:           " << productName << "\n" <<
		"Unit price:     " << MoneyToString(unitCentPrice) << " RUB\n" <<
		"Net weight:     " << WeightToString(weightNet) << " kg\n";
*/
}

size_t Product::GetCode()
{
	return productCode;
}

string Product::GetName()
{
	return productName;
}

long long Product::GetNetWeight()
{
	return weightNet;
}

long long Product::GetGrossWeight()
{
	return weightGross;
}

string Product::GetFullDetails()
{
	string result =
			"Code:               " + to_string(productCode) + "\n" +
			"Name:               " + productName + "\n" +
			"Unit price:         " + MoneyToString(unitCentPrice) + " RUB\n";
	if (manufacturer != "") {
		result += 
			"Manufacturer:       " + manufacturer + "\n";
	}
	if (weightNet != 0) {
		result +=
			"Net weight:         " + WeightToString(weightNet) + " kg\n";
	}
	if (weightGross != 0) {
		result +=
			"Gross weight:       " + WeightToString(weightGross) + " kg\n";
	}
	if (width != 0 && height != 0 && length != 0) {
		result += "Dimensions (WxHxL): " + to_string(width) + " mm x " + to_string(height) + " mm x " + to_string(length) + " mm\n";
	}

/* The following functionality is removed	
	result +=
		"Produced on:        " + GetProductionDate() + "\n" +
		"Expires on:         " + GetExpirationDate() + "\n";
	if (IsExpired())
		result += "PRODUCT EXPIRED!\n";
*/


	return result;
}

string Product::GetCodeAndName()
{
	return "(" + to_string(productCode) + ") \"" + productName + "\"";
}

long long Product::GetWidth()
{
	return this->width;
}

long long Product::GetHeight()
{
	return this->height;
}

long long Product::GetLength()
{
	return this->length;
}

long long Product::GetUnitCentPrice()
{
	return unitCentPrice;
}
