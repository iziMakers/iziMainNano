#ifndef MODULES_MANAGER_H
#define MODULES_MANAGER_H
#include "modules/Module.h"

Module* Module_getModule(unsigned long sn);

#define NB_MODULES_MAX    3

int nb_modules = 0;
Module modules[NB_MODULES_MAX];

Module* Module_getModule(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules[i].getSerialNumber() == sn) {
			return &modules[i];
		}
	}
	return NULL;
}

#endif /*MODULES_MANAGER_H*/
