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
#include "../bus/CommunicationManager.h"

//#include "Aspect.h"

class Module {
public:
	Module(ModuleType mt = mtWrong, CommunicationManager* comManager = NULL,
			unsigned long serialNumber = 0, unsigned long lastReading = 0,
			aJsonObject* root = NULL);
	virtual ~Module();
	virtual void processJsonInput(aJsonObject* root);
	virtual void processSpecificInput(aJsonObject* root);
	virtual void sendJson();
	ModuleType getType();
	unsigned long getSerialNumber();
	void setcomManager(CommunicationManager* comManager);
	unsigned long getLastReading();
	void setLastReading(unsigned long date);
	unsigned long getLastWriting();
	void setLastWriting(unsigned long date);

protected:
	ModuleType mt; // not used
	CommunicationManager* comManager;
	unsigned long serialNumber;
	unsigned long lastReading;
	unsigned long lastWriting = 0;
	//TODO to delete i think
	//String StrModule = "module";
	String StrIndent = "  ";
	String StrError = "err";
	//End TODO

	int getValueInt(aJsonObject* root, const char * id);
	void sendOutput(aJsonObject* objectJSON);
	virtual void setFromJson(int id, int value) {
	}
	;
	virtual aJsonObject* toJson() {
		return NULL;
	}
	;
};

#endif /* SRC_MODULES_MODULE_H_ */
