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

	//TODO to delete i think
	char StrModule[] = "module";
	char StrIndent[] = "  ";
	char StrError[] = "err";

#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

	char inBuffer[INBUFFER_SIZE];
	int inBuffer_i = 0;
	char outBuffer[OUTBUFFER_SIZE];
	int outBuffer_len = 0;
};

#endif /* SRC_COLORSENSOR_H_ */
