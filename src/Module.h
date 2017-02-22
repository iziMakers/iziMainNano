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

class Module {
public:
	Module();
	virtual ~Module();
	virtual void processInput();
	virtual void processOutput();

	bool isKnown(unsigned long sn);
	int number(unsigned long sn);
	int bus(unsigned long sn);

protected:
	unsigned long serialNumber;
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

#define NB_MODULES_MAX    3

	int nb_modules = 0;
	unsigned long modules_SN[NB_MODULES_MAX];
	unsigned long modules_last[NB_MODULES_MAX];
	String modules_Types[NB_MODULES_MAX] = { };
	int modules_Bus[NB_MODULES_MAX];      // BUS_RS485 , BUS_SPI

//End TODO
};

#endif /* SRC_MODULE_H_ */
