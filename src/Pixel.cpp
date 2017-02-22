/*
 * Pixel.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: Bruno
 */

#include "Pixel.h"
#include <arduino.h>

Pixel::Pixel() {
	// TODO Auto-generated constructor stub

}

Pixel::~Pixel() {
	// TODO Auto-generated destructor stub
}

void Pixel::setup() {
	for (int iiii = 0; iiii < PIXELS_MAX; iiii++) {
		PIXELS_pixel[iiii] = 0;
		PIXELS_new[iiii] = false;
	}
}

void Pixel::processOutput() {
	if (!1/*sendOutput*/) {
		if (isKnown(SN_Pixels)) {
			if (PIXELS_new_value) {
				//if (millis() >= lastMotors + 100) {
				Serial.print(StrIndent);
				Serial.print("Pout:");
				aJsonObject* objectJSON = aJson.createObject();
				if (objectJSON != NULL) {
					aJson.addItemToObject(objectJSON, "sn", aJson.createItem(SN_Pixels));

					if (PIXELS_effect_fire) {
						aJson.addItemToObject(objectJSON, "fire", aJson.createItem(1));
					} else {
						char charBuf[3];
						int nb_pixels = 5;
						for (int iiii = 0; iiii < PIXELS_MAX; iiii++) {
							if (PIXELS_new[iiii] && nb_pixels > 0) {
								itoa(iiii, charBuf, 3);
								aJson.addItemToObject(objectJSON, charBuf,
										aJson.createItem(PIXELS_pixel[iiii]));
								PIXELS_new[iiii] = false;
								nb_pixels -= 1;
							}
						}
						if (nb_pixels == 5) {
							aJson.addItemToObject(objectJSON, "fire", aJson.createItem(0));
						}
					}

					/*if(PIXELS_new[1]) {
					 aJson.addItemToObject(objectJSON, "1", aJson.createItem(PIXELS_pixel[1]));
					 PIXELS_new[1] = false;
					 }*/

					char* msg = aJson.print(objectJSON);
					Serial.print(msg);
					int iiii = 0;
					while (*(msg + iiii) != '\0') {
						outBuffer[iiii] = *(msg + iiii);
						iiii += 1;
					}
					outBuffer_len = iiii;
					Serial.print(":");
					Serial.println(outBuffer_len);
					free(msg);

					//freeMem("freeMem");
					//sendOutput = true;
					//sendBus = bus(SN_Pixels);

					PIXELS_new_value = false;
					for (int iiii = 0; iiii < PIXELS_MAX; iiii++) {
						if (PIXELS_new[iiii]) {
							PIXELS_new_value = true;
						}
					}

				} else {
					Serial.print(StrError);
					Serial.println(":json");
				}
				aJson.deleteItem(objectJSON);
				PIXELS_last = millis();
				// }
			}
		}
	}
}

void Pixel::set(int pixel_num, int pixel_color) {
	if (pixel_num > 0) {
		pixel_num -= 1;
	}

	PIXELS_pixel[pixel_num] = pixel_color;
	PIXELS_new[pixel_num] = true;
	PIXELS_new_value = true;
}

void Pixel::set_hsl(int pixel_num, double h, double s, double l) {
	if (pixel_num > 0) {
		pixel_num -= 1;
	}

	byte rgb[3];

	hslToRgb(h, s, l, rgb);

	int pixel_color = ((rgb[0] / 16) << 8) + ((rgb[1] / 16) << 4)
			+ ((rgb[2] / 16) << 0);

	PIXELS_pixel[pixel_num] = pixel_color;
	PIXELS_new[pixel_num] = true;
	PIXELS_new_value = true;
}

void Pixel::set_fire(boolean val) {
	PIXELS_effect_fire = val;
	PIXELS_new_value = true;
}

void Pixel::hslToRgb(double h, double s, double l, byte rgb[]) {
	double r, g, b;

	h = h / 360;
	s = s / 100;
	l = l / 100;

	if (s == 0) {
		r = g = b = l; // achromatic
	} else {
		double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		double p = 2 * l - q;
		r = hue2rgb(p, q, h + 1 / 3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1 / 3.0);
	}

	rgb[0] = r * 255;
	rgb[1] = g * 255;
	rgb[2] = b * 255;
}

double Pixel::hue2rgb(double p, double q, double t) {
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


