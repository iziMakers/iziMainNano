/*
 * Motor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Motor.h"
#include <arduino.h>

Motor::Motor() {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.print("Min");
	int value;
	if (root != NULL) {
		value = getValueInt(root, "a");
		if (value != NULL) {
			motorA_speed = value;
			lastReading = millis();
		}
		value = getValueInt(root, "b");
		if (value != NULL) {
			motorB_speed = value;
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":Min");
	}
	aJson.deleteItem(root);
}

void Motor::processOutput() {
	if (!1/*sendOutput*/) {
		if (motorA_speed != motorA_speed_target
				|| motorB_speed != motorB_speed_target
				|| (millis() >= lastMotors + 1000)) {
			if (millis() >= lastMotors + 100) {
				Serial.print(StrIndent);
				Serial.print("Mout:");
				aJsonObject* objectJSON = aJson.createObject();
				if (objectJSON != NULL) {
					aJson.addItemToObject(objectJSON, "sn", aJson.createItem(SN_Motors));
					aJson.addItemToObject(objectJSON, "a",
							aJson.createItem(motorA_speed_target));
					aJson.addItemToObject(objectJSON, "b",
							aJson.createItem(motorB_speed_target));
					char* msg = aJson.print(objectJSON);
					Serial.print(msg);
					int i = 0;
					while (*(msg + i) != '\0') {
						comManager->outBuffer[i] = *(msg + i);
						i += 1;
					}
					comManager->outBuffer_len = i;
					Serial.print(":");
					Serial.println(comManager->outBuffer_len);
					free(msg);

					//freeMem("freeMem");
					//sendOutput = true;
					//sendBus = bus(SN_Motors);
				} else {
					Serial.print(StrError);
					Serial.println(":json");
				}
				aJson.deleteItem(objectJSON);
				lastMotors = millis();
			}
		}
	}
	//comManager->send();
}
