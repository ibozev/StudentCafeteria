/*
 * Main.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */
#include <iostream>
#include <vector>
#include "Account.h"
#include "Product.h"
#include "Order.h"
#include "menu_manager.h"

using namespace std;

void setUniqueIds(const vector<Account*> &vectAcc, const vector<Product*> &vectProd) {
	Account::setUniqueAccId(vectAcc);
	Product::setUniqueProdId(vectProd);
}

int main() {
	vector<Account*> vectAcc;
	vector<Product*> vectProd;
	vector<Order*> vectOrders;

	menu_manager::fillUpVectors(vectAcc, vectProd, vectOrders);
	setUniqueIds(vectAcc, vectProd);

	menu_manager::userInterface(vectAcc, vectProd, vectOrders);

	menu_manager::exit(vectAcc, vectProd, vectOrders);
	cout << "Successfully exit!" << endl;

	return 0;
}
