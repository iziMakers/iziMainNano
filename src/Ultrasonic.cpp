/*
 * Ultrasonic.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Ultrasonic.h"
#include <arduino.h>

Ultrasonic::Ultrasonic() {
	// TODO Auto-generated constructor stub

}

Ultrasonic::~Ultrasonic() {
	// TODO Auto-generated destructor stub
}
int Ultrasonic::getUltrasonic() {
	//process();
	return ultrasonic_cm;
}

int Ultrasonic::getUltrasonic_inch() {
	//process();
	return (int) (ultrasonic_cm / 2.54);
}

void Ultrasonic::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.println("Uin");
				if (root != NULL) {
		int value = getValueInt(root, "US");
		if (value != NULL) {
			ultrasonic_cm = value;
			lastReading = millis();
					}
					//aJson.deleteItem(obj);
				} else {
					Serial.print(StrError);
					Serial.println(":USin");
				}
				aJson.deleteItem(root);
			}
