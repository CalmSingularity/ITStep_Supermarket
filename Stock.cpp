#include "Stock.h"

Stock::StockLine::StockLine(Product product, double quantity) :
	product(product),
	available(quantity)
{}

bool Stock::IsInStock(Product product)
{
	if (m_ProductsInStock.find(product.product_id) == m_ProductsInStock.end()) {
		return false;
	}
	else {
		return true;
	}
}

double inline Stock::GetQuantity(Product product)
{
	return m_ProductsInStock.at(product.product_id).available;
}

bool Stock::AddProduct(Product new_product)
{
	if (this->IsInStock(new_product)) {
		clog << "Product " << new_product.GetIdName() << " is already in stock!\n";
		return false;
	}

	StockLine stockline(new_product, 0);
	m_ProductsInStock.insert(make_pair(new_product.product_id, stockline));
	clog << "New product " << new_product.GetIdName() << " is added to stock with 0 quantity\n";

	return true;
}

bool Stock::ChangeQuantity(Product product, double delta)
{
	if (!IsInStock(product)) {
		cerr << product.GetIdName() << " is not in stock!\n";
		return false;
	}

	double current_quantity = GetQuantity(product);
	if ((current_quantity + delta) < 0) {
		cerr << "Cannot change quantity of " << product.GetIdName() << " by " << delta
			<< ", because the current quantity is " << current_quantity << "!\n";
		return false;
	}

	m_ProductsInStock.at(product.product_id).available += delta;
	clog << "Changed quantity of " << product.GetIdName() << " by " << delta << ". New quantity = "
		    << GetQuantity(product) << "\n";
	return true;
	
}

string Stock::GetProductInStock(Product product)
{
	if (IsInStock(product)) {
		return
			SetStringWidth(to_string(product.product_id), 12) + " " +
			SetStringWidth(product.product_name, 20) + " " +
			SetStringWidth(GetQuantityAsString(GetQuantity(product), product.soldByWeight), 10) + "\n";
	}
	else {
		cerr << "Product " << product.GetIdName() << " is not in stock!\n";
		return "";
	}
}

string Stock::GetAllProductsInStock()
{
	string result = "Product ID   Product Name         Available Qnt\n";
	for (auto it = m_ProductsInStock.begin(); it != m_ProductsInStock.end(); ++it) {
		if (it->second.available > 0.0000001) {
			result += 
				SetStringWidth(to_string(it->second.product.product_id), 12) + " " +
				SetStringWidth(it->second.product.product_name, 20) + " " +
				SetStringWidth(GetQuantityAsString(it->second.available, it->second.product.soldByWeight), 10) + "\n";
		}
	}
	return result;
}


