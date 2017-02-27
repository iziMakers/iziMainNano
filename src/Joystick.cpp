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

void Joystick::processSpecificInput(aJsonObject* root) {
	Serial.print("Jin");
	int value;
	for (int i = 1; i < 3; i++) {
		value = getValueInt(root, parameterNames[i]);
		setFromJson(i, value);
	}
}

void Joystick::setFromJson(int id, int value) {
	if (value != NULL) {
		switch (id) {
		case 0:
			// serialNumber;
			break;
		case 1:
			axeX = value;
			break;
		case 2:
			axeY = value;
			break;
		case 3:
			buttonState = value;
			break;
		default:
			// error
			return;
		}
		lastReading = millis();
	}
}
void Joystick::sendJson() {
	if (millis() > lastWriting + 300) {

		aJsonObject* objectJSON = toJson();
		Serial.print(StrIndent);
		Serial.print("Jout:");
		sendOutput(objectJSON);
		aJson.deleteItem(objectJSON);
		lastWriting = millis();
	}
}
aJsonObject * Joystick::toJson() {
	aJsonObject* objectJSON = aJson.createObject();
	aJson.addItemToObject(objectJSON, parameterNames[0],
			aJson.createItem((int) getSerialNumber()));
	aJson.addItemToObject(objectJSON, parameterNames[1], aJson.createItem(1));

	return objectJSON;
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
