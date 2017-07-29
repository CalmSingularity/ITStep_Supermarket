#include "Receipt.h"

Receipt::Receipt(Order& m_Order):
	m_Order(m_Order)
{}

string Receipt::OrderLineToString(Order::OrderLine orderLine)
{
	return
		SetStringWidth(to_string(orderLine.product.GetCode()), 12) + "  " +
		SetStringWidth(orderLine.product.GetName(), 20) + "  " +
		SetStringWidth(MoneyToString(orderLine.unitCentPrice), 11, true) + " *" +
		SetStringWidth(to_string(orderLine.qnt), 9, true) + " =" +
		SetStringWidth(MoneyToString(orderLine.unitCentPrice * orderLine.qnt), 14, true) + "\n";
}

string Receipt::GetAllProductsInOrder()
{
	string result =
		"--------------------------------------------------------------------------\n"; 
	result +=
		"Product Code  Product Name           Unit Price   Quantity     Total Price\n";
	result +=
		"--------------------------------------------------------------------------\n";
	for (auto it : m_Order.m_ProductsInOrder) {
		result += OrderLineToString(it.second);
	}
	return result;
}

string Receipt::GetHeader()
{
	string result =
		"-------------------------------- RECEIPT ---------------------------------\n";
	result +=
		  "Order created:   " + TmToString(m_Order.GetCreationTime(), true) +
		"\nOrder submitted: ";
	if (m_Order.IsSubmitted()) {
		result += TmToString(m_Order.GetSubmittedTime(), true);
	}
	else {
		result += "No";
	}
	
	result +=
		"\nOrder closed:    ";
	if (m_Order.IsClosed()) {
		result += TmToString(m_Order.GetClosedTime(), true);
	}
	else {
		result += "No";
	}

	result +=
		"\nOrder paid:      ";
	if (m_Order.IsPaid()) {
		result += "Yes";
	}
	else {
		result += "No";
	}

	result +=
		"\nNumber of positions: " + to_string(m_Order.GetNumberOfProducts());
	result +=
		"\nTotal gross weight:  " + WeightToString(m_Order.GetTotalGrossWeight()) + " kg\n";

	return result;
}

string Receipt::GetFinancialTotals()
{
	string result =
		"--------------------------------------------------------------------------\n";
	result +=
		  "Order total: " + SetStringWidth(MoneyToString(m_Order.totalCentAmount), 20, true) +
		"\nPaid:        " + SetStringWidth(MoneyToString(m_Order.paidCentAmount), 20, true) + 
		"\nDue:         " + SetStringWidth(MoneyToString(m_Order.GetAmountDue()), 20, true) + 
		"\n--------------------------------------------------------------------------\n";
	return result;
}

string Receipt::GetReceipt()
{
	return GetHeader() + GetAllProductsInOrder() + GetFinancialTotals();
}
