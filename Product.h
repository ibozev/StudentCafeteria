/*
 * Product.h
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <vector>
#include "ISerialization.h"

class Product : public ISerialization {
	public:
		enum ProdType {
			DRINK,
			MEAL
		};
	protected:
		ProdType type;
		long int id;
		std::string name;
		double price;
	private:
		static long int uniqueProdId;
	public:
		Product(ProdType, std::string, double);
		virtual ~Product() {};
		virtual void printInfo() const  = 0;
		virtual void setNewValue(const double) = 0;
		static void setUniqueProdId(const std::vector<Product*> &vect);
		void setNewPrice(const double newPrice) { price = newPrice; }
		long int getId() const { return id; }
		std::string getName() const { return name; }
		double getPrice() const { return price; }
	protected:
		friend std::istream& operator >> (std::istream &in, Product &obj);
		friend std::ostream& operator << (std::ostream &out, Product &obj);
	private:
		void setId();
};

#endif /* PRODUCT_H_ */
