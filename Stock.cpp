#include "Stock.h"

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
	return m_ProductsInStock.at(product.product_id).second;
}

bool Stock::AddProduct(Product new_product)
{
	if (this->IsInStock(new_product)) {
		clog << "Product " << new_product.GetIdName() << " is already in stock!\n";
		return false;
	}

	m_ProductsInStock.insert(make_pair(new_product.product_id, make_pair(new_product, 0)));
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

	m_ProductsInStock.at(product.product_id).second += delta;
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
	//Product* product;
	//double quantity;
	for (auto it = m_ProductsInStock.begin(); it != m_ProductsInStock.end(); ++it) {
		//quantity = it->second.second;
		if (it->second.second > 0.0000001) {
			result += 
				SetStringWidth(to_string(it->second.first.product_id), 12) + " " +
				SetStringWidth(it->second.first.product_name, 20) + " " +
				SetStringWidth(GetQuantityAsString(it->second.second, it->second.first.soldByWeight), 10) + "\n";
		}
	}
	return result;
}
