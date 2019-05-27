/*
 * Student.h
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "Account.h"

class Student: public Account {
	private:
		std::string fNum;
	public:
		Student(AccType type = AccType::STUDENT, std::string name = "", std::string fNum= "");
		virtual ~Student() {};
		virtual std::ostream& serialize(std::ostream &out) override;
		virtual std::istream& deserialize(std::istream &in) override;
		virtual void printInfo() const;
		virtual std::string getName() const { return fNum; }
};

#endif /* STUDENT_H_ */
