/*
 * Product.cpp
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#include <fstream>
#include <vector>
#include "Product.h"

using namespace std;

long int Product::uniqueProdId = 1;

Product::Product(ProdType pType, string pName, double pPrice) :
		type(pType), name(pName), price(pPrice)
{
	if (pName.empty())
		return;
	Product::setId();
}

void Product::setUniqueProdId(const std::vector<Product*> &vect) {
	if (vect.empty())
		return; //id == 1

	Product::uniqueProdId = ((vect.back()->id) + 1);
}

void Product::setId() {
	id = uniqueProdId++;
//	uniqueProdId++;
}

istream& operator >> (istream &in, Product &obj) {
	return obj.deserialize(in);
}

ostream& operator << (ostream &out, Product &obj){
	return obj.serialize(out);
}
