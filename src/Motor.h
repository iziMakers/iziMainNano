/*
 * Motor.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_
#include "Module.h"

class Motor: public Module {
public:
	Motor(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Motor();

	void processInput(aJsonObject* root);
	void processOutput();

	int getMotorA_speed();
	int getMotorA_speed_target();
	int getMotorB_speed();
	int getMotorB_speed_target();

	void setMotorA_speed_target(int value);
	void setMotorB_speed_target(int value);

private:
	int motorA_speed = 0;
	int motorA_speed_target = 0;
	int motorB_speed = 0;
	int motorB_speed_target = 0;
};

#endif /* SRC_MOTOR_H_ */
