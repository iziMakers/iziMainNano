/*
 * ColorSensor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "ColorSensor.h"

ColorSensor::ColorSensor(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		Module(mt, busCom, comManager, serialNumber, lastReading, root) {
}

ColorSensor::~ColorSensor() {
}

void ColorSensor::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.print("Cin");
	if (root != NULL) {
		int value = getValueInt(root, "H");
		if (value != NULL) {
			hue = value;
			lastReading = millis();
		}
		value = getValueInt(root, "S");
		if (value != NULL) {
			saturation = value;
			lastReading = millis();
		}
		value = getValueInt(root, "V");
		if (value != NULL) {
			iValue = value;
			lastReading = millis();
		}
		value = getValueInt(root, "P");
		if (value != NULL) {
			preset = value;
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":");
	}
}

int ColorSensor::getH() {
	//process();
	return hue;
}

int ColorSensor::getS() {
	//process();
	return saturation;
}

int ColorSensor::getV() {
	//process();
	return iValue;
}

int ColorSensor::getP() {
	//process();
	return preset;
}
