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

void SpiManager::send() {
	if (bReceiving) {
		if (digitalRead(SPI_SSinterruptPin) == HIGH) {
			if (millis() > lastRxStart + 10) {
				Serial.print(StrIndent);
				Serial.println("SPI end RX");
				endRX();
				//receiving = false;
			}
		}
	}

	if (!bReceiving) {
		if (millis() > lastRxEnd + 2) {
			if (millis() > lastTxEnd + 10) {
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
					lastTxEnd = millis();
				}
			}
		}
	}
}

void SpiManager::addIncomingChar(char inChar) {
	if (inChar != 0
			&& ((dataBufferLength == 0 && inChar == TrameByteStart)
					|| dataBufferLength != 0)) {
		dataBuffer[dataBufferLength] = inChar;
		if (dataBufferLength + 1 < INBUFFER_SIZE) {
			dataBufferLength += 1;
		}
	}
	lastRxStart = millis();
}
