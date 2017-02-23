/*
 * Joystick.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Joystick.h"

Joystick::Joystick(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		Module(mt, busCom, comManager, serialNumber, lastReading, root) {
}

Joystick::~Joystick() {
}

int Joystick::getAxeX() {
	//process();
	return axeX;
}
int Joystick::getAxeY() {
	//process();
	return axeY;
}
bool Joystick::isPressed() {
	//process();
	return buttonState;
}

void Joystick::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.println("Jin");
	int value;
	if (root != NULL) {
		value = getValueInt(root, "JX");
		if (value != NULL) {
			axeX = value;
			lastReading = millis();
		}
		value = getValueInt(root, "JY");
		if (value != NULL) {
			axeY = value;
			lastReading = millis();
		}
		value = getValueInt(root, "JSW");
		if (value != NULL) {
			if (value != 0) {
				buttonState = true;
			} else {
				buttonState = false;
			}
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":");
	}
	aJson.deleteItem(root);
}

void Joystick::processOutput() {
	if (!1/*sendOutput*/) {
		if (millis() > lastWriting + 300) {
			aJsonObject* objectJSON = aJson.createObject();
			aJson.addItemToObject(objectJSON, "sn",
					aJson.createItem((int) getSerialNumber()));
			aJson.addItemToObject(objectJSON, "j", aJson.createItem(1));

			Serial.print(StrIndent);
			Serial.print("Jout:");
			sendOutput(objectJSON);
			aJson.deleteItem(objectJSON);
		}
		lastReading = millis();
	}
}
