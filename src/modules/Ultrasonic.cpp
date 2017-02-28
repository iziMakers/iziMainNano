/*
 * Ultrasonic.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(unsigned long serialNumber,
		CommunicationManager* comManager, unsigned long lastReading,
		aJsonObject* root) :
		Module(mtUltrasonic, comManager, serialNumber, lastReading, root) {
}

Ultrasonic::~Ultrasonic() {
}
int Ultrasonic::getDistanceCm() {
	return distanceCm;
}

int Ultrasonic::getDistanceInch() {
	return (int) (distanceCm / 2.54);
}

void Ultrasonic::processSpecificInput(aJsonObject* root) {
	Serial.println("Uin");
	int value = getValueInt(root, "US");
	if (value != NULL) {
		distanceCm = value;
		lastReading = millis();
	}
}
