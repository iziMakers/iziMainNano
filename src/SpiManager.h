/*
 * SpiManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_SPIMANAGER_H_
#define SRC_SPIMANAGER_H_

#include "CommunicationManager.h"

class SpiManager: public CommunicationManager {
public:
	SpiManager();
	virtual ~SpiManager();

	void setup();
	void ssChange();
	void endRX();
	byte transferAndWait(const byte value);
	void beginMasterTransaction();
	void beginSlaveTransaction();
	void send();
	void addIncomingChar(char inChar);
	void MODULES_question();


	unsigned long SPI_RX_start_ms = 0;
	unsigned long SPI_RX_end_ms = 0;
	unsigned long SPI_TX_end_ms = 0;

	const byte SPI_SSinterruptPin = 3;
	const byte SPI_delayMicroBetweenByte = 7;


private:




};

#endif /* SRC_SPIMANAGER_H_ */
