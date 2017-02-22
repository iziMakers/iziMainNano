/*
 * Servo.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Servo.h"
#include <arduino.h>

Servo::Servo() {
	// TODO Auto-generated constructor stub

}

Servo::~Servo() {
	// TODO Auto-generated destructor stub
}

void Servo::processOutput() {
	if (!1/*sendOutput*/) {
		boolean new_val = false;
		for (int iiii = 0; iiii < 5; iiii++) {
			if (SERVOS_Val[iiii] != SERVOS_Val_target[iiii]) {
				new_val = true;
			}
		}

		if (new_val) { // || (millis() >= SERVOS_last + 1000)) {
			if (millis() >= SERVOS_last + 10) {
				Serial.print(StrIndent);
				Serial.print("Sout:");
				aJsonObject* objectJSON = aJson.createObject();
				if (objectJSON != NULL) {
					aJson.addItemToObject(objectJSON, "sn", aJson.createItem(SN_Servos));

					char buf[2];
					for (int iiii = 0; iiii < 5; iiii++) {
						if (SERVOS_Val[iiii] != SERVOS_Val_target[iiii]) {
							itoa(iiii + 1, buf, 10);
							aJson.addItemToObject(objectJSON, buf,
									aJson.createItem(SERVOS_Val_target[iiii]));

							SERVOS_Val[iiii] = SERVOS_Val_target[iiii];
						}
					}

					char* msg = aJson.print(objectJSON);
					Serial.print(msg);
					int i = 0;
					while (*(msg + i) != '\0') {
						outBuffer[i] = *(msg + i);
						i += 1;
					}
					outBuffer_len = i;
					Serial.print(":");
					Serial.println(outBuffer_len);
					free(msg);

					//freeMem("freeMem");
					//sendOutput = true;
					//sendBus = bus(SN_Servos);
				} else {
					Serial.print(StrError);
					Serial.println(":json");
				}
				aJson.deleteItem(objectJSON);
				SERVOS_last = millis();
			}
		}
	}
}
