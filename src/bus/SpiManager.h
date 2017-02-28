/*
 * SpiManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_BUS_SPIMANAGER_H_
#define SRC_BUS_SPIMANAGER_H_

#include "CommunicationManager.h"

class SpiManager: public CommunicationManager {
public:
	SpiManager();
	virtual ~SpiManager();

	void setup();
	void send();
	void addIncomingChar(char inChar);

	const byte SPI_SSinterruptPin = 3;
	const byte SPI_delayMicroBetweenByte = 7;

	//normally in private
	void endRX();

private:

	byte transferAndWait(const byte value);
	void beginMasterTransaction();
	void beginSlaveTransaction();

	unsigned long lastRxStart = 0;
	unsigned long lastRxEnd = 0;
	unsigned long lastTxEnd = 0;

};

#endif /* SRC_BUS_SPIMANAGER_H_ */
