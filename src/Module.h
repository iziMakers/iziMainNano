/*
 * Module.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULE_H_
#define SRC_MODULE_H_

class Module {
public:
	Module();
	virtual ~Module();

	bool isKnown(unsigned long sn);
	int number(unsigned long sn);
	int bus(unsigned long sn);
};

#endif /* SRC_MODULE_H_ */
