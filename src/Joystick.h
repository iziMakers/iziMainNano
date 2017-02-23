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
	Joystick(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Joystick();

	void processInput(aJsonObject* root);
	void processOutput();

	int getAxeX();
	int getAxeY();
	bool isPressed();


private:
	int axeX = 0;
	int axeY = 0;
	bool buttonState = false;
};

#endif /* SRC_JOYSTICK_H_ */
