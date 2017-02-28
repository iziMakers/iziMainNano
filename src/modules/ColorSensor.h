/*
 * ColorSensor.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_COLORSENSOR_H_
#define SRC_MODULES_COLORSENSOR_H_
#include "Module.h"

class ColorSensor: public Module {
public:
	ColorSensor(unsigned long serialNumber = 0, CommunicationManager* comManager =
	NULL, unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~ColorSensor();

	int getH();
	int getS();
	int getV();
	int getP();

private:
	char* parameterNames[5] = { "sn", "H", "S", "V", "P" };
	int red = 0;
	int green = 0;
	int blue = 0;
	int hue = 0;
	int saturation = 0;
	int iValue = 0;
	int preset = 0; // O:back 1:white 2:red 3:orange 4:yellow 5:lime 6:green 7:turquoise 8:cyan 9:cobalt 10:blue 11:violet 12:magenta 13:crimson

	void processSpecificInput(aJsonObject* root);
	void setFromJson(int id, int value);

};

#endif /* SRC_MODULES_COLORSENSOR_H_ */
