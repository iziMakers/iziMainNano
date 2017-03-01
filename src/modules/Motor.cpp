/*
 * Motor.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Motor.h"

Motor::Motor(unsigned long serialNumber, unsigned long lastReading,
		aJsonObject* root) :
		Module(mtMotor, serialNumber, lastReading, root) {
}

Motor::~Motor() {
}

void Motor::processSpecificInput(aJsonObject* root) {
	Serial.print("Min");
	int value;
	for (int i = 1; i < 3; i++) {
		value = getValueInt(root, parameterNames[i]);
		setFromJson(i, value);
	}
}

void Motor::setFromJson(int id, int value) {
	if (value != NULL) {
		switch (id) {
		case 0:
			// serialNumber;
			break;
		case 1:
			motorA_speed = value;
			break;
		case 2:
			motorB_speed = value;
			break;
		default:
			// error
			return;
		}
		lastReading = millis();
	}
}

void Motor::sendJson() {
	if (motorA_speed != motorA_speed_target || motorB_speed != motorB_speed_target
			|| (millis() >= lastWriting + 100)) {

		aJsonObject* objectJSON = toJson();
		Serial.print(StrIndent);
		Serial.print("Mout:");
		sendOutput(objectJSON);
		aJson.deleteItem(objectJSON);
		lastWriting = millis();
	}
}
aJsonObject* Motor::toJson() {
	aJsonObject* objectJSON = aJson.createObject();
	aJson.addItemToObject(objectJSON, parameterNames[0],
			aJson.createItem((int) getSerialNumber()));
	aJson.addItemToObject(objectJSON, parameterNames[1],
			aJson.createItem(motorA_speed_target));
	aJson.addItemToObject(objectJSON, parameterNames[2],
			aJson.createItem(motorB_speed_target));

	return objectJSON;
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
