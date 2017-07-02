#include "Order.h"
#include <string>
#include <iostream>
using namespace std;


Order::Order(StockDB& m_Stock):
	m_Stock(m_Stock)
{	
	totalWeight = 0;
	totalCentAmount = 0;
	paidCentAmount = 0;
	isSubmitted = false;
	isClosed = false;
	
	time_t currentTime = time(NULL);
	createdAt = *localtime(&currentTime);

	clog << "New order created at: " << GetCreationTime() << "\n";
}

Order::OrderLine::OrderLine(Product product, size_t qnt, size_t price) :
	product(product),
	qnt(qnt),
	price(price)
{}

bool Order::AddProduct(size_t productCode, size_t quantityToAdd)
{
	if (!m_Stock.IsInStock(productCode)) {
		return false;
	}
	
	// TODO: Check if there is enough in stock!

	if (IsInOrder(productCode)) {
		m_ProductsInOrder.at(productCode).qnt += quantityToAdd;

	}

	return true;
}

bool Order::IsInOrder(size_t productCode)
{
	if (m_ProductsInOrder.find(productCode) == m_ProductsInOrder.end()) {
		cerr << "Product with code " << productCode << " is not in the order!\n";
		return false;
	}
	else {
		return true;
	}
}

size_t Order::GetNumberOfProducts()
{
	return m_ProductsInOrder.size();
}

bool Order::IsClosed()
{
	return isClosed;
}

string Order::GetCreationTime()
{
	return TmToString(createdAt, true);
}

string Order::GetSubmittedTime()
{
	return TmToString(submittedAt, true);
}

string Order::GetClosedTime()
{
	return TmToString(closedAt, true);
}

