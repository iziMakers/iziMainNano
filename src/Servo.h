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
	Servo();
	virtual ~Servo();

	void processOutput();
	int SN_Servos = 102;

	int SERVOS_Val[5] = { 0, 0, 0, 0, 0 };
	int SERVOS_Val_target[5] = { 0, 0, 0, 0, 0 };
	unsigned long SERVOS_last = 0;
};

#endif /* SRC_SERVO_H_ */
