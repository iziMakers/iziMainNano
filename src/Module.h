/*
 * Module.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULE_H_
#define SRC_MODULE_H_

#include <arduino.h>
#include "aJSON.h"
#include "Aspect.h"

enum ModuleType {
	mtWrong, mtJoystick, mtMotor, mtUltrasonic, mtColorSensor, mtServo, mtPixel
};
enum BusCommunication {
	bcWrong, bcSPI, bcRS485
};

class Module {
public:
	Module(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong);
	virtual ~Module();
	virtual void processInput(aJsonObject* root);
	virtual void processOutput();
	ModuleType getType();
	BusCommunication getBusCom();
	unsigned long getSerialNumber();
	unsigned long getLastReading();
	void setLastReading(unsigned long date);

protected:
	int getValueInt(aJsonObject* root, const char * id);
	ModuleType mt;
	BusCommunication busCom;
	unsigned long serialNumber = 0;
	unsigned long lastReading = 0;
	unsigned long lastWriting = 0;
	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char inBuffer[INBUFFER_SIZE];
	int inBuffer_i = 0;
	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;

//End TODO
};

#endif /* SRC_MODULE_H_ */
