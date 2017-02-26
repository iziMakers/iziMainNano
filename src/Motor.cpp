/*
 * Motor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Motor.h"

Motor::Motor(ModuleType mt, BusCommunication busCom,
		CommunicationManager* comManager, unsigned long serialNumber,
		unsigned long lastReading, aJsonObject* root) :
		Module(mt, busCom, comManager, serialNumber, lastReading, root) {
}

Motor::~Motor() {
}

void Motor::processSpecificInput(aJsonObject* root) {
	Serial.print("Min");
	int value;
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
}

void Motor::processOutput() {
	if (!1/*sendOutput*/) {
		if (motorA_speed != motorA_speed_target
				|| motorB_speed != motorB_speed_target
				|| (millis() >= lastWriting + 100)) {
			aJsonObject* objectJSON = aJson.createObject();
			aJson.addItemToObject(objectJSON, "sn",
					aJson.createItem((int) getSerialNumber()));
			aJson.addItemToObject(objectJSON, "a",
					aJson.createItem(motorA_speed_target));
			aJson.addItemToObject(objectJSON, "b",
					aJson.createItem(motorB_speed_target));

			Serial.print(StrIndent);
			Serial.print("Mout:");
			sendOutput(objectJSON);
			aJson.deleteItem(objectJSON);
			lastWriting = millis();
		}
	}
}

int Motor::getMotorA_speed() {
	return motorA_speed;
}
int Motor::getMotorA_speed_target() {
	return motorA_speed_target;
}
int Motor::getMotorB_speed() {
	return motorB_speed;
}
int Motor::getMotorB_speed_target() {
	return motorB_speed_target;
}

void Motor::setMotorA_speed_target(int value) {
	motorA_speed_target = value;
}
void Motor::setMotorB_speed_target(int value) {
	motorB_speed_target = value;
}
