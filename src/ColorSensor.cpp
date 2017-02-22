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

void ColorSensor::processInput(unsigned long SN) {
	if (isKnown(SN_ColorSensor)) {
		if (SN > 0) {
			if (SN == SN_ColorSensor) {
				Serial.print(StrIndent);
				Serial.print("Cin");
				//Serial.println(inBuffer);

				aJsonObject* root = aJson.parse(inBuffer);
				if (root != NULL) {
					Serial.print("\n");
					//Serial.println("Jin:");
					//Serial.print(inBuffer);
					if (aJson.getObjectItem(root, "H") != NULL) {
						COLORSENSOR_H = (int) aJson.getObjectItem(root, "H")->valueint;
						COLORSENSOR_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("H:");
						Serial.println(COLORSENSOR_H);
					}
					if (aJson.getObjectItem(root, "S") != NULL) {
						COLORSENSOR_S = (int) aJson.getObjectItem(root, "S")->valueint;
						COLORSENSOR_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("S:");
						Serial.println(COLORSENSOR_S);
					}
					if (aJson.getObjectItem(root, "V") != NULL) {
						COLORSENSOR_V = (int) aJson.getObjectItem(root, "V")->valueint;
						COLORSENSOR_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("V:");
						Serial.println(COLORSENSOR_V);
					}
					if (aJson.getObjectItem(root, "P") != NULL) {
						COLORSENSOR_P = (int) aJson.getObjectItem(root, "P")->valueint;
						COLORSENSOR_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("P:");
						Serial.println(COLORSENSOR_P);
					}
				} else {
					Serial.print(StrError);
					Serial.println(":");
				}
				aJson.deleteItem(root);
			}
		}
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
