/*
 * Sensor.c
 *
 *  Created on: Apr 18, 2017
 *      Author: famga
 */
#include "Sensor.h"



uint8_t sens[5] = { 0, 0, 0, 1, 0 }; /* = 1 wenn Sensor ausgwertet werden soll */
TickType_t abtastzeit = 30;        /* Zeit zwischen Sensormessung */ 

typedef struct Mwertarray {

	uint16_t werte[5];
	uint16_t durchschnitt;
} Mwertarray;

typedef struct Messwerte {
	Mwertarray mess[5];
	
} Messwerte;

Messwerte messwerte;

typedef enum {
	ECHO_IDLE, /* device not used */
	ECHO_TRIGGERED, /* started trigger pulse */
	ECHO_MEASURE, /* measuring echo pulse */
	ECHO_OVERFLOW, /* measurement took too long */
	ECHO_FINISHED /* measurement finished */
} US_EchoState;

typedef struct US_DeviceType {
	LDD_TDeviceData *trigDevice; /* device handle for the Trigger pin */
	LDD_TDeviceData *echoDevice; /* input capture device handle (echo pin) */
	volatile US_EchoState state; /* state */
	TU2_TValueType capture; /* input capture value */
	void (*setVal)(LDD_TDeviceData*); /**< function pointer for TRIG device */
	void (*clrVal)(LDD_TDeviceData*); /**< function pointer for TRIG device */
} US_DeviceType;

typedef struct US_Devices {

	US_DeviceType usDevice[5];
	uint8_t currentDevice;
} US_Devices;

US_Devices usDevices;

void Sensor(void *pvParameters) {
	(void) pvParameters; /* parameter not used */

	TickType_t xLastWakeTime;
	TickType_t xFrequency = 200;
	xLastWakeTime = xTaskGetTickCount();
	US_Init();

	for (;;) {

		Measure();
		durchschnitt();
		//FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
		
	}

}

void US_EventEchoOverflow(LDD_TUserData *UserDataPtr) {
	US_Devices *ptr;
	ptr = (US_Devices*) UserDataPtr;
	ptr->usDevice[ptr->currentDevice].state = ECHO_OVERFLOW;
}

void US_EventEchoCapture(LDD_TUserData *UserDataPtr) {
	US_Devices *ptr;
	ptr = (US_Devices*) UserDataPtr;
	if (ptr->usDevice[ptr->currentDevice].state == ECHO_TRIGGERED) {
		TU2_ResetCounter(ptr->usDevice[ptr->currentDevice].echoDevice);
		ptr->usDevice[ptr->currentDevice].state = ECHO_MEASURE;
	} else if (ptr->usDevice[ptr->currentDevice].state == ECHO_MEASURE) {
		(void) TU2_GetCaptureValue(ptr->usDevice[ptr->currentDevice].echoDevice,
				ptr->currentDevice, &ptr->usDevice[ptr->currentDevice].capture);
		ptr->usDevice[ptr->currentDevice].state = ECHO_FINISHED;
	}

}

uint16_t calcAirspeed_dms(uint8_t temperatureCelsius) {

	/* Return the airspeed depending on the temperature, in deci-meter per second */
	unsigned int airspeed; /* decimeters per second */

	airspeed = 3313 + (6 * temperatureCelsius); /* dry air, 0% humidity, see http://en.wikipedia.org/wiki/Speed_of_sound */
	airspeed -= (airspeed / 100) * 17; /* factor in a relative humidity of ~40% */
	return airspeed;
}

uint16_t US_usToMillimeters(uint16_t microseconds, uint8_t temperatureCelsius) {
	return (microseconds * 1000UL) / calcAirspeed_dms(temperatureCelsius) / 2; /* 2 because of two way */
}

/* measure and return the microseconds */
uint16_t US_Measure_us(uint8_t i) {
	uint16_t us;

	/* send 10us pulse on TRIG line. */

	usDevices.currentDevice = i;
	usDevices.usDevice[i].setVal(usDevices.usDevice[i].trigDevice);
	
	WAIT1_Waitus(10);

	usDevices.usDevice[i].state = ECHO_TRIGGERED;
	usDevices.usDevice[i].clrVal(usDevices.usDevice[i].trigDevice);

	while (usDevices.usDevice[i].state != ECHO_FINISHED) {
		/* measure echo pulse */
		if (usDevices.usDevice[i].state == ECHO_OVERFLOW) {
			/* measurement took too long? */
			usDevices.usDevice[i].state = ECHO_IDLE;
			return 0;
		}
	}
	us = (usDevices.usDevice[i].capture * 1000UL)
			/ (TU2_CNT_INP_FREQ_U_0 / 1000);
	return us;
}

void US_Init(void) {
	
	usDevices.usDevice[0].state = ECHO_IDLE;
	usDevices.usDevice[0].capture = 0;
	usDevices.usDevice[0].trigDevice = TRIG_Init(NULL);
	usDevices.usDevice[0].echoDevice = TU2_Init(&usDevices);
	usDevices.usDevice[0].clrVal = TRIG_ClrVal;
	usDevices.usDevice[0].setVal = TRIG_SetVal;

	usDevices.usDevice[1].state = ECHO_IDLE;
	usDevices.usDevice[1].capture = 0;
	usDevices.usDevice[1].trigDevice = TRIG2_Init(NULL);
	usDevices.usDevice[1].echoDevice = usDevices.usDevice[0].echoDevice;
	usDevices.usDevice[1].clrVal = TRIG2_ClrVal;
	usDevices.usDevice[1].setVal = TRIG2_SetVal;

	usDevices.usDevice[2].state = ECHO_IDLE;
	usDevices.usDevice[2].capture = 0;
	usDevices.usDevice[2].trigDevice = TRIG3_Init(NULL);
	usDevices.usDevice[2].echoDevice = usDevices.usDevice[0].echoDevice;
	usDevices.usDevice[2].clrVal = TRIG3_ClrVal;
	usDevices.usDevice[2].setVal = TRIG3_SetVal;

	usDevices.usDevice[3].state = ECHO_IDLE;
	usDevices.usDevice[3].capture = 0;
	usDevices.usDevice[3].trigDevice = TRIG4_Init(NULL);
	usDevices.usDevice[3].echoDevice = usDevices.usDevice[0].echoDevice;
	usDevices.usDevice[3].clrVal = TRIG4_ClrVal;
	usDevices.usDevice[3].setVal = TRIG4_SetVal;

	usDevices.usDevice[4].state = ECHO_IDLE;
	usDevices.usDevice[4].capture = 0;
	usDevices.usDevice[4].trigDevice = TRIG5_Init(NULL);
	usDevices.usDevice[4].echoDevice = usDevices.usDevice[0].echoDevice;
	usDevices.usDevice[4].clrVal = TRIG5_ClrVal;
	usDevices.usDevice[4].setVal = TRIG5_SetVal;

}


void Measure(void) {
	TickType_t xLastWakeTime;
	TickType_t xFrequency = 120;
	xLastWakeTime = xTaskGetTickCount();

	uint8_t i = 0;
	uint8_t j = 0;
	uint16_t us = 0, cm = 0;
	uint8_t buf[8];

	for (j; j < 5; j++) {
		i = 0;
		// Term1_Cls(); 
		Term1_CursorDown(1);
		Term1_CursorLeft(80);

		for (i; i < 5; i++) {
			if (sens[i] == 1) {
				us = US_Measure_us(i);

				UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);

				cm = US_usToMillimeters(us, 22);
				messwerte.mess[i].werte[j] = cm;

				UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);
				Term1_SendStr("   ");
				Term1_SendNum(cm);
				Term1_SendStr("mm       ");
				FRTOS1_vTaskDelayUntil(&xLastWakeTime,
						abtastzeit/portTICK_RATE_MS);
			}

		}

	}

}


void durchschnitt(void) {
	uint8_t buf[8];
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t divisor = 0;

	uint16_t durch[5] = { 0, 0, 0, 1, 0 };
	Term1_CursorDown(2);
	Term1_CursorLeft(80);

	Term1_SendStr(
			" vlinks         hlinks        vrechts      hrechts       vmitte   ");
	Term1_CursorDown(1);
	Term1_CursorLeft(80);
	for (j; j < 5; j++) {
		for (i; i < 5; i++) {
			//if (sens[j] == 1){
			if (messwerte.mess[j].werte[i] != 0) {
				
				durch[j] += messwerte.mess[j].werte[i]; /*summiert alle Messwerte*/
				divisor++;
			}

		}
		i = 0;
		if (divisor != 0) {
			durch[j] = (durch[j] / divisor); /* dividiert die summe der Messwerte durch anzahl Messwerte ungleich 0*/
			divisor = 0;
			messwerte.mess[j].durchschnitt = durch[j]; 
			UTIL1_Num16uToStrFormatted(buf, sizeof(buf), durch[j], ' ', 5);
			Term1_SendStr("   ");
			Term1_SendNum(durch[j]);
			Term1_SendStr("mm       ");
		}
		//}

	}

	Term1_CursorDown(1);
	Term1_CursorLeft(80);
}
/*
 * 
 */
void setsens(uint8_t n){
	if(n<5){
	sens[n] = 1; 
	}
}

void deletsens(uint8_t n){
	if(n<5){
	sens[n]= 0;
	messwerte.mess[n].durchschnitt = 0; 
	messwerte.mess[n].werte[0] = 0;
	messwerte.mess[n].werte[1] = 0; 
	messwerte.mess[n].werte[2] = 0; 
	messwerte.mess[n].werte[3] = 0; 
	messwerte.mess[n].werte[4] = 0; 
	}             //////////////////////////////////////////////////// änderung
}

uint16_t getsens(uint8_t n){

	return  messwerte.mess[n].durchschnitt; 
}









