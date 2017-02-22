#include <aJSON.h>
#include <arduino.h>

#include "src/RS485Manager.h"
#include "src/SpiManager.h"

SpiManager SPI;
RS485Manager RS485(2,6); ///RX,TX
void process();

#define PIN_DC      A0

//#define PIN_LED  13     // no pin_led à cause du SPI

int SN_Module = 100;      // conflit de nom à résoudre !!

#define MODULE_JOYSTICKS    true
#define MODULE_MOTORS       true
#define MODULE_ULTRASONIC   true
#define MODULE_COLORSENSOR  true
#define MODULE_SERVO        true
#define MODULE_PIXELS       true

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

//RS485
#define INBUFFER_SIZE         128
#define OUTBUFFER_SIZE        128

char inBuffer[INBUFFER_SIZE];
int inBuffer_i = 0;
char outBuffer[OUTBUFFER_SIZE];
int outBuffer_len = 0;

boolean stringComplete = false;       // whether the string is complete
boolean receiving = false;

//String outputString = "";           // a string to hold incoming data
boolean sendOutput = false;           // whether the string is complete
int sendBus = 0;                      // BUS_RS485 , BUS_SPI

#define NB_MODULES_MAX    3

int nb_modules = 0;
unsigned long modules_SN[NB_MODULES_MAX];
unsigned long modules_last[NB_MODULES_MAX];
String modules_Types[NB_MODULES_MAX] = { };
int modules_Bus[NB_MODULES_MAX];      // BUS_RS485 , BUS_SPI

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
		aJson.addItemToObject(objectJSON, "sm", aJson.createItem(SN_Module));
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
	bool stringProcessed = false;
	unsigned long SN_Module = 0;
	int receiveBus = 0;                   // BUS_RS485 , BUS_SPI

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

	if (RS485.RS485_stringComplete) {
		for (int i = 0; i < RS485.RS485_inBuffer_i; i++) {
			inBuffer[i] = RS485.RS485_inBuffer[i];
		}
		inBuffer_i = RS485.RS485_inBuffer_i;

		RS485.RS485_inBuffer_i = 0;

		//inBuffer[inBuffer_i] = 0;

		RS485.RS485_stringComplete = false;
		receiveBus = BUS_RS485;
		stringComplete = true;
	} else if (SPI.SPI_stringComplete) {
		for (int i = 0; i < SPI.SPI_inBuffer_i; i++) {
			inBuffer[i] = SPI.SPI_inBuffer[i];
		}
		inBuffer_i = SPI.SPI_inBuffer_i;

		SPI.SPI_inBuffer_i = 0;

		//inBuffer[inBuffer_i] = 0;

		SPI.SPI_stringComplete = false;
		receiveBus = BUS_SPI;
		stringComplete = true;
	} else {
		//stringComplete = false;
	}

	if (stringComplete) {

		//Serial.println("SC");

		Serial.print(millis());

		if (receiveBus == BUS_SPI) {
			Serial.print(" SPI>");
		} else if (receiveBus == BUS_RS485) {
			Serial.print(" RS485>");
		} else {
			Serial.print(" ?");
		}

		//memset(JsonBuffer, 0, JSON_BUFFER_SIZE);

		for (int i = 0; i < inBuffer_i; i++) {
			//JsonBuffer[i] = inBuffer[i];
			Serial.write(inBuffer[i]);
		}
		//JsonBuffer[inBuffer_i] = inBuffer[inBuffer_i];

		Serial.print(".");

		//if(false) {
		if (inBuffer_i > 2) {

			//Serial.println("_ok");

			unsigned long startParse = micros();

			aJsonObject* root = aJson.parse(inBuffer);
			//aJsonObject* root = aJson.parse(JsonBuffer);

			if (root != NULL) {
				Serial.print("parse:");
				Serial.print(micros() - startParse);
				Serial.println("us");

				aJsonObject* sn = aJson.getObjectItem(root, "sn");
				if (sn != NULL) {
					SN_Module = sn->valueint;    //valueint      root["sn"];
					if (!0/* MODULES_isKnown(SN_Module)*/) {
						modules_SN[nb_modules] = SN_Module;
						modules_Bus[nb_modules] = receiveBus;

						//modules_last[nb_modules] = millis();
						nb_modules += 1;
						Serial.print(StrIndent);
						Serial.print("New:");
						Serial.println(SN_Module);
					} else {
						Serial.print(StrIndent);
						Serial.print("Mod:");
						Serial.println(SN_Module);
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
				//Serial.print(String(micros() - startParse));
				//Serial.println("us");
				//Serial.print(String(micros() - startParse) + "us *** parseObject() failed: << ");

			}
			aJson.deleteItem(root);

			if (!parseSuccess) {
				Serial.print("(");
				for (int i = 0; i < inBuffer_i; i++) {
					Serial.print(inBuffer[i], HEX);
					Serial.print(".");
				}
				//Serial.print(String(JsonBuffer));
				Serial.println(")");
			}
		}

		stringProcessed = true;
	}

	if (parseSuccess) {
		//COLORSENSOR_processInput(SN_Module);// TODO
	}

	//SERVOS_processOutput(); // TODO

	/*
	 if (parseSuccess) {
	 JOYSTICKS_processInput(SN_Module);
	 }
	 JOYSTICKS_processOutput();

	 if (parseSuccess) {
	 ULTRASONIC_processInput(SN_Module);
	 }
	 //JOYSTICKS_processOutput();
	 */

	/*
	 if (parseSuccess) {
	 MOTORS_processInput(SN_Module);
	 }
	 MOTORS_processOutput();
	 */

	if (stringProcessed) {
		stringComplete = false;

		// clear the string:
		memset(inBuffer, 0, inBuffer_i);
		inBuffer_i = 0;

		//Serial.println("inBuffer cleared");
	}

	// time to send

	RS485.MODULES_question();
	SPI.MODULES_question();

	if (sendBus == BUS_RS485) {
		RS485.send();
	} else if (sendBus == BUS_SPI) {
		SPI.send();
	}
}

// loop ****************

void loop() { // run over and over

	while (true) {

		//SERVOS_Val_target = constrain( (millis() / 100) % 180, 0, 180);
		//SERVOS_Val_target = (SERVOS_Val_target / 10) * 10;

		//SERVOS_Val_target = constrain( ((millis() / 4000) % 2) * 180, 0, 180);
		//SERVOS_Val_target = map(SERVOS_Val_target, 0, 180, 10, 170);

		//motorA_speed_target = 50;
		//motorB_speed_target = 50;
		//motorA_speed_target = ((JOYSTICKS_getJ1Y() - JOYSTICKS_getJ1X()) / 2);
		process();
		//motorB_speed_target = ((JOYSTICKS_getJ1Y() + JOYSTICKS_getJ1X()) / 2);
		//process();
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

