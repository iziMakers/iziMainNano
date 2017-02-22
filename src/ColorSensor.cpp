/*
 * ColorSensor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "ColorSensor.h"

ColorSensor::ColorSensor() {
	// TODO Auto-generated constructor stub

}

ColorSensor::~ColorSensor() {
	// TODO Auto-generated destructor stub
}

void ColorSensor::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.print("Cin");
	if (root != NULL) {
		int value = getValueInt(root, "H");
		if (value != NULL) {
			COLORSENSOR_H = value;
			lastReading = millis();
		}
		value = getValueInt(root, "S");
		if (value != NULL) {
			COLORSENSOR_S = value;
			lastReading = millis();
		}
		value = getValueInt(root, "V");
		if (value != NULL) {
			COLORSENSOR_V = value;
			lastReading = millis();
		}
		value = getValueInt(root, "P");
		if (value != NULL) {
			COLORSENSOR_P = value;
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":");
	}
}



int ColorSensor::getH() {
	//process();
	return COLORSENSOR_H;
}

int ColorSensor::getS() {
	//process();
	return COLORSENSOR_S;
}

int ColorSensor::getV() {
	//process();
	return COLORSENSOR_V;
}

int ColorSensor::getP() {
	//process();
	return COLORSENSOR_P;
}
