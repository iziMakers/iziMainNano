#include <aJSON.h>
#include <arduino.h>
#include "src/Aspect.h"

#include "src/RS485Manager.h"
#include "src/SpiManager.h"
#include "src/ModulesManager.h"

SpiManager SPI;
RS485Manager RS485(2, 6); ///RX,TX
void process();

#define PIN_DC      A0

//#define PIN_LED  13     // no pin_led à cause du SPI

#define MODULE_JOYSTICKS    true
#define MODULE_MOTORS       true
#define MODULE_ULTRASONIC   true
#define MODULE_COLORSENSOR  true
#define MODULE_SERVO        true
#define MODULE_PIXELS       true

#include "src/Module.h"

#if MODULE_JOYSTICKS
#include "src/Joystick.h"
#endif

#if MODULE_MOTORS
#include "src/Motor.h"
#endif

#if MODULE_ULTRASONIC
#include "src/Ultrasonic.h"
#endif

#if MODULE_COLORSENSOR
#include "src/ColorSensor.h"
#endif

#if MODULE_SERVO
#include "src/Servo.h"
#endif

#if MODULE_PIXELS
#include "src/Pixel.h"
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
	/*if(!receiving) {
	 Serial.print("RX:");
	 Serial.print(inChar, HEX);
	 }*/
	//receiving = true;
	SPI.addIncomingChar(inChar);
	SPI.SPI_RX_start_ms = millis();
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

/*
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

void pause(unsigned long length_ms) {     // pause qui ne bloque le process
	unsigned long start_ms = millis();
	while (millis() < start_ms + length_ms) {
		process();
	}
}

void process() {
	//char inBuffer[INBUFFER_SIZE];
	//char JsonBuffer[JSON_BUFFER_SIZE];
	bool parseSuccess = false;
	bool stringComplete = false;
	bool stringProcessed = false;
	ModuleType moduleType = mtWrong;
	unsigned long serialNumber = 0;
	BusCommunication receiveBus = bcWrong;                  // BUS_RS485 , BUS_SPI

	RS485.RS484_read();

	/*
	 if (receiving) {
	 if (digitalRead(SPI_SSinterruptPin) == HIGH) {
	 // receiving should be finished
	 receiving = false;
	 stringComplete = true;
	 receiveBus = BUS_SPI;

	 Serial.print("X_");
	 }
	 }
	 */
	aJsonObject* root;
	if (RS485.getStringComplete()) {
		root = aJson.parse(RS485.dataBuffer);
		for (int i = 0; i < RS485.dataBufferLength; i++) {
			DEBUG_PRINT(RS485.dataBuffer[i]);
		}
		DEBUG_PRINTLN(".");
		RS485.dataBufferLength = 0;
		RS485.bStringComplete = false;     // notify that the buffer is treated

		receiveBus = bcRS485;
		stringComplete = true;
		DEBUG_PRINT(millis());
		DEBUG_PRINT(" RS485>");

	} else if (SPI.getStringComplete()) {
		root = aJson.parse(SPI.dataBuffer);
		for (int i = 0; i < SPI.dataBufferLength; i++) {
			DEBUG_PRINT(SPI.dataBuffer[i]);
		}
		DEBUG_PRINTLN(".");
		SPI.dataBufferLength = 0;
		SPI.bStringComplete = false;         // notify that the buffer is treated

		receiveBus = bcSPI;
		stringComplete = true;
		DEBUG_PRINT(millis());
		DEBUG_PRINT(" SPI>");

	} else {
		receiveBus = bcWrong;
		stringComplete = false;
		DEBUG_PRINT(" ?");

	}

	if (stringComplete) {
		if (root != NULL) {
			aJsonObject* sn = aJson.getObjectItem(root, "sn");
			if (sn != NULL) {
				serialNumber = sn->valueint;    //valueint      root["sn"];
				Module* existing = Module_getModule(serialNumber);
				if (existing == NULL) {
					Module newModule(mtWrong, receiveBus); // TODO add Module type
					newModule.setLastReading(millis());
					newModule.processInput(root);
					modules[nb_modules] = newModule;
					nb_modules += 1;

					DEBUG_PRINT(StrIndent);
					DEBUG_PRINT("New:");
					DEBUG_PRINTLN(serialNumber);
				} else {
					existing->processInput(root);

					DEBUG_PRINT(StrIndent);
					DEBUG_PRINT("Mod:");
					DEBUG_PRINTLN(serialNumber);
				}
				parseSuccess = true;
			} else {
				Serial.print(StrError);
				Serial.println(":no \"sn\"");
			}
			//aJson.deleteItem(sn);
		} else {
			Serial.print(StrError);
			Serial.println(":parse");
		}
		aJson.deleteItem(root);
	}
	stringProcessed = true;
	stringComplete = false;



// time to send

	RS485.MODULES_question();
	SPI.MODULES_question();
	/*SERVOS_processOutput(); // TODO
	 JOYSTICKS_processOutput();
	 MOTORS_processOutput();

	if (sendBus == BUS_RS485) {
		RS485.send();
	} else if (sendBus == BUS_SPI) {
		SPI.send();
	 }*/
}

// loop ****************

void loop() { // run over and over
	while (true) {
		process();
	}
}

//Code to print out the free memory
struct __freelist {
	size_t sz;
	struct __freelist *nx;
};

extern char * const __brkval;
extern struct __freelist *__flp;

uint16_t freeMem(uint16_t *biggest) {
	char *brkval;
	char *cp;
	unsigned freeSpace;
	struct __freelist *fp1, *fp2;

	brkval = __brkval;
	if (brkval == 0) {
		brkval = __malloc_heap_start;
	}
	cp = __malloc_heap_end;
	if (cp == 0) {
		cp = ((char *) AVR_STACK_POINTER_REG) - __malloc_margin;
	}
	if (cp <= brkval)
		return 0;

	freeSpace = cp - brkval;

	for (*biggest = 0, fp1 = __flp, fp2 = 0; fp1; fp2 = fp1, fp1 = fp1->nx) {
		if (fp1->sz > *biggest)
			*biggest = fp1->sz;
		freeSpace += fp1->sz;
	}

	return freeSpace;
}

uint16_t biggest;

void freeMem(char* message) {
	Serial.print(message);
	Serial.print(":\t");
	Serial.println(freeMem(&biggest));
}
