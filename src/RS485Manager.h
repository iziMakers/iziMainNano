/*
 * RS485Manager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_RS485MANAGER_H_
#define SRC_RS485MANAGER_H_

#include "CommunicationManager.h"
#include <SoftwareSerial.h>

class RS485Manager: private SoftwareSerial, public CommunicationManager {
public:
	RS485Manager(uint8_t receivePin, uint8_t transmitPin, uint8_t rePin = 4,
			uint8_t dePin = 5, long baudrate = 9600, bool inverse_logic =
			false);
	virtual ~RS485Manager();

	void setup();
	void send();
	void addIncomingChar(char inChar);
	void MODULES_question();

	void setRX();
	void setTX();
	void RS484_read();



private:
	uint8_t rePin;
	uint8_t dePin;
	long baudrate;   // 115200  57600 9600
	unsigned long RS485_lastRecevied = 0;





};

#endif /* SRC_RS485MANAGER_H_ */
