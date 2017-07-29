#include "CashDeskConsole.h"

CashDeskConsole::CashDeskConsole(StockDB& m_Stock):
	m_Stock(m_Stock)
{}

void CashDeskConsole::PrintMenu()
{
	cout << "-------------- Cash Desk Menu --------------\n";
	cout << "M                   = print MENU\n";
	cout << "B                   = print STOCK database\n";
	cout << "I product_code      = get full PRODUCT INFO\n";
	cout << "A product_code qnt  = ADD some quantity of a product to the order\n";
	cout << "R product_code qnt  = REMOVE some quantity of a product from the order\n";
	cout << "D product_code      = DELETE a product from the order completely\n";
	cout << "L                   = LIST all products in the order\n";
	cout << "F product_code      = FIND a product in the order\n";
	cout << "S                   = SUBMIT the order for payment\n";
	cout << "P amount_with_cents = accept a full or partial PAYMENT for the order\n";
	cout << "C                   = CLOSE the order\n";
	cout << "T                   = print RECEIPT\n";
	cout << "U                   = *fill the order with products for testing purposes\n";
	cout << "Q                   = QUIT\n\n";
	cout << "Enter a command below:\n";
}

void CashDeskConsole::FlushInputStream()
{
	cin.ignore(256, '\n');
}


int CashDeskConsole::RunConsole()
{
	cout << "Welcome to Cash Desk Console!\n";
	Order order(m_Stock);   // create new order
	Receipt receipt(order); // attach a receipt to it
	PrintMenu();
	char input;
	size_t productCode;
	int qnt;
	long long money;

	do {
		cout << "\n>> ";
		cin >> input; // get command from user

		// evaluate command:
		switch (input) { 
		case 'M':
		case 'm':
			PrintMenu();
			FlushInputStream();
			break;
		case 'B':
		case 'b':
			cout << m_Stock.PrintAllProductsInStock() << endl;
			FlushInputStream();
			break;
		case 'I':
		case 'i':
			cin >> productCode;
			cout << m_Stock.ReadStockRecord(productCode).product.GetFullDetails();
			FlushInputStream();
			break;
		case 'A':
		case 'a':
			cin >> productCode >> qnt;
			order.AddProduct(productCode, qnt);
			cout << receipt.OrderLineToString(order.ReadOrderLine(productCode));
			FlushInputStream();
			break;
		case 'R':
		case 'r':
			cin >> productCode >> qnt;
			order.RemoveProduct(productCode, qnt);
			cout << receipt.OrderLineToString(order.ReadOrderLine(productCode));
			FlushInputStream();
			break;
		case 'D':
		case 'd':
			cin >> productCode;
			order.DeleteOrderLine(productCode);
			FlushInputStream();
			break;
		case 'L':
		case 'l':
			cout << receipt.GetAllProductsInOrder();
			FlushInputStream();
			break;
		case 'F':
		case 'f':
			cin >> productCode;
			cout << receipt.OrderLineToString(order.ReadOrderLine(productCode));
			FlushInputStream();
			break;
		case 'S':
		case 's':
			cout << "Submitting the order...\n";
			order.SubmitOrder();
			FlushInputStream();
			break;
		case 'P':
		case 'p':
			cin >> money;
			if (order.Pay(money)) {
				cout << receipt.GetFinancialTotals();
			}
			FlushInputStream();
			break;
		case 'C':
		case 'c':
			cout << "Closing the order...\n";
			order.CloseOrder();
			FlushInputStream();
			break;
		case 'T':
		case 't':
			cout << receipt.GetReceipt();
			FlushInputStream();
			break;
		case 'U':
		case 'u':
			order.AddProduct(111, 2);
			order.AddProduct(121, 1);
			order.AddProduct(141, 5);
			order.AddProduct(181, 1);
			order.AddProduct(211, 1);
			order.AddProduct(212, 2);
			order.AddProduct(224, 1);
			order.AddProduct(225, 2);
			order.AddProduct(217, 1);
			order.AddProduct(228, 2);
			FlushInputStream();
			break;
		case 'Q':
		case 'q':
			cout << "Good bye!\n";
			break;

		}
	} while ((input != 'Q') && (input != 'q'));

	return 0;
}
