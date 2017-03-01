/*
 * Enums.h
 *
 *  Created on: 28 févr. 2017
 *      Author: Bruno
 */

#ifndef SRC_ENUMS_H_
#define SRC_ENUMS_H_

enum BusCom {
	busWrong, busSPI, busRS485
};

enum ModuleType {
	mtWrong, mtJoystick, mtMotor, mtUltrasonic, mtColorSensor, mtServo, mtPixel
};


#endif /* SRC_ENUMS_H_ */
