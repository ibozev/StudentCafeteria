/*
 * Order.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: bozev21
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Order.h"

using namespace std;

Order::Order() :
		dateOfOrder(), orderPrice(), ownerName(), products()
{
}

Order::Order(string name, vector<string> vect, double price) :
		orderPrice(price), ownerName(name), products(vect)
{
	Order::setDate();
}

void Order::setDate() {
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
	dateOfOrder = ostr.str();
}

istream& operator >> (istream &in, Order &obj) {
	in >> obj.dateOfOrder;
	in >> obj.orderPrice;
	in >> std::ws; //extract extra white spaces before string
	getline(in, obj.ownerName);

    std::size_t products_sz;
    if (in >> products_sz >> std::ws ) { //throw away the new line
        obj.products.resize(products_sz) ;
        for (string &s : obj.products)
        	getline(in, s);
    }
	return in;
}

ostream& operator << (ostream &out, Order &obj) {
	//first line
	out << obj.dateOfOrder << " " << obj.orderPrice << " " << obj.ownerName << endl;

	// number of products on the next lime
	out << obj.products.size() << endl;
	for (string& s : obj.products)
		out << s << endl; // one product per line

	return out;
}

void Order::printInfo() {
	cout << dateOfOrder << "\t\t" << left << std::setw(32)
		<< ownerName << std::fixed << std::setprecision(2)
			<< orderPrice << " lv." << endl;
	for (string &s : products)
		cout << "\t- " << s << endl;
	cout << endl;
}

