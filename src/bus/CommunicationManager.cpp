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
void CommunicationManager::send() {
}
void CommunicationManager::addIncomingChar(char inChar) {
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
			char* msg = aJson.print(objectJSON);
			//char* msg = "\"{\"module\":\"?\"}";
			//Serial.println(msg);

			int i = 0;
			while (*(msg + i) != '\0') {
				outBuffer[i] = *(msg + i);
				Serial.print(outBuffer[i]);
				i += 1;
			}
			outBuffer_len = i;
			send();
			lastSentQuestion = millis();
			free(msg);

			//Serial.print("len:");
			Serial.println(outBuffer_len);
		} else {
			Serial.print(StrError);
			Serial.println(":json");
		}
		aJson.deleteItem(objectJSON);
		//freeMem("freeMem");
	}
}
