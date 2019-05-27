/*
 * menu_manager.h
 *
 *  Created on: Nov 18, 2018
 *      Author: bozev21
 */

#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_

namespace menu_manager {
	void fillUpVectors(std::vector<Account*> &vectAcc,
			std::vector<Product*> &vectProd, std::vector<Order*> &vectOrders);

	void exit(std::vector<Account*> &vectAcc,
				std::vector<Product*> &vectProd, std::vector<Order*> &vectOrders);

	void userInterface(std::vector<Account*> &vectAcc,
			std::vector<Product*> &vectProd, std::vector<Order*> &vectOrders);
};

#endif /* MENU_MANAGER_H_ */
