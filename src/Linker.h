#ifndef MODULES_MANAGER_H
#define MODULES_MANAGER_H
#include <aJSON.h>
#include "modules/Module.h"
#include "bus/CommunicationManager.h"

#define NB_MODULES_MAX    3

int nbModules = 0;
Module* modules[NB_MODULES_MAX];
Module* Module_getModule(unsigned long sn);
void addModule(Module* module);

int nbKnownModules = 0;
Module* modulesKnown[NB_MODULES_MAX];
CommunicationManager* busForKnownModules[NB_MODULES_MAX];
Module* Module_getModuleKnown(unsigned long sn);
void addModuleKnown(Module* module, CommunicationManager* busForKnownModule);

Module* Module_getModule(unsigned long sn) {
	for (int i = 0; i < nbModules; i++) {
		if (modules[i]->getSerialNumber() == sn) {
			return modules[i];
		}
	}
	return NULL;
}
void addModule(Module* module) {
	if (nbModules < NB_MODULES_MAX) {
		modules[nbModules] = module;
		nbModules++;
	}
}
Module* Module_getModuleKnown(unsigned long sn) {
	for (int i = 0; i < nbKnownModules; i++) {
		if (modulesKnown[i]->getSerialNumber() == sn) {
			return modulesKnown[i];
		}
	}
	return NULL;
}

void addModuleKnown(Module* module, CommunicationManager* busForKnownModule) {
	if (nbModules < NB_MODULES_MAX) {
		modulesKnown[nbKnownModules] = module;
		busForKnownModules[nbKnownModules] = busForKnownModule;
		nbKnownModules++;
	}
}

void parseJSon(CommunicationManager* busForKnownModule, aJsonObject* root) {
	unsigned long serialNumber = 0;

	if (root != NULL) {
		aJsonObject* sn = aJson.getObjectItem(root, "sn");
		if (sn != NULL) {
			serialNumber = sn->valueint;    //valueint      root["sn"];
			Module* knownModule = Module_getModuleKnown(serialNumber);
			if (knownModule == NULL) {
				//Module newModule(mtWrong, receiveBus); // TODO create module there
				Module* unknownModule = Module_getModule(serialNumber);
				if (unknownModule != NULL) {
					unknownModule->processJsonInput(root);
					addModuleKnown(unknownModule, busForKnownModule);

					DEBUG_PRINT("  ");
					DEBUG_PRINT("New:");
					DEBUG_PRINTLN(serialNumber);
				} else {
					DEBUG_PRINT("Error");
					DEBUG_PRINTLN(":no WrongModuleConnected");
				}
			} else {
				knownModule->processJsonInput(root);

				DEBUG_PRINT("  ");
				DEBUG_PRINT("Mod:");
				DEBUG_PRINTLN(serialNumber);
			}
		} else {
			DEBUG_PRINT("Error");
			DEBUG_PRINTLN(":no \"sn\"");
		}
	}
	aJson.deleteItem(root);
}

#endif /*MODULES_MANAGER_H*/
