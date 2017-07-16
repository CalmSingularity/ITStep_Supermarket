#pragma once
#include <string>
using namespace std;
#include "Product.h"

/* Takes money value *100 (including cents/copeiks) and converts it into a string formatted as 1 234.56 */
string MoneyToString(long long money);

/* Converts weight in grams into a string formatted as 12.345 (kilos.grams) */
string WeightToString(long long weight);

/* Takes date/time in a form of tm structure and returns a string with the date formatted as DD/MM/YYYY.
 * If showTime is true, adds HH:MM:SS */
string TmToString(tm date, bool showTime = false);

/* Adds filler character to the end of the string if its length is less that width argument */
string SetStringWidth(string input, int width, bool adjustRight = false, char filler = ' ');