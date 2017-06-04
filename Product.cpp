#include "Product.h"

Product::Product(
	size_t product_id,
	string product_name, 
	size_t unit_price,
	size_t weight_net,
	bool soldByWeight)
	:
	product_id(product_id),
	product_name(product_name),
	unit_price(unit_price),
	weight_net(weight_net),
	soldByWeight(soldByWeight)
{
	manufacturer = "";
	width = 0;
	height = 0;
	length = 0;	
	if (soldByWeight) {
		weight_gross = weight_net;
	} 
	else {
		weight_gross = 0;
	}

	/*clog << "New product added:\n" << 
		"Code:           " << to_string(product_id) << "\n" <<
		"Name:           " << product_name << "\n" <<
		"Unit price:     " << MoneyToString(unit_price) << " RUB\n" <<
		"Net weight:     " << WeightToString(weight_net) << " kg\n";
	if (soldByWeight) {
		clog <<	"Sold by weight: Yes\n";
	}*/
}

void Product::SetManufacturer(string manufacturer) 
{
	this->manufacturer = manufacturer;
}

void Product::SetWeightGross(size_t weight_gross)
{
	this->weight_gross = weight_gross;
}

void Product::SetDimensions(size_t width, size_t height, size_t length)
{
	this->width = width;
	this->height = height;
	this->length = length;
}

size_t Product::GetId()
{
	return product_id;
}

string Product::GetFullDetails()
{
	string result =
		"Code:               " + to_string(product_id) + "\n" +
		"Name:               " + product_name + "\n" +
		"Manufacturer:       " + manufacturer + "\n" +
		"Unit price:         " + MoneyToString(unit_price) + " RUB\n" +
		"Net weight:         " + WeightToString(weight_net) + " kg\n";
	if (soldByWeight) {
		result += 
			"Sold by weight:     Yes\n";
	} 
	else {
		result +=
			"Gross weight:       " + WeightToString(weight_gross) + " kg\n" +
			"Dimensions (WxHxL): " + to_string(width) + " mm x "
			+ to_string(height) + " mm x " + to_string(length) + " mm\n";
	}
	result +=
		"Produced on:        " + GetProductionDate() + "\n" +
		"Expires on:         " + GetExpirationDate() + "\n";
	
	if (IsExpired())
		result += "EXPIRED!\n";
	
	return result;
}

string Product::GetIdName()
{
	return "(" + to_string(product_id) + ") \"" + product_name + "\"";
}

size_t Product::GetWidth()
{
	return this->width;
}

size_t Product::GetHeight()
{
	return this->height;
}

size_t Product::GetLength()
{
	return this->length;
}

void Product::SetProductionDate(int prod_mday, int prod_month, int prod_year) 
{
	production_date.tm_mday = prod_mday;
	production_date.tm_mon = prod_month - 1;
	production_date.tm_year = prod_year - 1900;
}

void Product::SetExpirationDate(int exp_mday, int exp_mon, int exp_year)
{
	expiration_date.tm_mday = exp_mday;
	expiration_date.tm_mon = exp_mon - 1;
	expiration_date.tm_year = exp_year - 1900;
}

string Product::GetProductionDate() 
{
	return TmToString(production_date);
}

string Product::GetExpirationDate()
{
	return TmToString(expiration_date);;
}

bool Product::IsExpired()
{
	// TODO!
//	time_t current_time = time(NULL);
//	if (expiration_date < *localtime(&current_time))
		return false;
//	else
//		return true;
}

