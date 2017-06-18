#include "StockDB.h"

StockDB::StockRecord::StockRecord(Product product, double quantity) :
	product(product),
	available(quantity)
{}

bool StockDB::IsInStock(Product product)
{
	if (m_ProductsInStock.find(product.productCode) == m_ProductsInStock.end()) {
		return false;
	}
	else {
		return true;
	}
}

double inline StockDB::GetQuantity(Product product)
{
	if (!IsInStock(product)) {
		cerr << product.GetCodeName() << " is not in stock!\n";
		return 0;
	}
	return m_ProductsInStock.at(product.productCode).available;
}

bool StockDB::AddProduct(Product new_product)
{
	if (this->IsInStock(new_product)) {
		clog << "Product " << new_product.GetCodeName() << " is already in stock!\n";
		return false;
	}

	StockRecord stockline(new_product, 0);
	if (m_ProductsInStock.insert(make_pair(new_product.productCode, stockline)).second) {
		clog << "New product " << new_product.GetCodeName() << " is added to stock with 0 quantity\n";
		return true;
	}
	else {
		return false;
	}
	
}

bool StockDB::ChangeQuantity(Product product, double delta)
{
	if (!IsInStock(product)) {
		cerr << product.GetCodeName() << " is not in stock!\n";
		return false;
	}

	double current_quantity = GetQuantity(product);
	if ((current_quantity + delta) < 0) {
		cerr << "Cannot change quantity of " << product.GetCodeName() << " by " << delta
			<< ", because the current quantity is " << current_quantity << "!\n";
		return false;
	}

	m_ProductsInStock.at(product.productCode).available += delta;
	clog << "Changed quantity of " << product.GetCodeName() << " by " << delta << ". New quantity = "
		    << GetQuantity(product) << "\n";
	return true;
	
}

string StockDB::GetProductInStock(Product product)
{
	if (IsInStock(product)) {
		return
			SetStringWidth(to_string(product.productCode), 12) + " " +
			SetStringWidth(product.productName, 20) + " " +
			SetStringWidth(GetQuantityAsString(GetQuantity(product), product.soldByWeight), 10) + "\n";
	}
	else {
		cerr << "Product " << product.GetCodeName() << " is not in stock!\n";
		return "";
	}
}

string StockDB::GetAllProductsInStock()
{
	string result = "Product ID   Product Name         Available Qnty\n";
	for (auto it = m_ProductsInStock.begin(); it != m_ProductsInStock.end(); ++it) {
		if (it->second.available > 0.0000001) {
			result += 
				SetStringWidth(to_string(it->second.product.productCode), 12) + " " +
				SetStringWidth(it->second.product.productName, 20) + " " +
				SetStringWidth(GetQuantityAsString(it->second.available, it->second.product.soldByWeight), 10) + "\n";
		}
	}
	return result;
}


