/*
 * Servo.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_SERVO_H_
#define SRC_SERVO_H_
#include "Module.h"


class Servo: public Module {
public:
	Servo(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Servo();

	void processInput(aJsonObject* root);
	void processOutput();

	void setServoAngle(uint8_t id, uint8_t angle);
	uint8_t getServoTargetAngle(uint8_t id); // TODO usefull?
	uint8_t getServoAngle(uint8_t id);

private:
	uint8_t servoAngles[5] = { 0, 0, 0, 0, 0 };
	uint8_t servoTargetAngles[5] = { 0, 0, 0, 0, 0 };
};

#endif /* SRC_SERVO_H_ */
