/*
 * RS485Manager.cpp
 *
 *  Created on: 22 f�vr. 2017
 *      Author: Bruno
 */

#include "RS485Manager.h"
#include <arduino.h>

#include <SoftwareSerial.h>
RS485Manager::RS485Manager() {
	RS485_Serial(RS485_PIN_RX, RS485_PIN_TX); // RX, TX

}

RS485Manager::~RS485Manager() {
	// TODO Auto-generated destructor stub
}



#define BUS_RS485   1

#define RS485_PIN_RX  2
#define RS485_PIN_TX  6
#define RS485_PIN_RE  4
#define RS485_PIN_DE  5

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

long RS485_baudrate = 9600;   // 115200  57600

char RS485_inBuffer[INBUFFER_SIZE];
int RS485_inBuffer_i = 0;

boolean RS485_stringComplete = false;  // whether the string is complete
boolean RS485_receiving = false;

unsigned long RS485_lastSent = 0;
unsigned long RS485_lastRecevied = 0;

void RS485Manager::setup() {
	// set the data rate for the SoftwareSerial port
	RS485_Serial.begin(RS485_baudrate);
	//RS485_Serial.println("Hello, world?");

	pinMode(RS485_PIN_RE, OUTPUT);
	pinMode(RS485_PIN_DE, OUTPUT);
	setRX();
}

void RS485Manager::setRX() {
	digitalWrite(RS485_PIN_RE, LOW);
	digitalWrite(RS485_PIN_DE, LOW);
}

void RS485Manager::setTX() {
	digitalWrite(RS485_PIN_RE, HIGH);
	digitalWrite(RS485_PIN_DE, HIGH);
}

void RS485Manager::addIncomingChar(char inChar) {
	//receiving = true;

	if (inChar != 0) {
		if (RS485_inBuffer_i == 0) {
			if (inChar == TrameByteStart) {
				RS485_inBuffer[RS485_inBuffer_i] = inChar;
				if (RS485_inBuffer_i + 1 < INBUFFER_SIZE) {
					RS485_inBuffer_i += 1;
				}
			}
		} else {
			RS485_inBuffer[RS485_inBuffer_i] = inChar;
			if (RS485_inBuffer_i + 1 < INBUFFER_SIZE) {
				RS485_inBuffer_i += 1;
				//inBuffer[inBuffer_i] = 0;
				//receiving = true;
			}
		}
	}
}

void RS485Manager::read() {
	if (RS485_Serial.available()) {
		//digitalWrite(PIN_LED, HIGH);

		if (RS485_receiving) {
			Serial.println("RX not finished");
		}

		memset(RS485_inBuffer, (char) 0, INBUFFER_SIZE);
		RS485_inBuffer_i = 0;
		RS485_stringComplete = false;

		Serial.print("[");
		while (RS485_Serial.available()) {
			RS485_receiving = true;
			// get the new byte:
			char inChar = (char) RS485_Serial.read();
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
				RS485_stringComplete = true;
				RS485_receiving = false;
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

			if (!RS485_Serial.available()) {
				// on se laisse une chance de récupérer d'autres caractères
				// à 9600 bauds, 1 octet prend 100us
				delayMicroseconds(200);
			}
		}
		RS485_lastRecevied = millis();

		if (RS485_receiving) {
			RS485_receiving = false;
			Serial.print("RX not finished properly:");
			Serial.print(inBuffer_i);
			Serial.print(":");
			for (int i = 0; i < inBuffer_i; i++) {
				Serial.write(inBuffer[i]);
			}
			Serial.write('\n');

			RS485_inBuffer_i = 0;
		}

		//digitalWrite(PIN_LED, LOW);
	}
}

void RS485Manager::send() {
	if (sendOutput) {
		if (!RS485_receiving) {
			if (!RS485_Serial.available()) {

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
					RS485_Serial.write(outBuffer[i]);
					Serial.write(outBuffer[i]);
				}
				RS485_Serial.write('\n');
				Serial.write('\n');

				delay(1);

				setRX();

				//outputString = "";
				sendOutput = false;

				//digitalWrite(PIN_LED, LOW);
			} else {
				Serial.println("Cannot send");
			}
		} else {
			Serial.println("Cannot send");

			if (millis() - RS485_lastRecevied > 100) {
				RS485_receiving = false;
			}
		}
	}
}

void RS485Manager::MODULES_question() {
	if (!sendOutput) {
		//measureDC();
		if (millis() > RS485_lastSent + 3100) {
			//printDC();

			aJsonObject* objectJSON = aJson.createObject();
			Serial.print(StrIndent);
			Serial.print("qm:");

			if (objectJSON != NULL) {
				aJson.addItemToObject(objectJSON, StrModule, aJson.createItem("?"));
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
				sendOutput = true;
				sendBus = BUS_RS485;      // BUS_RS485

				RS485_lastSent = millis();
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
