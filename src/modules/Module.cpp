/*
 * Module.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "../modules/Module.h"

Module::Module(unsigned long serialNumber, unsigned long lastReading,
		aJsonObject* root) :
		serialNumber(serialNumber), lastReading(lastReading) {
	if (root != NULL)
		processJsonInput(root);
	mt = mtWrong;
}

Module::~Module() {
}
void Module::processJsonInput(aJsonObject* root) {
	Serial.print(StrIndent);
	if (root != NULL) {
		processSpecificInput(root);
		lastReading = millis();
	} else {
		Serial.print(StrError);
		Serial.println(":");
	}
	aJson.deleteItem(root);
}

uint8_t Module::getType() {
	return mt;
}
unsigned long Module::getSerialNumber() {
	return serialNumber;
}
unsigned long Module::getLastReading() {
	return lastReading;
}
unsigned long Module::getLastWriting() {
	return lastWriting;
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
