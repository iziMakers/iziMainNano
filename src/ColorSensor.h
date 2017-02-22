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
	ColorSensor();
	virtual ~ColorSensor();
	void processInput(unsigned long SN);
	int getH();
	int getS();
	int getV();
	int getP();




	int SN_ColorSensor = 102;

	int COLORSENSOR_R = 0;
	int COLORSENSOR_G = 0;
	int COLORSENSOR_B = 0;
	int COLORSENSOR_H = 0;
	int COLORSENSOR_S = 0;
	int COLORSENSOR_V = 0;
	int COLORSENSOR_P = 0; // O:back 1:white 2:red 3:orange 4:yellow 5:lime 6:green 7:turquoise 8:cyan 9:cobalt 10:blue 11:violet 12:magenta 13:crimson
	unsigned long COLORSENSOR_lastReceived = 0;


};

#endif /* SRC_COLORSENSOR_H_ */
