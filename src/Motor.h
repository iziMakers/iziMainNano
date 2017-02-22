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
	Motor();
	virtual ~Motor();

	void processInput(unsigned long SN);
	void processOutput();

	int SN_Motors = 101;

	int motorA_speed = 0;
	int motorA_speed_target = 0;
	int motorB_speed = 0;
	int motorB_speed_target = 0;
	unsigned long lastMotors = 0;
};

#endif /* SRC_MOTOR_H_ */
