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
	Pixel();
	virtual ~Pixel();

	void setup();
	void processOutput();
	void set(int pixel_num, int pixel_color);
	void set_hsl(int pixel_num, double h, double s, double l);

	void set_fire(boolean val);

	void hslToRgb(double h, double s, double l, byte rgb[]);
	double hue2rgb(double p, double q, double t);

#define PIXELS_MAX    100
	int SN_Pixels = 103;

	boolean PIXELS_new_value = false;
	int PIXELS_pixel[PIXELS_MAX];
	boolean PIXELS_new[PIXELS_MAX];

	boolean PIXELS_effect_fire = false;

	unsigned long PIXELS_last = 0;
};

#endif /* SRC_PIXEL_H_ */
