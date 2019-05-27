/*
 * Meal.h
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#ifndef MEAL_H_
#define MEAL_H_

#include "Product.h"

class Meal: public Product {
	private:
		double weight; //grams
	public:
		Meal(ProdType type = ProdType::MEAL, std::string name = "",
				double price = 0.0, double weight = 0.0);
		virtual ~Meal() {};
		virtual std::ostream& serialize(std::ostream &out) override;
		virtual std::istream& deserialize(std::istream &in) override;
		virtual void printInfo() const;
		virtual void setNewValue(const double newWeight) override { weight = newWeight; }
};

#endif /* MEAL_H_ */
