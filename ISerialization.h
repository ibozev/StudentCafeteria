/*
 * ISerialization.h
 *
 *  Created on: Nov 21, 2018
 *      Author: bozev21
 */

#ifndef ISERIALIZATION_H_
#define ISERIALIZATION_H_

class ISerialization {
	public:
		virtual ~ISerialization() {};
		virtual std::ostream& serialize(std::ostream &out) = 0;
		virtual std::istream& deserialize(std::istream &in) = 0;
};

#endif /* ISERIALIZATION_H_ */
