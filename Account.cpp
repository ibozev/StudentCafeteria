/*
 * Account.cpp
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include "Account.h"

using namespace std;

long int Account::uniqueAccId = 1;

Account::Account(AccType aType, string aName) :
	type(aType), name(aName)
{
	if (aName.empty()) //cuz of accId
		return;
	Account::setId();
	Account::setDate();
	Account::setDisc();
}

void Account::setUniqueAccId(const std::vector<Account*> &vect) {
	if (vect.empty())
		return; //id == 1

	Account::uniqueAccId = ((vect.back()->id) + 1);
}

void Account::setId() {
	id = uniqueAccId++;
//	Account::uniqueAccId++;
}

void Account::setDate() {
	ostringstream ostr;
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);

	ostr << (now->tm_year + 1900) << '-';

	if ((now->tm_mon + 1) < 10)
		ostr << "0" << now->tm_mon + 1;
	else
		ostr << now->tm_mon + 1;

	ostr << "-";

	if (now->tm_mday < 10)
		ostr << "0" << now->tm_mday;
	else
		ostr << now->tm_mday;

	dateOfReg = ostr.str();
}

void Account::setDisc() {
	if (type == AccType::STUDENT)
		discount = 30.00;
	else
		discount = 20.00;
}

istream& operator >> (istream &in, Account &obj) {
	return obj.deserialize(in);
}

ostream& operator << (ostream &out, Account &obj){
	return obj.serialize(out);
}
