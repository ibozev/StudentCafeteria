/*
 * Meal.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <iomanip>
#include "Meal.h"

using namespace std;

Meal::Meal(ProdType type, string name, double price, double weight) :
		Product(type, name, price), weight(weight)
{
}

ostream& Meal::serialize(ostream &out) {
	return out << type << " " << id << " "
			<< weight << " " << price << " " << name ;
}

istream& Meal::deserialize(istream &in) {
	in >> id;
	in >> weight;
	in >> price;
	in >> ws; //extract extra whitespaces before string
	getline(in, name);

	return in;
}

void Meal::printInfo() const {
	string prodType;

	if (type == Product::ProdType::MEAL)
		prodType = "meal";
	cout << prodType << right << std::setw(14) << id << "\t" << left << std::setw(24)
			<< name << std::fixed << std::setprecision(0) << weight << "gr.\t\t"
				<< std::fixed << std::setprecision(2) << price << " lv." << endl;
}
