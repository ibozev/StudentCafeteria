/*
 * Order.h
 *
 *  Created on: Nov 25, 2018
 *      Author: bozev21
 */

#ifndef ORDER_H_
#define ORDER_H_

class Order {
	private:
		std::string dateOfOrder;
		double orderPrice;
		std::string ownerName;
		std::vector<std::string> products;
	public:
		Order();
		Order(std::string, std::vector<std::string>, double);
		virtual ~Order() {};
		void printInfo();
		std::string getOwnerName() const { return ownerName; }
		std::string getDateOfOrder() const { return dateOfOrder; }
	private:
		void setDate();
		friend std::istream& operator >> (std::istream &in, Order &obj);
		friend std::ostream& operator << (std::ostream &out, Order &obj);
};

#endif /* ORDER_H_ */
