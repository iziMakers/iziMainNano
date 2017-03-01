/*
 * Module.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_MODULE_H_
#define SRC_MODULES_MODULE_H_

#include <arduino.h>
#include "aJSON.h"
#include "../Enums.h"

class Module {
public:
	Module(ModuleType mt = mtWrong, unsigned long serialNumber = 0,
			unsigned long lastReading = 0,
			aJsonObject* root = NULL);
	virtual ~Module();

	void processJsonInput(aJsonObject* root);
	void processSpecificInput(aJsonObject* root);
	aJsonObject* sendJson();

	ModuleType getType();
	unsigned long getSerialNumber();
	unsigned long getLastReading();
	void setLastReading(unsigned long date);
	unsigned long getLastWriting();
	void setLastWriting(unsigned long date);

	//TODO to delete i think
	String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";
	char TrameByteStart = '{';
	char TrameByteEnd = '}';
	//End TODO

protected:
	ModuleType mt; // not used
	unsigned long serialNumber;
	unsigned long lastReading;
	unsigned long lastWriting = 0;

	int getValueInt(aJsonObject* root, const char * id);
	void sendOutput(aJsonObject* objectJSON);
	void setFromJson(int id, int value) {
	}
	;
	aJsonObject* toJson() {
		return NULL;
	}
	;
};

#endif /* SRC_MODULES_MODULE_H_ */
