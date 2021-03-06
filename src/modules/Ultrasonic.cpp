/*
 * Ultrasonic.cpp
 *
 *  Created on: 21 f�vr. 2017
 *      Author: Bruno
 */

#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(unsigned long serialNumber, unsigned long lastReading,
		aJsonObject* root) :
		Module(serialNumber, lastReading, root) {
	mt = mtUltrasonic;
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
