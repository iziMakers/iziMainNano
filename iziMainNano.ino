#include <aJSON.h>
#include <arduino.h>
#include "src/Aspect.h"
#include "src/bus/RS485Manager.h"
#include "src/bus/SpiManager.h"
//#include "src/FreeMemory.h"
#include "src/Linker.h"

SpiManager SPI;
RS485Manager RS485(2, 6); ///RX,TX

/*#define PIN_DC      A0

 void measureDC() {
 int v_max = 5 * inputMesureDC_x;
 inputMesureDC = map(analogRead(PIN_DC), 0, 1023, 0, v_max);
 }
 void printDC() {
 Serial.print("DC:");
 Serial.println(inputMesureDC);
 }

 //int inputMesureDC = 0;
 //int inputMesureDC_x = 5045;      // multiplicateur pour obtenir des mV
 */

//#define PIN_LED  13     // no pin_led � cause du SPI


#include "src/modules/Joystick.h"
//Joystick joystick(100);
#include "src/modules/Motor.h"
//Motor motor(101);
#include "src/modules/Ultrasonic.h"
//Ultrasonic ultrasonic(102);
#include "src/modules/ColorSensor.h"
//ColorSensor colorSensor(103);
#include "src/modules/Servo.h"
//Servo servo(104);
#include "src/modules/Pixel.h"
//Pixel pixel(105);

const long baudrate_PC = 115200;

// SPI interrupt routine **************
ISR (SPI_STC_vect) {
	byte inChar = SPDR;  // grab byte from SPI Data Register
	SPI.setReceiving(true);
	SPI.addIncomingChar(inChar);

}

void ssChange() {
	delayMicroseconds(1);
	if (digitalRead(SPI.SPI_SSinterruptPin) == HIGH) { // RISING
		if (SPI.getReceiving()) {
			SPI.endRX();
		}
	} else { // FALLING
		SPI.setReceiving(true);
	}
}

// PC *********************************

void PC_setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(baudrate_PC);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	aJsonObject* objectJSON = aJson.createObject();

	if (objectJSON != NULL) {
		aJson.addItemToObject(objectJSON, "sm", aJson.createItem(100));
		aJson.addItemToObject(objectJSON, "mm", aJson.createItem("Starting"));

		char* msg = aJson.print(objectJSON);
		Serial.println(msg);
		free(msg);
	}
	aJson.deleteItem(objectJSON);
	//Serial.println("{\"mm\":\"Starting\"}");
}

// setup ******************************

void setup() {
	PC_setup();

	RS485.setup();
	SPI.setup();
	attachInterrupt(digitalPinToInterrupt(SPI.SPI_SSinterruptPin), ssChange,
	CHANGE); // interrupt for SS rising edge

	//pinMode(PIN_LED, OUTPUT);
	//digitalWrite(PIN_LED, LOW);

	//addModule(&motor);
	//addModule(&joystick);
	//addModule(&ultrasonic);
	//addModule(&pixel);
	//addModule(&colorSensor);
	//addModule(&servo);

	while (nbKnownModules == 0) {
		process();
	}
}

void pause(unsigned long length_ms) {     // pause qui ne bloque le process
	unsigned long start_ms = millis();
	while (millis() < start_ms + length_ms) {
		process();
	}
}

void process() {

	RS485.RS484_read();

	aJsonObject* root = RS485.processJSon();
	parseJSon(&RS485, root);
	RS485.MODULES_question();

	root = SPI.processJSon();
	parseJSon(&SPI, root);
	SPI.MODULES_question();

	for (int i = 0; i < nbKnownModules; i++) {
		busForKnownModules[0]->send(modulesKnown[0]->sendJson());
	}
}

void loop() { // run over and over
	while (true) {
		process();
	}
}
