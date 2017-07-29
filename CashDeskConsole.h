#pragma once
#include <iostream>
using namespace std;
#include "StockDB.h"
#include "Order.h"
#include "Receipt.h"

class CashDeskConsole 
{
private:
	StockDB& m_Stock;    // which stock database orders will be connected to

public:
	CashDeskConsole(StockDB& m_Stock); // constructor
	int RunConsole();  // run console interface
	void PrintMenu();  // prints menu to the output stream
	void FlushInputStream();  // flushes remaining characters in the input stream
};