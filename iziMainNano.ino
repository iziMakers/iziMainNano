#include <aJSON.h>
#include <arduino.h>
#include "src/Aspect.h"
#include "src/bus/RS485Manager.h"
#include "src/bus/SpiManager.h"
//#include "src/FreeMemory.h"

#include "src/ModulesManager.h"

SpiManager SPI;
RS485Manager RS485(2, 6); ///RX,TX
void process();

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

//#define PIN_LED  13     // no pin_led à cause du SPI
#define MODULE_JOYSTICKS    true
#define MODULE_MOTORS       true
#define MODULE_ULTRASONIC   true
#define MODULE_COLORSENSOR  true
#define MODULE_SERVO        true
#define MODULE_PIXELS       true

#include "src/modules/Module.h"

#if MODULE_JOYSTICKS
#include "src/modules/Joystick.h"
Joystick joystick(100);
#endif

#if MODULE_MOTORS
#include "src/modules/Motor.h"
Motor motor(101);
#endif

#if MODULE_ULTRASONIC
#include "src/modules/Ultrasonic.h"
Ultrasonic ultrasonic(102);
#endif

#if MODULE_COLORSENSOR
#include "src/modules/ColorSensor.h"
ColorSensor colorSensor(103);
#endif

#if MODULE_SERVO
#include "src/modules/Servo.h"
Servo servo(104);
#endif

#if MODULE_PIXELS
#include "src/modules/Pixel.h"
Pixel pixel(105);
#endif

long baudrate_PC = 115200;

char StrModule[] = "module";
char StrIndent[] = "  ";
char StrError[] = "err";

char TrameByteStart = '{';
char TrameByteEnd = '}';

// SPI interrupt routine
ISR (SPI_STC_vect) {
	byte inChar = SPDR;  // grab byte from SPI Data Register
	SPI.setReceiving(true);
	SPI.addIncomingChar(inChar);
	SPI.lastRxStart = millis();
}

// PC ****************

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

// setup ****************

void setup() {
	PC_setup();

	RS485.setup();
	SPI.setup();

	//pinMode(PIN_LED, OUTPUT);
	//digitalWrite(PIN_LED, LOW);

	while (nb_modules == 0) {
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
	ModuleType moduleType = mtWrong;
	unsigned long serialNumber = 0;
	BusCommunication receiveBus = bcWrong;                  // BUS_RS485 , BUS_SPI
	aJsonObject* root;

	RS485.RS484_read();

	if (RS485.getStringComplete()) {
		root = aJson.parse(RS485.dataBuffer);
		for (int i = 0; i < RS485.dataBufferLength; i++) {
			DEBUG_PRINT(RS485.dataBuffer[i]);
		}
		DEBUG_PRINTLN(".");
		RS485.dataBufferLength = 0;
		RS485.setStringComplete(false);     // notify that the buffer is treated

		receiveBus = bcRS485;
		DEBUG_PRINT(millis());
		DEBUG_PRINT(" RS485>");

	} else if (SPI.getStringComplete()) {
		root = aJson.parse(SPI.dataBuffer);
		for (int i = 0; i < SPI.dataBufferLength; i++) {
			DEBUG_PRINT(SPI.dataBuffer[i]);
		}
		DEBUG_PRINTLN(".");
		SPI.dataBufferLength = 0;
		SPI.setStringComplete(false);         // notify that the buffer is treated

		receiveBus = bcSPI;
		DEBUG_PRINT(millis());
		DEBUG_PRINT(" SPI>");

	} else {
		receiveBus = bcWrong;
		DEBUG_PRINT(" ?");
		return;

	}

	if (root != NULL) {
		aJsonObject* sn = aJson.getObjectItem(root, "sn");
		if (sn != NULL) {
			serialNumber = sn->valueint;    //valueint      root["sn"];
			Module* knownModule = Module_getModuleKnown(serialNumber);
			if (knownModule == NULL) {
				//Module newModule(mtWrong, receiveBus); // TODO create module there
				Module* unknownModule = Module_getModule(serialNumber);
				unknownModule->setBusCom(receiveBus);
				unknownModule->processJsonInput(root);
				addModuleKnown(*unknownModule);

				DEBUG_PRINT(StrIndent);
				DEBUG_PRINT("New:");
				DEBUG_PRINTLN(serialNumber);
			} else {
				knownModule->processJsonInput(root);

				DEBUG_PRINT(StrIndent);
				DEBUG_PRINT("Mod:");
				DEBUG_PRINTLN(serialNumber);
			}
		} else {
			Serial.print(StrError);
			Serial.println(":no \"sn\"");
		}
	} else {
		Serial.print(StrError);
		Serial.println(":parse");
	}
	aJson.deleteItem(root);

	RS485.MODULES_question();
	SPI.MODULES_question();
}

void loop() { // run over and over
	while (true) {
		process();
	}
}
