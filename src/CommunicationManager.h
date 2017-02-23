/*
 * CommunicationManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_COMMUNICATIONMANAGER_H_
#define SRC_COMMUNICATIONMANAGER_H_

#include <arduino.h>
#include "aJSON.h"

class CommunicationManager {
public:
	CommunicationManager();
	virtual ~CommunicationManager();bool getStringComplete();bool getReceiving();
	virtual void setup();
	virtual void send();
	virtual void addIncomingChar(char inChar);
	virtual void MODULES_question();

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char inBuffer[INBUFFER_SIZE];
	int inBuffer_i = 0;
	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;
	char dataBuffer[INBUFFER_SIZE];
	int dataBufferLength = 0;
	boolean bStringComplete = false;  // whether the string is complete
	boolean bReceiving = false;

protected:

	unsigned long lastSentQuestion = 0;
	unsigned long RS485_lastRecevied = 0;

	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";

	char TrameByteStart = '{';
	char TrameByteEnd = '}';
#define BUS_RS485   1
#define BUS_SPI     2
	//End TODO

};

#endif /* SRC_COMMUNICATIONMANAGER_H_ */
