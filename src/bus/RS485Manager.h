/*
 * RS485Manager.h
 *
 *  Created on: 22 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_BUS_RS485MANAGER_H_
#define SRC_BUS_RS485MANAGER_H_

#include <SoftwareSerial.h>
#include "CommunicationManager.h"

class RS485Manager: private SoftwareSerial, public CommunicationManager {
public:
	RS485Manager(uint8_t receivePin, uint8_t transmitPin, uint8_t rePin = 4,
			uint8_t dePin = 5, long baudrate = 9600, bool inverse_logic =
			false);
	virtual ~RS485Manager();

	void setup();
	void send(aJsonObject*);

	void setRxMode();
	void setTxMode();
	void RS484_read();



private:
	uint8_t rePin;
	uint8_t dePin;
	long baudrate;   // 115200  57600 9600






};

#endif /* SRC_BUS_RS485MANAGER_H_ */
