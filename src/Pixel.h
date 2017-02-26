/*
 * Pixel.h
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_PIXEL_H_
#define SRC_PIXEL_H_
#include "Module.h"

class Pixel: public Module {
public:
	Pixel(ModuleType mt = mtWrong, BusCommunication busCom = bcWrong,
			CommunicationManager* comManager = NULL, unsigned long serialNumber = 0,
			unsigned long lastReading = 0, aJsonObject* root = NULL);
	virtual ~Pixel();

	void setup();
	void processSpecificInput(aJsonObject* root);
	void processOutput();
	void setPixelColor(int pixel_num, int pixel_color);
	void setPixelHSL(int pixel_num, double h, double s, double l);
	void setFireOn(boolean val);

private:
	void hslToRgb(float h, float s, float l, byte rgb[]);
	float hue2rgb(float p, float q, float t);

	const static uint8_t pixelMaxNomber = 100;
	int pixelColors[pixelMaxNomber];
	boolean isNewPixelColors[pixelMaxNomber];
	boolean isOneNewPixelColor = false;

	boolean fireEffectActivated = false;
};

#endif /* SRC_PIXEL_H_ */
