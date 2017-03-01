/*
 * Pixel.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Pixel.h"

Pixel::Pixel(unsigned long serialNumber, unsigned long lastReading,
		aJsonObject* root) :
		Module(mtPixel, serialNumber, lastReading, root) {
}

Pixel::~Pixel() {
}

void Pixel::setup() {
	for (int i = 0; i < pixelMaxNomber; i++) {
		pixelColors[i] = 0;
		isNewPixelColors[i] = false;
	}
	//processOutput()
}

void Pixel::sendJson() {
	if (isOneNewPixelColor) {
		//if (millis() >= lastWriting + 1000) {

		aJsonObject* objectJSON = toJson();
		Serial.print(StrIndent);
		Serial.print("Mout:");
		sendOutput(objectJSON);
		aJson.deleteItem(objectJSON);
		lastWriting = millis();

		//verification
		isOneNewPixelColor = false;
		for (int iiii = 0; iiii < pixelMaxNomber; iiii++) {
			if (isNewPixelColors[iiii]) {
				isOneNewPixelColor = true;
			}
		}
	}

}

aJsonObject* Pixel::toJson() {
	aJsonObject* objectJSON = aJson.createObject();
	aJson.addItemToObject(objectJSON, parameterNames[0],
			aJson.createItem((int) getSerialNumber()));

	if (fireEffectActivated) {
		aJson.addItemToObject(objectJSON, parameterNames[1], aJson.createItem(1));
	} else {
		char charBuf[3];
		int nb_pixels = 5;
		for (int iiii = 0; iiii < pixelMaxNomber; iiii++) {
			if (isNewPixelColors[iiii] && nb_pixels > 0) {
				itoa(iiii, charBuf, 3);
				aJson.addItemToObject(objectJSON, charBuf,
						aJson.createItem(pixelColors[iiii]));
				isNewPixelColors[iiii] = false;
				nb_pixels -= 1;
			}
		}
		if (nb_pixels == 5) {
			aJson.addItemToObject(objectJSON, parameterNames[1], aJson.createItem(0));
		}
	}

	return objectJSON;
}

void Pixel::setPixelColor(int pixel_num, int pixel_color) {
	if (pixel_num > 0) {
		pixel_num -= 1;
	}
	pixelColors[pixel_num] = pixel_color;
	isNewPixelColors[pixel_num] = true;
	isOneNewPixelColor = true;
}

void Pixel::setPixelHSL(int pixel_num, double h, double s, double l) {
	if (pixel_num > 0) {
		pixel_num -= 1;
	}

	byte rgb[3];

	hslToRgb(h, s, l, rgb);

	int pixel_color = ((rgb[0] / 16) << 8) + ((rgb[1] / 16) << 4)
			+ ((rgb[2] / 16) << 0);

	pixelColors[pixel_num] = pixel_color;
	isNewPixelColors[pixel_num] = true;
	isOneNewPixelColor = true;
}

void Pixel::setFireOn(boolean val) {
	fireEffectActivated = val;
	isOneNewPixelColor = true;
}

void Pixel::hslToRgb(float h, float s, float l, byte rgb[]) {
	float r, g, b;

	h = h / 360;
	s = s / 100;
	l = l / 100;

	if (s == 0) {
		r = g = b = l; // achromatic
	} else {
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1 / 3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1 / 3.0);
	}

	rgb[0] = r * 255;
	rgb[1] = g * 255;
	rgb[2] = b * 255;
}

float Pixel::hue2rgb(float p, float q, float t) {
	if (t < 0)
		t += 1;
	if (t > 1)
		t -= 1;
	if (t < 1 / 6.0)
		return p + (q - p) * 6 * t;
	if (t < 1 / 2.0)
		return q;
	if (t < 2 / 3.0)
		return p + (q - p) * (2 / 3.0 - t) * 6;
	return p;
}

