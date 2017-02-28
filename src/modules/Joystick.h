/*
 * Joystick.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_JOYSTICK_H_
#define SRC_MODULES_JOYSTICK_H_

#include "Module.h"

class Joystick: public Module {
public:
	Joystick(unsigned long serialNumber = 0, CommunicationManager* comManager =
	NULL, unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Joystick();

	void sendJson();

	int getAxeX();
	int getAxeY();bool isPressed();

private:
	char* parameterNames[4] = { "sn", "JX", "JY", "JSW" };
	int axeX = 0;
	int axeY = 0;bool buttonState = false;

	void processSpecificInput(aJsonObject* root);
	void setFromJson(int id, int value);
	aJsonObject* toJson();
};

#endif /* SRC_MODULES_JOYSTICK_H_ */
