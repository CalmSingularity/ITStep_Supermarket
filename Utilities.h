#pragma once
#include <string>
using namespace std;
#include "Product.h"

string MoneyToString(size_t money);   // Takes money value *100 (including cents/copeiks) and converts it into a string formatted as 1 234.56
string WeightToString(size_t weight); // Takes weight value in grams and converts it into a string formatted as 12.345
string TmToString(tm date, bool showTime = false);  // Takes date/time in a form of tm structure and returns a string with the date formatted as DD/MM/YYYY
string SetStringWidth(string input, size_t length, char filler = ' '); // Adds filler character to the end of the string to its length is less that length argument
string GetQuantityAsString(double quantity, bool soldByWeight); // return quantity as string with fractional part if product is soldByWeight or integer otherwise