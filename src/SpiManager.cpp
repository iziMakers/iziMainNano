/*
 * SpiManager.cpp
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#include "SpiManager.h"

SpiManager::SpiManager() {
	// TODO Auto-generated constructor stub
}

SpiManager::~SpiManager() {
	// TODO Auto-generated destructor stub
}

void SpiManager::setup() {
	beginSlaveTransaction();
	//attachInterrupt(digitalPinToInterrupt(SPI_SSinterruptPin), ssChange, CHANGE); // interrupt for SS rising edge
}

void SpiManager::ssChange() {
	delayMicroseconds(1);
	if (digitalRead(SPI_SSinterruptPin) == HIGH) { // RISING
		if (bReceiving) {
			endRX();
		}
	} else { // FALLING
		bReceiving = true;
	}
}

void SpiManager::endRX() {
	bReceiving = false;
	if (dataBufferLength > 0) {
		bStringComplete = true;
	}
	SPI_RX_end_ms = millis();
}

byte SpiManager::transferAndWait(const byte value) {
	SPDR = value;                     //Load data into the buffer
	//while (!(SPSR & (1 << SPIF) ));   //Wait until transmission complete
	delayMicroseconds(SPI_delayMicroBetweenByte);
	return (SPDR);                    //Return received data
}

void SpiManager::beginMasterTransaction() {
	SPCR |= _BV(MSTR);
	SPCR &= ~_BV(SPIE);
	digitalWrite(MOSI, LOW);
	digitalWrite(SCK, LOW);
	digitalWrite(SS, LOW);
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	pinMode(SS, OUTPUT);
}

void SpiManager::beginSlaveTransaction() {
	pinMode(MISO, OUTPUT);
	SPCR = _BV(SPE);
	SPCR |= _BV(SPIE);
}

void SpiManager::send() {
	if (bReceiving) {
		if (digitalRead(SPI_SSinterruptPin) == HIGH) {
			if (millis() > SPI_RX_start_ms + 10) {
				Serial.print(StrIndent);
				Serial.println("SPI end RX");
				endRX();
				//receiving = false;
			}
		}
	}

	if (!bReceiving) {
		if (millis() > SPI_RX_end_ms + 2) {
			if (millis() > SPI_TX_end_ms + 10) {
				if (digitalRead(SPI_SSinterruptPin) == HIGH) {

					beginMasterTransaction();
					// enable Slave Select
					digitalWrite(SS, LOW);

					Serial.print("SPI<");

					for (int i = 0; i < outBuffer_len; i++) {
						Serial.print(outBuffer[i]);
						//if(i + 1 == outBuffer_len) {
						//Serial.print('\n');
						//}
						transferAndWait(outBuffer[i]);
					}

					// disable Slave Select
					digitalWrite(SS, HIGH);
					beginSlaveTransaction();

					Serial.println("");
					SPI_TX_end_ms = millis();
				}
			}
		}
	}
}

void SpiManager::addIncomingChar(char inChar) {
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
			}
		}
	}
}

void SpiManager::MODULES_question() {
	if (!1/*sendOutput*/) {
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
				free(msg);
				//sendOutput = true;
				//sendBus = BUS_SPI;      // BUS_RS485

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
