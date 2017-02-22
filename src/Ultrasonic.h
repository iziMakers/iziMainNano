/*
 * Ultrasonic.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_

#include "Module.h"

class Ultrasonic: public Module {
public:
	Ultrasonic();
	virtual ~Ultrasonic();

	int getUltrasonic();

	int getUltrasonic_inch();

	void processInput(unsigned long SN);

	int SN_Ultrasonic = 101;

	int ultrasonic_cm = 0;
	unsigned long lastUltrasonic = 0;


};

#endif /* SRC_ULTRASONIC_H_ */
