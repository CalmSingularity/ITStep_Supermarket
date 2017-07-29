#include <string>
#include <iostream>
using namespace std;
#include "Order.h"

Order::Order(StockDB& m_Stock):
	m_Stock(m_Stock)
{	
	totalGrossWeight = 0;
	totalCentAmount = 0;
	paidCentAmount = 0;
	isSubmitted = false;
	isClosed = false;
	
	time_t currentTime = time(NULL);
	createdAt = *localtime(&currentTime);

	clog << "New order created at " << TmToString(GetCreationTime(), true) << "\n";
}

Order::OrderLine::OrderLine(Product product, long long qnt, long long unitCentPrice) :
	product(product),
	qnt(qnt),
	unitCentPrice(unitCentPrice)
{}

bool Order::AddProduct(size_t productCode, int qntToAdd)
{
	if (qntToAdd <= 0) {
		return false;
	}

	if (isSubmitted) {
		cerr << "Cannot change the order because it's submitted for payment!\n";
		return false;
	}

	StockDB::StockRecord stockRecord = m_Stock.ReadStockRecord(productCode);
	OrderLine orderLine = ReadOrderLine(productCode);
	
	if (stockRecord.availableQnt < (qntToAdd + orderLine.qnt)) {
		cerr << "Not enough of product " << stockRecord.product.GetCodeAndName() <<
			" is available in the stock to add " << qntToAdd << " unit(s) to the order.\n";
		return false;
	}
	
	if (IsInOrder(productCode)) {

		m_ProductsInOrder.at(productCode).qnt += qntToAdd;
		totalGrossWeight += stockRecord.product.GetGrossWeight() * qntToAdd;
		totalCentAmount += stockRecord.product.GetUnitCentPrice() * qntToAdd;

		OrderLine updatedOrderLine = ReadOrderLine(productCode);
		clog << stockRecord.product.GetCodeAndName() << " is already in the order. Added " << 
			qntToAdd << " unit(s). New quantity in the order is " << updatedOrderLine.qnt << ".\n";
		return true;
	}
	else {
		OrderLine newOrderLine(stockRecord.product, qntToAdd, stockRecord.product.GetUnitCentPrice());
		if (m_ProductsInOrder.insert(make_pair(productCode, newOrderLine)).second) {
			totalGrossWeight += stockRecord.product.GetGrossWeight() * qntToAdd;
			totalCentAmount += stockRecord.product.GetUnitCentPrice() * qntToAdd;
			clog << "New product " << stockRecord.product.GetCodeAndName() << " is added to the order with quantity "
				<< newOrderLine.qnt << ".\n";
			return true;
		}
		else {
			cerr << "Error: new product " << stockRecord.product.GetCodeAndName() << " is not added to the order!\n";
			return false;
		}
	}
}

bool Order::RemoveProduct(size_t productCode, int qntToRemove)
{
	if (qntToRemove <= 0) {
		return false;
	}

	if (isSubmitted) {
		cerr << "Cannot change the order because it's submitted for payment!\n";
		return false;
	}

	if (!IsInOrder(productCode)) {
		cerr << "Product with code " << productCode << " is not in the order!\n";
		return false;
	}
	
	OrderLine orderLine = ReadOrderLine(productCode);
	if (orderLine.qnt < qntToRemove) {
		cerr << "Cannot remove " << qntToRemove << " unit(s) of " << orderLine.product.GetCodeAndName() <<
			", because there are only " << orderLine.qnt << " unit(s) in the order.\n";
		return false;
	}
	else {
		m_ProductsInOrder.at(productCode).qnt -= qntToRemove;
		totalGrossWeight -= orderLine.product.GetGrossWeight() * qntToRemove;
		totalCentAmount -= orderLine.product.GetUnitCentPrice() * qntToRemove;
		OrderLine updatedOrderLine = ReadOrderLine(productCode);
		clog << "Removed " << qntToRemove << " unit(s) of " << orderLine.product.GetCodeAndName() <<
			" from the order. Remaining quantity is " << updatedOrderLine.qnt << ".\n";
		return true;
	}
}

bool Order::IsInOrder(size_t productCode)
{
	if (m_ProductsInOrder.find(productCode) == m_ProductsInOrder.end()) {
		cerr << "Product with code " << productCode << " is not in the order.\n";
		return false;
	}
	else {
		return true;
	}
}

Order::OrderLine Order::ReadOrderLine(size_t productCode)
{
	if (!IsInOrder(productCode)) {
		Product dummyProduct(productCode, "", 0);
		OrderLine dummyLine(dummyProduct, 0, 0);
		return dummyLine;
	}
	else {
		return m_ProductsInOrder.at(productCode);
	}
}

bool Order::DeleteOrderLine(size_t productCode)
{
	if (isSubmitted) {
		cerr << "Cannot change the order because it's submitted for payment!\n";
		return false;
	}

	if (!IsInOrder(productCode)) {
		return false;
	}

	OrderLine orderLine = ReadOrderLine(productCode);
	int nErased = m_ProductsInOrder.erase(productCode);
	if (nErased >= 1) {
		totalGrossWeight -= orderLine.product.GetGrossWeight() * orderLine.qnt;
		totalCentAmount -= orderLine.product.GetUnitCentPrice() * orderLine.qnt;
		clog << "Removed product " << orderLine.product.GetCodeAndName() << " from the order. " << nErased << " line(s) removed.\n";
		return true;
	}
	else {
		cerr << "Error: cannot remove product " << orderLine.product.GetCodeAndName() << " from the order.\n";
		return false;
	}
}

long long Order::GetNumberOfProducts()
{
	return m_ProductsInOrder.size();
}

long long Order::GetTotalAmount()
{
	return totalCentAmount;
}

long long Order::GetPaidAmount()
{
	return paidCentAmount;
}

long long Order::GetAmountDue()
{
	return (totalCentAmount - paidCentAmount);
}

long long Order::GetTotalGrossWeight()
{
	return totalGrossWeight;
}

bool Order::SubmitOrder()
{
	if (isSubmitted) {
		cerr << "Cannot submit the order because it's already submitted!\n";
		return false;
	}

	// check if all products are sufficient in the stock
	for (auto it : m_ProductsInOrder) {
		StockDB::StockRecord stockRecord = m_Stock.ReadStockRecord(it.first);
		if (it.second.qnt > stockRecord.availableQnt) {
			cerr << "Cannot submit the order because there is only " << stockRecord.availableQnt << 
				" unit(s) of " << stockRecord.product.GetCodeAndName() << " is available!\n";
			return false;
		}
	}

	// decrease products' available quantity in the stock
	for (auto it : m_ProductsInOrder) {
		bool successReleaseFromStock = m_Stock.ChangeAvailableQnt(it.first, -it.second.qnt);
		if (!successReleaseFromStock) {
			cerr << "Critical error! Cannot release " << it.second.qnt << " unit(s) of " << 
				it.second.product.GetCodeAndName() << 
				" from stock. The available quantities in stock may be incorrect!\n";
			return false;
		}
	}

	time_t currentTime = time(NULL);
	submittedAt = *localtime(&currentTime);
	isSubmitted = true;

	clog << "The order is submitted at " << TmToString(GetSubmittedTime(), true) << "\n";
	return true;
}

bool Order::IsSubmitted()
{
	return isSubmitted;
}

bool Order::Pay(long long paymentAmount)
{
	if (!isSubmitted) {
		cerr << "Cannot pay for the order because it's not submitted!\n";
		return false;
	}
	if (isClosed) {
		cerr << "Cannot pay for the order because it's already closed!\n";
		return false;
	}
	paidCentAmount += paymentAmount;
	clog << "Accepted payment of " << MoneyToString(paymentAmount) << endl;
	return true;
}

bool Order::IsPaid()
{
	if ((paidCentAmount - totalCentAmount) >= 0) {
		return true;
	}
	else { 
		return false; 
	}

}

bool Order::CloseOrder()
{
	if (!isSubmitted) {
		cerr << "Cannot close the order because it's not submitted!\n";
		return false;
	}
	if (!IsPaid()) {
		cerr << "Cannot close the order because it's not paid!\n";
		return false;
	}
	if (isClosed) {
		cerr << "Cannot close the order because it's already closed!\n";
		return false;
	}

	time_t currentTime = time(NULL);
	closedAt = *localtime(&currentTime);
	isClosed = true;

	clog << "The order is closed at " << TmToString(GetSubmittedTime(), true) << "\n";
	return true;
}

bool Order::IsClosed()
{
	return isClosed;
}

tm Order::GetCreationTime()
{
	return createdAt;
}

tm Order::GetSubmittedTime()
{
	return submittedAt;
}

tm Order::GetClosedTime()
{
	return closedAt;
}
