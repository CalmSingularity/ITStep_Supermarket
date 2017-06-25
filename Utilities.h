#pragma once
#include <string>
using namespace std;
#include "Product.h"

/* Takes money value *100 (including cents/copeiks) and converts it into a string formatted as 1 234.56 */
string MoneyToString(size_t money);

/* Converts weight into a string formatted as 12.345 (kilos.grams) */
string WeightToString(size_t weight); 

/* Takes date/time in a form of tm structure and returns a string with the date formatted as DD/MM/YYYY */
string TmToString(tm date, bool showTime = false);

/* Adds filler character to the end of the string to its length is less that length argument */
string SetStringWidth(string input, size_t width, char filler = ' ');