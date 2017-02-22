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

void Ultrasonic::processInput(unsigned long SN) {
	if (isKnown(SN_Ultrasonic)) {
		if (SN > 0) {
			if (SN == SN_Ultrasonic) {
				aJsonObject* root = aJson.parse(inBuffer);
				if (root != NULL) {
					//Serial.print(inBuffer);
					//aJsonObject* obj;
					//obj = aJson.getObjectItem(root, "US");
					if (aJson.getObjectItem(root, "US") != NULL) {
						ultrasonic_cm = (int) aJson.getObjectItem(root, "US")->valueint;
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("US_cm: ");
						Serial.println(ultrasonic_cm);
						lastUltrasonic = millis();
					}
					//aJson.deleteItem(obj);
				} else {
					Serial.print(StrError);
					Serial.println(":USin");
				}
				aJson.deleteItem(root);
			}
		}
	}
}
