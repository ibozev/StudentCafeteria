/*
 * Account.h
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "ISerialization.h"
#include <vector>

class Account : public ISerialization {
	public:
		enum AccType {
			STUDENT, //0
			TEACHER //1
		};
	protected:
		AccType type;
		std::string dateOfReg;
		long int id;
		std::string name;
		double discount; //in percents
	private:
		static long int uniqueAccId;
	public:
		Account(AccType , std::string);
		virtual ~Account() {};
		virtual void printInfo() const  = 0;
		virtual std::string getName() const { return name; }
		static void setUniqueAccId(const std::vector<Account*> &vect);
		long int getId() const { return id; }
	protected:
		friend std::istream& operator >> (std::istream &in, Account &obj);
		friend std::ostream& operator << (std::ostream &out, Account &obj);
	private:
		void setDate();
		void setDisc();
		void setId();
};

#endif /* ACCOUNT_H_ */
