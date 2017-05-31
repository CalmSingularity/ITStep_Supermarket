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

	cout << "New order created at: " << this->getCreationTime() << "\n";
}

size_t Order::getNumberOfProducts()
{
	return productsInOrder.size();
}

string Order::getCreationTime()
{
	return tmToString(created_at, true);
}

bool Order::isClosed()
{
	return is_closed;
}

string Order::getClosedTime()
{
	return tmToString(closed_at, true);
}
