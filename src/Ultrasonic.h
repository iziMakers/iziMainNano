/*
 * Ultrasonic.h
 *
 *  Created on: 21 f�vr. 2017
 *      Author: Bruno
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_

#include "Module.h"

class Ultrasonic: public Module {
public:
	Ultrasonic(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Ultrasonic();

	int getDistanceCm();
	int getDistanceInch();

	void processInput(aJsonObject* root);
	void processOutput();

private:
	int distanceCm = 0;

};

#endif /* SRC_ULTRASONIC_H_ */
