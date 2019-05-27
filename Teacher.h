/*
 * Teacher.h
 *
 *  Created on: Nov 11, 2018
 *      Author: bozev21
 */

#ifndef TEACHER_H_
#define TEACHER_H_

#include "Account.h"

class Teacher: public Account {
	public:
		Teacher(AccType type = AccType::TEACHER, std::string name = "");
		virtual ~Teacher() {};
		virtual std::ostream& serialize(std::ostream &out) override;
		virtual std::istream& deserialize(std::istream &in) override;
		virtual void printInfo() const;
};

#endif /* TEACHER_H_ */
