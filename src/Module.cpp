/*
 * Module.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Module.h"

Module::Module(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong) :
		mt(mt), busCom(busCom) {
	// TODO Auto-generated constructor stub

}

Module::~Module() {
	// TODO Auto-generated destructor stub
}

int Module::getValueInt(aJsonObject* root, const char * id) {
	if (aJson.getObjectItem(root, id) != NULL) {
		int value = (int) aJson.getObjectItem(root, id)->valueint;
		Serial.print(StrIndent);
		Serial.print(StrIndent);
		Serial.print(id);
		Serial.println(value);
		return value;
	}
	return NULL;
}
