#include "Order.h"
#include <string>
#include <iostream>
using namespace std;

Order::Order()
{	
	time_t currentTime = time(NULL);
	createdAt = *localtime(&currentTime);
	totalWeight = 0;
	totalCentAmount = 0;
	paidCentAmount = 0;
	isClosed = false;

	clog << "New order created at: " << GetCreationTime() << "\n";
}

Order::OrderLine::OrderLine(Product product, size_t qnt, size_t price) :
	product(product),
	qnt(qnt),
	price(price)
{}

bool Order::AddProduct(size_t productCode, size_t quantityToAdd)
{

	return true;
}

size_t Order::GetNumberOfProducts()
{
	return m_ProductsInOrder.size();
}

string Order::GetCreationTime()
{
	return TmToString(createdAt, true);
}

bool Order::IsClosed()
{
	return isClosed;
}

string Order::GetClosedTime()
{
	return TmToString(closedAt, true);
}

