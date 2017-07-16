#include "StockDB.h"


StockDB::StockRecord::StockRecord(Product product, long long availableQnt) :
	product(product),
	availableQnt(availableQnt)
{}

bool StockDB::CreateStockRecord(Product product, long long availableQnt)
{
	if (IsInStock(product.GetCode())) {
		clog << "Product " << product.GetCodeAndName() << " is already in the stock!\n";
		return false;
	}

	StockRecord stockRecord(product, availableQnt);
	if (m_ProductsInStock.insert(make_pair(product.productCode, stockRecord)).second) {
		clog << "New product " << product.GetCodeAndName() << " is added to the stock with quantity "
			<< stockRecord.availableQnt << "\n";
		return true;
	}
	else {
		cerr << "Error: a new product " << product.GetCodeAndName() << " is not added to the stock!\n";
		return false;
	}
}

bool StockDB::IsInStock(size_t productCode)
{
	if (m_ProductsInStock.find(productCode) == m_ProductsInStock.end()) {
		cerr << "Product with code " << productCode << " is not in stock!\n";
		return false;
	}
	else {
		return true;
	}
}

StockDB::StockRecord StockDB::ReadStockRecord(size_t productCode)
{
	if (!IsInStock(productCode)) {
		Product dummyProduct(productCode, "", 0);
		StockRecord dummyRecord(dummyProduct, 0);
		return dummyRecord;
	}
	else {
		return m_ProductsInStock.at(productCode);
	}
}

long long StockDB::GetAvailableQnt(size_t productCode)
{
	StockRecord stockRecord = ReadStockRecord(productCode);
	return stockRecord.availableQnt;
}

bool StockDB::ChangeAvailableQnt(size_t productCode, long long delta)
{
	if (!IsInStock(productCode)) {
		return false;
	}

	StockDB::StockRecord stockRecord = ReadStockRecord(productCode);
	if (((long long)stockRecord.availableQnt + delta) < 0) {
		cerr << "Cannot change quantity of " << stockRecord.product.GetCodeAndName() << " by " << delta
			<< ", because the current quantity is " 
			<< WeightToString(stockRecord.availableQnt) << "!\n";
		return false;
	}
	else {
		m_ProductsInStock.at(productCode).availableQnt += delta;
		stockRecord = ReadStockRecord(productCode);
		clog << "Changed quantity of " << stockRecord.product.GetCodeAndName() << " by " << to_string(delta) 
			<< ". New quantity = " << to_string(stockRecord.availableQnt) << "\n";
		return true;
	}
}

bool StockDB::DeleteStockRecord(size_t productCode)
{
	if (!IsInStock(productCode)) {
		return false;
	}

	int nErased = m_ProductsInStock.erase(productCode);
	if (nErased >= 1) {
		clog << "Removed product with code " << productCode << " from the stock. " << nErased << " record(s) removed.\n";
		return true;
	}
	else {
		cerr << "Error: cannot remove product with code " << productCode << " from the stock.\n";
		return false;
	}
}

string StockDB::PrintStockRecord(StockRecord stockRecord)
{
	return
		SetStringWidth(to_string(stockRecord.product.productCode), 13) + " " +
		SetStringWidth(stockRecord.product.productName, 20) + " " +
		SetStringWidth(to_string(stockRecord.availableQnt), 7) + "\n";
}

string StockDB::PrintAllProductsInStock()
{
	string result = "Product Code  Product Name         Available Qnt\n";
	for (auto it : m_ProductsInStock) {
		result += PrintStockRecord(it.second);
	}

	return result;
}


