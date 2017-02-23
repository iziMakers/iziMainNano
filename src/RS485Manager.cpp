/*
 * RS485Manager.cpp
 *
 *  Created on: 22 f�vr. 2017
 *      Author: Bruno
 */

#include "RS485Manager.h"
#include <arduino.h>

#include <SoftwareSerial.h>

RS485Manager::RS485Manager(uint8_t receivePin, uint8_t transmitPin,
		uint8_t rePin, uint8_t dePin, long baudrate,
		bool inverse_logic) :
		SoftwareSerial(receivePin, transmitPin, inverse_logic), rePin(rePin), dePin(
				dePin), baudrate(baudrate) {

}

RS485Manager::~RS485Manager() {
	// TODO Auto-generated destructor stub
}

void RS485Manager::setup() {
	// set the data rate for the SoftwareSerial port
	begin(baudrate);
	//RS485_Serial.println("Hello, world?");

	pinMode(rePin, OUTPUT);
	pinMode(dePin, OUTPUT);
	setRX();
}

void RS485Manager::setRX() {
	digitalWrite(rePin, LOW);
	digitalWrite(dePin, LOW);
}

void RS485Manager::setTX() {
	digitalWrite(rePin, HIGH);
	digitalWrite(dePin, HIGH);
}

void RS485Manager::addIncomingChar(char inChar) {
	//receiving = true;

	if (inChar != 0) {
		if (dataBufferLength == 0) {
			if (inChar == TrameByteStart) {
				dataBuffer[dataBufferLength] = inChar;
				if (dataBufferLength + 1 < INBUFFER_SIZE) {
					dataBufferLength += 1;
				}
			}
		} else {
			dataBuffer[dataBufferLength] = inChar;
			if (dataBufferLength + 1 < INBUFFER_SIZE) {
				dataBufferLength += 1;
				//inBuffer[inBuffer_i] = 0;
				//receiving = true;
			}
		}
	}
}

void RS485Manager::RS484_read() {
	if (available()) {
		//digitalWrite(PIN_LED, HIGH);

		if (bReceiving) {
			Serial.println("RX not finished");
		}

		memset(dataBuffer, (char) 0, INBUFFER_SIZE);
		dataBufferLength = 0;
		bStringComplete = false;

		Serial.print("[");
		while (available()) {
			bReceiving = true;
			// get the new byte:
			char inChar = (char) read();
			Serial.write(inChar);
			// add it to the inputString:
			//inputString += inChar;
			if (inChar != '\n') {
				//Serial.write(inChar);
				addIncomingChar(inChar);
			}
			// if the incoming character is a newline, set a flag
			// so the main loop can do something about it:
			if (inChar == '\n') {
				bStringComplete = true;
				bReceiving = false;
				//Serial.println("> " + inputString);
				//Serial.println("> " + String(inBuffer));

				Serial.write(']');
				/*Serial.write('>');
				 Serial.write(' ');
				 for (int i = 0 ; i < inBuffer_i ; i++) {
				 Serial.write(inBuffer[i]);
				 }
				 Serial.write('\n');
				 */

				//receiveBus = BUS_RS485;
			}

			if (!available()) {
				// on se laisse une chance de récupérer d'autres caractères
				// à 9600 bauds, 1 octet prend 100us
				delayMicroseconds(200);
			}
		}
		RS485_lastRecevied = millis();

		if (bReceiving) {
			bReceiving = false;
			Serial.print("RX not finished properly:");
			Serial.print(inBuffer_i);
			Serial.print(":");
			for (int i = 0; i < inBuffer_i; i++) {
				Serial.write(inBuffer[i]);
			}
			Serial.write('\n');

			dataBufferLength = 0;
		}

		//digitalWrite(PIN_LED, LOW);
	}
}

void RS485Manager::send() {
	if (1/*sendOutput*/) {
		if (!bReceiving) {
			if (!available()) {

				//digitalWrite(PIN_LED, HIGH);

				//Serial.println("< " + outputString);
				//Serial.println("< " + String(outBuffer));

				/*for(int i = 0 ; i < outBuffer_len ; i++) {
				 Serial.write(outBuffer[i]);
				 }
				 Serial.write('\n');*/

				setTX();

				Serial.print("RS485<");
				//Serial.write('<');
				//Serial.write(' ');
				//RS485_Serial.println(String(outBuffer));
				for (int i = 0; i < outBuffer_len; i++) {
					write(outBuffer[i]);
					Serial.write(outBuffer[i]);
				}
				write('\n');
				Serial.write('\n');

				delay(1);

				setRX();

				//outputString = "";
				//sendOutput = false;

				//digitalWrite(PIN_LED, LOW);
			} else {
				Serial.println("Cannot send");
			}
		} else {
			Serial.println("Cannot send");

			if (millis() - RS485_lastRecevied > 100) {
				bReceiving = false;
			}
		}
	}
}

void RS485Manager::MODULES_question() {
	if (!1/*sendOutput*/) {
		//measureDC();
		if (millis() > lastSentQuestion + 3100) {
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
				free(msg);
				//sendOutput = true;
				//sendBus = BUS_RS485;      // BUS_RS485

				lastSentQuestion = millis();
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
}
