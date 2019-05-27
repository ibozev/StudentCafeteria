/*
 * Drink.h
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#ifndef DRINK_H_
#define DRINK_H_

#include "Product.h"

class Drink: public Product {
	private:
		double volume; //in liters
	public:
		Drink(ProdType type = ProdType::DRINK, std::string name = "",
				double price = 0.0, double volume = 0.0);
		virtual ~Drink() {};
		virtual std::ostream& serialize(std::ostream &out) override;
		virtual std::istream& deserialize(std::istream &in) override;
		virtual void printInfo() const;
		virtual void setNewValue(const double newVol) override { volume = newVol; }
};

#endif /* DRINK_H_ */
