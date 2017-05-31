#include "Product.h"

Product::Product(
	size_t product_code,
	string product_name, 
	size_t unit_price,
	size_t weight_net,
	bool soldByWeight)
	:
	product_code(product_code),
	product_name(product_name),
	unit_price(unit_price),
	weight_net(weight_net),
	soldByWeight(soldByWeight)
{
	manufacturer = "";
	width = 0;
	height = 0;
	length = 0;	
	if (soldByWeight)
		weight_gross = weight_net;
	else
		weight_gross = 0;
}

void Product::setManufacturer(string manufacturer) 
{
	this->manufacturer = manufacturer;
}

void Product::setWeightGross(size_t weight_gross)
{
	this->weight_gross = weight_gross;
}

void Product::setDimensions(size_t width, size_t height, size_t length)
{
	this->width = width;
	this->height = height;
	this->length = length;
}

string Product::getFullDetails()
{
	string result =
		"Code:               " + to_string(product_code) + "\n" +
		"Name:               " + product_name + "\n" +
		"Manufacturer:       " + manufacturer + "\n" +
		"Unit price:         " + moneyToString(unit_price) + " RUB\n" +
		"Net weight:         " + weightToString(weight_net) + " kg\n";
	if (soldByWeight) {
		result += 
			"Sold by weight:     Yes\n";
	} 
	else {
		result +=
			"Gross weight:       " + weightToString(weight_gross) + " kg\n" +
			"Dimensions (WxHxL): " + to_string(width) + " mm x "
			+ to_string(height) + " mm x " + to_string(length) + " mm\n";
	}
	result +=
		"Produced on:        " + getProductionDate() + "\n" +
		"Expires on:         " + getExpirationDate() + "\n";
	
	if (isExpired())
		result += "EXPIRED!\n";
	
	return result;
}

size_t Product::getWidth()
{
	return this->width;
}

size_t Product::getHeight()
{
	return this->height;
}

size_t Product::getLength()
{
	return this->length;
}

void Product::setProductionDate(int prod_mday, int prod_month, int prod_year) 
{
	production_date.tm_mday = prod_mday;
	production_date.tm_mon = prod_month - 1;
	production_date.tm_year = prod_year - 1900;
}

void Product::setExpirationDate(int exp_mday, int exp_mon, int exp_year)
{
	expiration_date.tm_mday = exp_mday;
	expiration_date.tm_mon = exp_mon - 1;
	expiration_date.tm_year = exp_year - 1900;
}

string Product::getProductionDate() 
{
	return tmToString(production_date);
}

string Product::getExpirationDate()
{
	return tmToString(expiration_date);;
}

bool Product::isExpired()
{
	// TODO!
//	time_t current_time = time(NULL);
//	if (expiration_date < *localtime(&current_time))
		return false;
//	else
//		return true;
}

