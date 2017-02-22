/*
 * Joystick.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Joystick.h"

Joystick::Joystick() {
	// TODO Auto-generated constructor stub

}

Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
}

int Joystick::getJ1X() {
	//process();
	return JOYSTICKS_J1X;
}
int Joystick::getJ1Y() {
	//process();
	return JOYSTICKS_J1Y;
}
int Joystick::getJ1SW() {
	//process();
	return JOYSTICKS_J1SW;
}

void Joystick::processInput(aJsonObject* root) {
	Serial.print(StrIndent);
	Serial.println("Jin");
	int value;
	if (root != NULL) {
		value = getValueInt(root, "JX");
		if (value != NULL) {
			JOYSTICKS_J1X = value;
			lastReading = millis();
		}
		value = getValueInt(root, "JY");
		if (value != NULL) {
			JOYSTICKS_J1Y = value;
			lastReading = millis();
		}
		value = getValueInt(root, "JSW");
		if (value != NULL) {
			JOYSTICKS_J1SW = value;
			lastReading = millis();
		}
	} else {
		Serial.print(StrError);
		Serial.println(":");
	}
	aJson.deleteItem(root);
}

void Joystick::processOutput() {
	if (!1/*sendOutput*/) {
		if (millis() > lastWriting + 300) {
			aJsonObject* objectJSON = aJson.createObject();
			aJson.addItemToObject(objectJSON, "sn",
					aJson.createItem((int) getSerialNumber()));
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
				//sendOutput = true;
				//sendBus = bus(SN_Joystick);
				Serial.println(":ok");
			} else {
				Serial.print(StrError);
				Serial.println(":");
			}
			aJson.deleteItem(objectJSON);
			//freeMem("freeMem");
		}
		lastReading = millis();
	}
}
