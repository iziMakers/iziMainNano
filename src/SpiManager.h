/*
 * SpiManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_SPIMANAGER_H_
#define SRC_SPIMANAGER_H_

#include <arduino.h>

class SpiManager {
public:
	SpiManager();
	virtual ~SpiManager();

#define INBUFFER_SIZE         128
#define BUS_SPI     2

	char SPI_inBuffer[INBUFFER_SIZE];
	int SPI_inBuffer_i = 0;

	boolean SPI_stringComplete = false;   // whether the string is complete
	boolean SPI_receiving = false;

	unsigned long SPI_lastSent = 0;

//int inputMesureDC = 0;
//int inputMesureDC_x = 5045;      // multiplicateur pour obtenir des mV

	unsigned long SPI_RX_start_ms = 0;
	unsigned long SPI_RX_end_ms = 0;
	unsigned long SPI_TX_end_ms = 0;

	long SPI_lastUpdate = 0;
	const byte SPI_SSinterruptPin = 3;

	const byte SPI_delayMicroBetweenByte = 7;



	void setup();
	void ssChange();
	void endRX();
	byte transferAndWait(const byte value);
	void beginMasterTransaction();
	void beginSlaveTransaction();
	void send();
	void addIncomingChar(char inChar);
	void MODULES_question();
};

#endif /* SRC_SPIMANAGER_H_ */
