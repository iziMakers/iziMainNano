#ifndef MODULES_MANAGER_H
#define MODULES_MANAGER_H
#include "modules/Module.h"

Module* Module_getModule(unsigned long sn);
Module* Module_getModuleKnown(unsigned long sn);

void addModuleKnown(Module module);

#define NB_MODULES_MAX    3

int nb_modules = 0;
Module modules[NB_MODULES_MAX];
Module modulesKnown[NB_MODULES_MAX];

Module* Module_getModule(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modules[i].getSerialNumber() == sn) {
			return &modules[i];
		}
	}
	return NULL;
}
Module* Module_getModuleKnown(unsigned long sn) {
	for (int i = 0; i < nb_modules; i++) {
		if (modulesKnown[i].getSerialNumber() == sn) {
			return &modulesKnown[i];
		}
	}
	return NULL;
}

void addModuleKnown(Module module) {
	modulesKnown[nb_modules] = module;
	nb_modules++;
}


#endif /*MODULES_MANAGER_H*/
