/*
 * Ultrasonic.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_ULTRASONIC_H_
#define SRC_MODULES_ULTRASONIC_H_

#include "Module.h"

class Ultrasonic: public Module {
public:
	Ultrasonic(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Ultrasonic();

	int getDistanceCm();
	int getDistanceInch();

	void processSpecificInput(aJsonObject* root);
	void processOutput();

private:
	int distanceCm = 0;

};

#endif /* SRC_MODULES_ULTRASONIC_H_ */
