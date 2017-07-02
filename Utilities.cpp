#include "Utilities.h"

unsigned long long raiseToPower(unsigned int base, unsigned int power) {
	if (power == 0) {
		return 1;
	}
	if (power == 1) {
		return base;
	}
	if (power == 2) {
		return base * base;
	}

	if (power >= 3) {
		unsigned long long result = raiseToPower(base, power / 2);
		result *= result;
		if (power % 2 == 1)
			result *= base;
		return result;
	}
}

string MoneyToString(long long money) {
	string result = to_string(money);

	if (result.length() < 2) {
		result.insert(0, "0.0");
	}
	else if (result.length() == 2) {
		result.insert(0, "0.");
	}
	else {
		int pos = result.length() - 2;
		result.insert(pos, ".");
		pos -= 3;
		while (pos > 0) {
			result.insert(pos, " ");
			pos -= 3;
		}
	}

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

string SetStringWidth(string input, size_t length, bool adjustRight, char filler) 
{
	string result = "";
	if (!adjustRight) {
		result += input;
	}
	size_t to_add = length - input.size();
	if (to_add > 0)	{
		for (size_t i = 0; i < to_add; ++i)	{
			result.push_back(filler);
		}
	}
	if (adjustRight) {
		result += input;
	}
	return result;
}