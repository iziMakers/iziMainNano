/*
 * Module.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_MODULE_H_
#define SRC_MODULES_MODULE_H_

#include <arduino.h>
#include "aJSON.h"
#include <avr/pgmspace.h>

//  ENUMS *****************************
const uint8_t mtWrong = 0;
const uint8_t mtJoystick = 1;
const uint8_t mtMotor = 2;
const uint8_t mtUltrasonic = 3;
const uint8_t mtColorSensor = 4;
const uint8_t mtServo = 7;
const uint8_t mtPixel = 6;

class Module {
public:
	Module(unsigned long serialNumber = 0, unsigned long lastReading = 0,
			aJsonObject* root = NULL);
	virtual ~Module();

	void processJsonInput(aJsonObject*);
	virtual aJsonObject* sendJson();

	uint8_t getType();
	unsigned long getSerialNumber();
	unsigned long getLastReading();
	void setLastReading(unsigned long);
	unsigned long getLastWriting();
	void setLastWriting(unsigned long);

	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";
	char TrameByteStart = '{';
	char TrameByteEnd = '}';
	//End TODO

protected:
	uint8_t mt; // not used
	unsigned long serialNumber;
	unsigned long lastReading;
	unsigned long lastWriting = 0;

	int getValueInt(aJsonObject* root, const char * id);
	void sendOutput(aJsonObject* objectJSON);
	virtual void processSpecificInput(aJsonObject*);
	virtual void setFromJson(int, int);
	virtual aJsonObject* toJson();
};

#endif /* SRC_MODULES_MODULE_H_ */
