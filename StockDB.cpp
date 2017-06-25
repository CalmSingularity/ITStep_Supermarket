#include "StockDB.h"

StockDB::StockRecord::StockRecord(Product product, size_t availableQnt) :
	product(product),
	availableQnt(availableQnt)
{}

bool StockDB::CreateStockRecord(Product product, size_t availableQnt)
{
	if (IsInStock(product.GetCode())) {
		clog << "Product " << product.GetCodeName() << " is already in stock!\n";
		return false;
	}

	StockRecord stockRecord(product, availableQnt);
	if (m_ProductsInStock.insert(make_pair(product.productCode, stockRecord)).second) {
		clog << "New product " << product.GetCodeName() << " is added to the stock with quantity "
			<< QuantityToString(stockRecord.availableQnt, stockRecord.product.soldByWeight) << "\n";
		return true;
	}
	else {
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
		Product dummyProduct(0, "", 0, 0, false);
		StockRecord dummyRecord(dummyProduct, 0);
		return dummyRecord;
	}
	else {
		return m_ProductsInStock.at(productCode);
	}
}

size_t StockDB::GetAvailableQnt(size_t productCode)
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
		cerr << "Cannot change quantity of " << stockRecord.product.GetCodeName() << " by " << delta
			<< ", because the current quantity is " 
			<< QuantityToString(stockRecord.availableQnt, stockRecord.product.soldByWeight) << "!\n";
		return false;
	}
	else {
		m_ProductsInStock.at(productCode).availableQnt += delta;
		stockRecord = ReadStockRecord(productCode);
		clog << "Changed quantity of " << stockRecord.product.GetCodeName() << " by " 
			<< QuantityToString(delta, stockRecord.product.soldByWeight) << ". New quantity = "
			<< QuantityToString(stockRecord.availableQnt, stockRecord.product.soldByWeight) << "\n";
		return true;
	}
}

bool StockDB::DeleteStockRecord(size_t productCode)
{
	if (!IsInStock(productCode)) {
		return false;
	}

	size_t nErased = m_ProductsInStock.erase(productCode);
	if (nErased >= 1) {
		clog << "Removed product with code " << productCode << " from the stock. " << nErased << " record(s) removed.\n";
		return true;
	}
	else {
		return false;
	}
}

string StockDB::GetProductInStock(size_t productCode)
{
	if (IsInStock(productCode)) {
		StockDB::StockRecord stockRecord = ReadStockRecord(productCode);
		return
			SetStringWidth(to_string(productCode), 12) + " " +
			SetStringWidth(stockRecord.product.productName, 20) + " " +
			SetStringWidth(QuantityToString(stockRecord.availableQnt, stockRecord.product.soldByWeight), 10) + "\n";
	}
	else {
		return "";
	}
}

string StockDB::GetAllProductsInStock()
{
	string result = "Product ID   Product Name         Available Qnt\n";
	for (auto it: m_ProductsInStock) {
		if (it.second.availableQnt > 0) {
			result += 
				SetStringWidth(to_string(it.second.product.productCode), 12) + " " +
				SetStringWidth(it.second.product.productName, 20) + " " +
				SetStringWidth(QuantityToString(it.second.availableQnt, it.second.product.soldByWeight), 10) + "\n";
		}
	}
	return result;
}

