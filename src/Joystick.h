/*
 * Joystick.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_JOYSTICK_H_
#define SRC_JOYSTICK_H_

#include "Module.h"

class Joystick: public Module {
public:
	Joystick();
	virtual ~Joystick();

	int getJ1X();
	int getJ1Y();
	int getJ1SW();

	void processInput(aJsonObject* root);
	void processOutput();

	int JOYSTICKS_J1X = 0;
	int JOYSTICKS_J1Y = 0;
	int JOYSTICKS_J1SW = 0;
	int JOYSTICKS_J2X = 0;
	int JOYSTICKS_J2Y = 0;
	int JOYSTICKS_J2SW = 0;
};

#endif /* SRC_JOYSTICK_H_ */
