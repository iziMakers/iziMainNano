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

class RS485Manager {
public:
	RS485Manager();
	virtual ~RS485Manager();

#define BUS_RS485   1

#define RS485_PIN_RX  2
#define RS485_PIN_TX  6
#define RS485_PIN_RE  4
#define RS485_PIN_DE  5

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	SoftwareSerial RS485_Serial;
	long RS485_baudrate = 9600;   // 115200  57600

	char RS485_inBuffer[INBUFFER_SIZE];
	int RS485_inBuffer_i = 0;

	boolean RS485_stringComplete = false;  // whether the string is complete
	boolean RS485_receiving = false;

	unsigned long RS485_lastSent = 0;
	unsigned long RS485_lastRecevied = 0;

	void setup();

	void setRX();

	void setTX();

	void addIncomingChar(char inChar);

	void read();
	void send();

	void MODULES_question();



};

#endif /* SRC_RS485MANAGER_H_ */
