/*
 * RS485Manager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_RS485MANAGER_H_
#define SRC_RS485MANAGER_H_

#include <arduino.h>
#include <SoftwareSerial.h>
#include "aJSON.h"

class RS485Manager: private SoftwareSerial {
public:
	RS485Manager(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic =
			false);
	virtual ~RS485Manager();

#define BUS_RS485   1

#define RS485_PIN_RE  4
#define RS485_PIN_DE  5

	void setup();
	void setRX();
	void setTX();
	void addIncomingChar(char inChar);
	void RS484_read();
	void send();
	void MODULES_question();
	long RS485_baudrate = 9600;   // 115200  57600

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

	char RS485_inBuffer[INBUFFER_SIZE];
	int RS485_inBuffer_i = 0;

	boolean RS485_stringComplete = false;  // whether the string is complete
	boolean RS485_receiving = false;

	unsigned long RS485_lastSent = 0;
	unsigned long RS485_lastRecevied = 0;



#define NB_MODULES_MAX    3

	int nb_modules = 0;
	unsigned long modules_SN[NB_MODULES_MAX];
	unsigned long modules_last[NB_MODULES_MAX];
	String modules_Types[NB_MODULES_MAX] = { };
	int modules_Bus[NB_MODULES_MAX];      // BUS_RS485 , BUS_SPI

//End TODO



};

#endif /* SRC_RS485MANAGER_H_ */
