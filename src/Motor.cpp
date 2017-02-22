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

void Motor::processInput(unsigned long SN) {
	if (isKnown(SN_Motors)) {
		if (SN > 0) {
			if (SN == SN_Motors) {
				aJsonObject* root = aJson.parse(inBuffer);
				if (root != NULL) {
					//aJsonObject* obj;
					//obj = aJson.getObjectItem(root, "a");
					if (aJson.getObjectItem(root, "a") != NULL) {
						motorA_speed = aJson.getObjectItem(root, "a")->valueint;
						lastMotors = millis();

						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("a:");
						Serial.println(motorA_speed);
					}
					//aJsonObject* b_ = aJson.getObjectItem(root, "b");
					if (aJson.getObjectItem(root, "b") != NULL) {
						motorB_speed = aJson.getObjectItem(root, "b")->valueint;
						lastMotors = millis();

						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("b:");
						Serial.println(motorB_speed);
					}
				} else {
					Serial.print(StrError);
					Serial.println(":Min");
				}
				aJson.deleteItem(root);
			}
		}
	}
}

void Motor::processOutput() {
	if (!sendOutput) {
		if (isKnown(SN_Motors)) {
			if (motorA_speed != motorA_speed_target
					|| motorB_speed != motorB_speed_target
					|| (millis() >= lastMotors + 1000)) {
				if (millis() >= lastMotors + 100) {
					Serial.print(StrIndent);
					Serial.print("Mout:");
					aJsonObject* objectJSON = aJson.createObject();
					if (objectJSON != NULL) {
						aJson.addItemToObject(objectJSON, "sn",
								aJson.createItem(SN_Motors));
						aJson.addItemToObject(objectJSON, "a",
								aJson.createItem(motorA_speed_target));
						aJson.addItemToObject(objectJSON, "b",
								aJson.createItem(motorB_speed_target));
						char* msg = aJson.print(objectJSON);
						Serial.print(msg);
						int i = 0;
						while (*(msg + i) != '\0') {
							outBuffer[i] = *(msg + i);
							i += 1;
						}
						outBuffer_len = i;
						Serial.print(":");
						Serial.println(outBuffer_len);
						free(msg);

						//freeMem("freeMem");
						sendOutput = true;
						sendBus = bus(SN_Motors);
					} else {
						Serial.print(StrError);
						Serial.println(":json");
					}
					aJson.deleteItem(objectJSON);
					lastMotors = millis();
				}
			}
		}
	}
}
