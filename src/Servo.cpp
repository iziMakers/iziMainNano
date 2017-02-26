/*
 * Servo.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Servo.h"

Servo::Servo(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		Module(mt, busCom, comManager, serialNumber, lastReading, root) {
}

Servo::~Servo() {
}

void Servo::processOutput() {
	if (!1/*sendOutput*/) {
		boolean new_val = false;
		for (int iiii = 0; iiii < 5; iiii++) {
			if (servoAngles[iiii] != servoTargetAngles[iiii]) {
				new_val = true;
			}
		}

		if (new_val) { // || (millis() >= lastWirting + 1000)) {
			if (millis() >= lastReading + 10) {
				Serial.print(StrIndent);
				Serial.print("Sout:");
				aJsonObject* objectJSON = aJson.createObject();
				aJson.addItemToObject(objectJSON, "sn",
						aJson.createItem((int) getSerialNumber()));
				char buf[2];
				for (int iiii = 0; iiii < 5; iiii++) {
					if (servoAngles[iiii] != servoTargetAngles[iiii]) {
						itoa(iiii + 1, buf, 10);
						aJson.addItemToObject(objectJSON, buf,
								aJson.createItem(servoTargetAngles[iiii]));

						servoAngles[iiii] = servoTargetAngles[iiii];
					}
				}

				sendOutput(objectJSON);
				aJson.deleteItem(objectJSON);
				lastWriting = millis();
			}
		}
	}
}

void Servo::setServoAngle(uint8_t id, uint8_t angle) {
	if (angle >= 180) {
		angle = 180;
	} else if (angle < 0) {
		angle = 0;
	}
	servoTargetAngles[id] = angle;
}
uint8_t Servo::getServoTargetAngle(uint8_t id) {
	return servoTargetAngles[id];
}
uint8_t Servo::getServoAngle(uint8_t id) {
	return servoAngles[id];
}
