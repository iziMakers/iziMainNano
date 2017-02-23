/*
 * Ultrasonic.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		Module(mt, busCom, comManager, serialNumber, lastReading, root) {
}

Ultrasonic::~Ultrasonic() {
}
int Ultrasonic::getDistanceCm() {
	//process();
	return distanceCm;
}

int Ultrasonic::getDistanceInch() {
	//process();
	return (int) (distanceCm / 2.54);
}

void Ultrasonic::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.println("Uin");
	if (root != NULL) {
		int value = getValueInt(root, "US");
		if (value != NULL) {
			distanceCm = value;
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":USin");
	}
	aJson.deleteItem(root);
}
