/*
 * CommunicationManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_BUS_COMMUNICATIONMANAGER_H_
#define SRC_BUS_COMMUNICATIONMANAGER_H_

#include <arduino.h>
#include "aJSON.h"

//  ENUMS *****************************
const uint8_t busWrong = 0;
const uint8_t busSPI = 1;
const uint8_t busRS485 = 2;

class CommunicationManager {
public:
	CommunicationManager();
	virtual ~CommunicationManager();
	void setup();
	virtual void send(aJsonObject*);
	void addIncomingChar(char);
	void MODULES_question();
	aJsonObject* processJSon();

	bool getStringComplete();bool getReceiving();
	void setStringComplete(bool);
	void setReceiving(bool);

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;
	char dataBuffer[INBUFFER_SIZE];
	int dataBufferLength = 0;

protected:

	uint8_t busCom = busWrong;
	unsigned long lastSentQuestion = 0;
	unsigned long lastRxEnd = 0;
	unsigned long lastTxEnd = 0;

	bool bStringComplete = false;  // whether the string is complete
	bool bReceiving = false;

	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";
	char TrameByteStart = '{';
	char TrameByteEnd = '}';
	//End TODO

};

#endif /* SRC_BUS_COMMUNICATIONMANAGER_H_ */
