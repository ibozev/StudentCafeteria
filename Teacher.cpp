/*
 * Teacher.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <iomanip>
#include "Teacher.h"

using namespace std;

Teacher::Teacher(AccType aType, string aName) :
	Account(aType, aName)
{
}

ostream& Teacher::serialize(ostream &out) {
	return out << type << " " << id << " "
			<< dateOfReg << " " << discount << " " << name ;
}

istream& Teacher::deserialize(istream &in) {
	in >> id;
	in >> dateOfReg;
	in >> discount;
	in >> ws; //extract extra whitespaces before string
	getline(in, name);

	return in;
}

void Teacher::printInfo() const {
	string accType;

	if (type == Account::AccType::TEACHER)
		accType = "teacher";
	cout << accType << "\t\t" << dateOfReg << right << std::setw(15) << id << "\t"
			<< left << std::setw(24) << name << discount << "%" << endl;
}
