/*
 * Module.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Module.h"

Module::Module(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		mt(mt), busCom(busCom), comManager(comManager), serialNumber(serialNumber), lastReading(
				lastReading) {
	processInput(root);
}

Module::~Module() {
}
void Module::processInput(aJsonObject* root) {
}
void Module::processOutput() {
}
ModuleType Module::getType() {
	return mt;
}
BusCommunication Module::getBusCom() {
	return busCom;
}
unsigned long Module::getSerialNumber() {
	return serialNumber;
}
unsigned long Module::getLastReading() {
	return lastReading;
}
void Module::setLastReading(unsigned long date) {
	lastReading = date;
}
unsigned long Module::getLastWriting() {
	return lastWriting;
}
void Module::setLastWriting(unsigned long date) {
	lastWriting = date;
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

