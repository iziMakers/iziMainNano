/*
 * SpiManager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_SPIMANAGER_H_
#define SRC_SPIMANAGER_H_

#include <arduino.h>
#include "aJSON.h"

class SpiManager {
public:
	SpiManager();
	virtual ~SpiManager();

	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";

	char TrameByteStart = '{';
	char TrameByteEnd = '}';

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char inBuffer[INBUFFER_SIZE];
	int inBuffer_i = 0;
	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;

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

#define NB_MODULES_MAX    3

	int nb_modules = 0;
	unsigned long modules_SN[NB_MODULES_MAX];
	unsigned long modules_last[NB_MODULES_MAX];
	String modules_Types[NB_MODULES_MAX] = { };
	int modules_Bus[NB_MODULES_MAX];      // BUS_RS485 , BUS_SPI

//End TODO



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
