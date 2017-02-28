/*
 * Pixel.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_MODULES_PIXEL_H_
#define SRC_MODULES_PIXEL_H_
#include "Module.h"

class Pixel: public Module {
public:
	Pixel(unsigned long serialNumber = 0, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long lastReading = 0,
			aJsonObject* root = NULL);
	virtual ~Pixel();

	void setup();
	void sendJson();
	void setPixelColor(int pixel_num, int pixel_color);
	void setPixelHSL(int pixel_num, double h, double s, double l);
	void setFireOn(boolean val);

private:
	char* parameterNames[2] = { "sn", "fire" };
	const static uint8_t pixelMaxNomber = 100;
	int pixelColors[pixelMaxNomber];
	boolean isNewPixelColors[pixelMaxNomber];
	boolean isOneNewPixelColor = false;
	boolean fireEffectActivated = false;

	aJsonObject* toJson();
	void hslToRgb(float h, float s, float l, byte rgb[]);
	float hue2rgb(float p, float q, float t);
};

#endif /* SRC_MODULES_PIXEL_H_ */
