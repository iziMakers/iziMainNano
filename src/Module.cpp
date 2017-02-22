/*
 * Module.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Module.h"

Module::Module() {
	// TODO Auto-generated constructor stub

}

Module::~Module() {
	// TODO Auto-generated destructor stub
}
bool Module::isKnown(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules_SN[i] == sn) {
			return true;
		}
	}
	return false;
}

int Module::number(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules_SN[i] == sn) {
			return i;
		}
	}
	return -1;
}

int Module::bus(unsigned long sn) {
	int modNum = number(sn);
	if (modNum > -1) {
		return modules_Bus[modNum];
	}
	return -1;
}
