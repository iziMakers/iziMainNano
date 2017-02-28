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

class CommunicationManager {
public:
	CommunicationManager();
	virtual ~CommunicationManager();
	virtual void setup();
	virtual void send();
	virtual void addIncomingChar(char inChar);
	virtual void MODULES_question();
	virtual void processJSon();

	bool getStringComplete();bool getReceiving();
	void setStringComplete(bool complete);
	void setReceiving(bool receving);

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char inBuffer[INBUFFER_SIZE];
	int inBuffer_i = 0;
	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;
	char dataBuffer[INBUFFER_SIZE];
	int dataBufferLength = 0;

	aJsonObject* root;

protected:

	unsigned long lastSentQuestion = 0;
	unsigned long lastRxStart = 0;
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
