#pragma once
#include <string>
using namespace std;

string moneyToString(size_t money);   // Takes money value *100 (including cents/copeiks) and converts it into a string formatted as 1 234.56
string weightToString(size_t weight); // Takes weight value in grams and converts it into a string formatted as 12.345
string tmToString(tm date, bool show_time = false);  // Takes date/time in a form of tm structure and returns a string with the date formatted as DD/MM/YYYY