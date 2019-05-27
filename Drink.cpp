/*
 * Drink.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <iomanip>
#include "Drink.h"

using namespace std;

Drink::Drink(ProdType type, string name, double price, double vol) :
	Product(type, name, price), volume(vol)
{
}

ostream& Drink::serialize(ostream &out) {
	return out << type << " " << id << " "
			<< volume << " " << price << " " << name ;
}

istream& Drink::deserialize(istream &in) {
	in >> id;
	in >> volume;
	in >> price;
	in >> ws; //extract extra whitespaces before string
	getline(in, name);

	return in;
}

void Drink::printInfo() const {
	string prodType;

	if (type == Product::ProdType::DRINK)
		prodType = "drink";
	cout<< prodType << right << std::setw(13) << id << "\t"<< left << std::setw(24)
		<< name << std::fixed << std::setprecision(3) << volume << "l.\t\t"
			<< std::setprecision(2) << price << " lv." << endl;
}
