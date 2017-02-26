/*
 * ColorSensor.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_COLORSENSOR_H_
#define SRC_COLORSENSOR_H_
#include "Module.h"

class ColorSensor: public Module {
public:
	ColorSensor(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~ColorSensor();
	int getH();
	int getS();
	int getV();
	int getP();
	void processSpecificInput(aJsonObject* root);

private:
	int red = 0;
	int green = 0;
	int blue = 0;
	int hue = 0;
	int saturation = 0;
	int iValue = 0;
	int preset = 0; // O:back 1:white 2:red 3:orange 4:yellow 5:lime 6:green 7:turquoise 8:cyan 9:cobalt 10:blue 11:violet 12:magenta 13:crimson
};

#endif /* SRC_COLORSENSOR_H_ */
