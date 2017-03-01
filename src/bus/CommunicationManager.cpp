/*
 * CommunicationManager.cpp
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#include "CommunicationManager.h"

CommunicationManager::CommunicationManager() {
	// TODO Auto-generated constructor stub

}

CommunicationManager::~CommunicationManager() {
	// TODO Auto-generated destructor stub
}

bool CommunicationManager::getStringComplete() {
	return bStringComplete;
}

bool CommunicationManager::getReceiving() {
	return bReceiving;
}
void CommunicationManager::setStringComplete(bool complete) {
	bStringComplete = complete;
}
void CommunicationManager::setReceiving(bool receiving) {
	bReceiving = receiving;
}
void CommunicationManager::setup() {
}
void CommunicationManager::send(aJsonObject* objectJSON) {
}
void CommunicationManager::addIncomingChar(char inChar) {
	if (inChar != 0
			&& ((dataBufferLength == 0 && inChar == TrameByteStart)
					|| dataBufferLength != 0)) {
		dataBuffer[dataBufferLength] = inChar;
		if (dataBufferLength + 1 < INBUFFER_SIZE) {
			dataBufferLength += 1;
		}
	}
}
void CommunicationManager::MODULES_question() {
	//measureDC();
	if (millis() > lastSentQuestion + 3000) {
		//printDC();

		aJsonObject* objectJSON = aJson.createObject();
		Serial.print(StrIndent);
		Serial.print("qm:");

		if (objectJSON != NULL) {
			aJson.addItemToObject(objectJSON, "module", aJson.createItem("?"));
			send(objectJSON);
			lastSentQuestion = millis();
		} else {
			Serial.print(StrError);
			Serial.println(":json");
		}
		aJson.deleteItem(objectJSON);
		//freeMem("freeMem");
	}
}
aJsonObject* CommunicationManager::processJSon() {
	aJsonObject* root = NULL;
	if (getStringComplete()) {
		root = aJson.parse(dataBuffer);
		for (int i = 0; i < dataBufferLength; i++) {
			Serial.print(dataBuffer[i]);
		}
		Serial.println(".");
		dataBufferLength = 0;
		setStringComplete(false);         // notify that the buffer is treated

		Serial.print(millis());
		if (busCom == busSPI) {
			Serial.print(" SPI>");
		} else {
			Serial.print(" RS485>");
		}
	}
	return root;
}
