#ifndef MODULES_MANAGER_H
#define MODULES_MANAGER_H
#include "Module.h"

bool Module_isKnown(unsigned long sn);
int Module_getId(unsigned long sn); // TODO check if it's really usefull
BusCommunication Module_getBus(unsigned long sn);

#define NB_MODULES_MAX    3

int nb_modules = 0;
Module modules[NB_MODULES_MAX];

bool Module_isKnown(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules[i].getSerialNumber() == sn) {
			return true;
		}
	}
	return false;
}

int Module_getId(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules[i].getSerialNumber() == sn) {
			return i;
		}
	}
	return -1;
}

BusCommunication Module_getBus(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules[i].getSerialNumber() == sn) {
			return modules[i].getBusCom();
		}
	}
	return bcWrong;
}

#endif /*MODULES_MANAGER_H*/
