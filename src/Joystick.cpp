/*
 * Joystick.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Joystick.h"
#include <arduino.h>

Joystick::Joystick() {
	// TODO Auto-generated constructor stub

}

Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
}


int Joystick::getJ1X() {
	process();
	return JOYSTICKS_J1X;
}
int Joystick::getJ1Y() {
	process();
	return JOYSTICKS_J1Y;
}
int Joystick::getJ1SW() {
	process();
	return JOYSTICKS_J1SW;
}

void Joystick::processInput(unsigned long SN) {
	if (isKnown(SN_Joystick)) {
		if (SN > 0) {
			if (SN == SN_Joystick) {
				Serial.print(StrIndent);
				Serial.print("Jin");
				//Serial.println(inBuffer);

				aJsonObject* root = aJson.parse(inBuffer);
				if (root != NULL) {
					Serial.print("\n");
					//Serial.println("Jin:");
					//Serial.print(inBuffer);
					if (aJson.getObjectItem(root, "JX") != NULL) {
						JOYSTICKS_J1X = (int) aJson.getObjectItem(root, "JX")->valueint;
						JOYSTICKS_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("J1X:");
						Serial.println(JOYSTICKS_J1X);
					}
					if (aJson.getObjectItem(root, "JY") != NULL) {
						JOYSTICKS_J1Y = (int) aJson.getObjectItem(root, "JY")->valueint;
						JOYSTICKS_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("J1Y:");
						Serial.println(JOYSTICKS_J1Y);
					}
					if (aJson.getObjectItem(root, "JSW") != NULL) {
						JOYSTICKS_J1SW = (int) aJson.getObjectItem(root, "JSW")->valueint;
						JOYSTICKS_lastReceived = millis();
						Serial.print(StrIndent);
						Serial.print(StrIndent);
						Serial.print("J1SW:");
						Serial.println(JOYSTICKS_J1SW);
					}
				} else {
					Serial.print(StrError);
					Serial.println(":");
				}
				aJson.deleteItem(root);
			}
		}
	}
}

void Joystick::processOutput() {
	if (!sendOutput) {
		if (millis() > JOYSTICKS_lastReceived + 300) {
			if (isKnown(SN_Joystick)) {
				aJsonObject* objectJSON = aJson.createObject();
				aJson.addItemToObject(objectJSON, "sn", aJson.createItem(SN_Joystick));
				aJson.addItemToObject(objectJSON, "j", aJson.createItem(1));

				Serial.print(StrIndent);
				Serial.print("Jout:");
				if (objectJSON != NULL) {
					char* msg = aJson.print(objectJSON);
					int i = 0;
					while (*(msg + i) != '\0') {
						outBuffer[i] = *(msg + i);
						Serial.write(outBuffer[i]);
						i += 1;
					}
					outBuffer_len = i;
					free(msg);
					sendOutput = true;
					sendBus = bus(SN_Joystick);
					Serial.println(":ok");
				} else {
					Serial.print(StrError);
					Serial.println(":");
				}
				aJson.deleteItem(objectJSON);
				//freeMem("freeMem");
			}
			JOYSTICKS_lastReceived = millis();
		}
	}
}
