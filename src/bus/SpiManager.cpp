/*
 * SpiManager.cpp
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#include "SpiManager.h"

SpiManager::SpiManager() {
	busCom = busSPI;
}

SpiManager::~SpiManager() {
}

void SpiManager::setup() {
	beginSlaveTransaction();
}

void SpiManager::endRX() {
	bReceiving = false;
	if (dataBufferLength > 0) {
		bStringComplete = true;
	}
	lastRxEnd = millis();
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

void SpiManager::send(aJsonObject* objectJSON) {
	if (bReceiving && digitalRead(SPI_SSinterruptPin) == HIGH) {
		endRX();
	}

	if (!bReceiving && (millis() > lastRxEnd + 2) && (millis() > lastTxEnd + 10)
			&& digitalRead(SPI_SSinterruptPin) == HIGH) {

		if (objectJSON != NULL) {

			beginMasterTransaction();
			// enable Slave Select
			digitalWrite(SS, LOW);

			Serial.print("SPI<");

			char* msg = aJson.print(objectJSON);
			int i = 0;
			while (*(msg + i) != '\0') {
				transferAndWait(*(msg + i));
				i += 1;
			}
			free(msg);
			//freeMem("freeMem");
			// disable Slave Select
			digitalWrite(SS, HIGH);
			beginSlaveTransaction();

			lastTxEnd = millis();
			Serial.println(":ok");
		} else {
			Serial.print(StrError);
			Serial.println(":json");
		}
	}
}

