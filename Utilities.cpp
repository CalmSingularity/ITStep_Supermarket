#include "Utilities.h"


string MoneyToString(size_t money) {
	size_t millions = money / 100000000;
	size_t thousands = money / 100000 - millions * 1000;
	size_t singles = money / 100 - thousands * 1000 - millions * 1000000;
	size_t cents = money % 100;

	string result = "";

	// Add heading zeros to thousands:
	if (millions > 0) {
		result = to_string(millions) + " ";
		if (thousands < 100) {
			if (thousands < 10) {
				result += "00";
			}
			else {
				result += "0";
			}
		}
	}

	if (thousands > 0) {
		result += to_string(thousands) + " ";
		if (singles < 100) {
			if (singles < 10) {
				result += "00";
			}
			else {
				result += "0";
			}
		}
	}

	result += to_string(singles) + ".";

	if (cents < 10) {
		result += "0";
	}

	result += to_string(cents);

/* TRY THIS
	const int CENTS_DIGITS = 2;
	size_t temp = money / 10 * CENTS_DIGITS;  // get rid of cents
	size_t nDigits = 0;  
	while (temp > 0) { 
		// count the number of digits, excluding cents
		++nDigits;
		temp / 10;
	}

	string result = "";
	for (i = nDigits - 1; i > 0; --i) {
		string += to_string(money / ((10 * i) * (10 * CENTS_DIGITS)));
		if (i % 3 == 0) {
			string += " ";
		}
	}
	string += to_string(money % 10);
	string += ".";
	string += to_string(money % (10 * CENTS_DIGITS));

*/
	return result;
}


string WeightToString(size_t weight)
{
	size_t kilos = weight / 1000;
	size_t grams = weight % 1000;

	string result = to_string(kilos) + ".";

	if (grams < 100) {
		if (grams < 10) {
			result += "00";
		}
		else {
			result += "0";
		}
	}
	result += to_string(grams);
	return result;
}

string TmToString(tm date, bool showTime)
{
	string result = "";

	if (date.tm_mday < 10)
		result += "0";
	result += to_string(date.tm_mday);
	result += "/";

	if (date.tm_mon < 9)
		result += "0";
	result += to_string(date.tm_mon + 1);
	result += "/";
	
	result += to_string(date.tm_year + 1900);

	if (showTime) {
		result += " ";
		if (date.tm_hour < 10)
			result += "0";
		result += to_string(date.tm_hour);
		result += ":";
		if (date.tm_min < 10)
			result += "0";
		result += to_string(date.tm_min);
		result += ":";
		if (date.tm_sec < 10)
			result += "0";
		result += to_string(date.tm_sec);
	}

	return result;
}

string SetStringWidth(string input, size_t length, char filler) 
{
	string result = input;
	size_t to_add = length - input.size();
	if (to_add > 0)	{
		for (size_t i = 0; i < to_add; ++i)	{
			result.push_back(filler);
		}
		
	}
	return result;
}