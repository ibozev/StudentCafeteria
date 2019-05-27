/*
 * Student.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <iomanip>
#include "Student.h"

using namespace std;

Student::Student(AccType type, string name, string num) :
	Account(type, name), fNum(num)
{
}

ostream& Student::serialize(ostream &out) {
	return out << type << " " << id << " "
			<< dateOfReg << " " << discount << " " << fNum << " " << name ;
}

istream& Student::deserialize(istream &in) {
	in >> id;
	in >> dateOfReg;
	in >> discount;
	in >> fNum;
	in >> ws; //extract extra white spaces before string
	getline(in, name);

	return in;
}

void Student::printInfo() const {
	string accType;

	if (type == Account::AccType::STUDENT)
		accType = "student";
	cout << accType << "\t\t" << dateOfReg << right << std::setw(15) << id << "\t"
			<< left << std::setw(24)<< name << discount << "%"
			<< "\t\t" << fNum << endl;
}
