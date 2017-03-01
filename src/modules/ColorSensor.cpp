/*
 * ColorSensor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "ColorSensor.h"

ColorSensor::ColorSensor(unsigned long serialNumber, unsigned long lastReading,
		aJsonObject* root) :
		Module(mtColorSensor, serialNumber, lastReading, root) {
}

ColorSensor::~ColorSensor() {
}

void ColorSensor::processSpecificInput(aJsonObject* root) {
	Serial.print("Cin");
	int value;
	for (int i = 1; i < 5; i++) {
		value = getValueInt(root, parameterNames[i]);
		setFromJson(i, value);
	}
}
void ColorSensor::setFromJson(int id, int value) {
	if (value != NULL) {
		switch (id) {
		case 0:
			// serialNumber;
			break;
		case 1:
			hue = value;
			break;
		case 2:
			saturation = value;
			break;
		case 3:
			iValue = value;
			break;
		case 4:
			preset = value;
			break;
		default:
			// error
			return;
		}
		lastReading = millis();
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
