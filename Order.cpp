#include "Order.h"
#include <string>
#include <iostream>
using namespace std;

Order::Order()
{	
	time_t current_time = time(NULL);
	created_at = *localtime(&current_time);
	total_weight = 0;
	total_amount = 0;
	paid_amount = 0;
	is_closed = false;

	clog << "New order created at: " << GetCreationTime() << "\n";
}

size_t Order::GetNumberOfProducts()
{
	return m_ProductsInOrder.size();
}

string Order::GetCreationTime()
{
	return TmToString(created_at, true);
}

bool Order::IsClosed()
{
	return is_closed;
}

string Order::GetClosedTime()
{
	return TmToString(closed_at, true);
}
