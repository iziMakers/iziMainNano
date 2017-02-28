/*
 * Module.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "../modules/Module.h"

Module::Module(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		mt(mt), busCom(busCom), comManager(comManager), serialNumber(serialNumber), lastReading(
				lastReading) {
	processJsonInput(root);
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
void Module::processSpecificInput(aJsonObject* root) {
}
void Module::sendJson() {
}

ModuleType Module::getType() {
	return mt;
}
BusCommunication Module::getBusCom() {
	return busCom;
}
void Module::setBusCom(BusCommunication bus) {
	busCom = bus;
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

void Module::sendOutput(aJsonObject* objectJSON) {
	if (objectJSON != NULL) {
		char* msg = aJson.print(objectJSON);
		int i = 0;
		while (*(msg + i) != '\0') {
			comManager->outBuffer[i] = *(msg + i);
			i += 1;
		}
		comManager->outBuffer_len = i;
		free(msg);
		//freeMem("freeMem");
		//comManager->send();
		Serial.println(":ok");
	} else {
		Serial.print(StrError);
		Serial.println(":json");
	}

}

