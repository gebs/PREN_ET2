/*
 * Sensor.h
 *
 *  Created on: Apr 18, 2017
 *      Author: famga
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "PE_LDD.h"

#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "KSDK1.h"
#include "UTIL1.h"
#include "DIR_L.h"

#include "speed_R.h"
#include "speed_L.h"
#include "DIR_R.h"
#include "WAIT1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "Parcour.h"
#include "TU2.h"
#include "TRIG2.h"
#include "TRIG3.h"
#include "TRIG4.h"
#include "TRIG5.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "TRIG.h"
#include "Test.h"

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "FRTOS1.h"
#include "TestFreeRTOS.h"
#include "Motor.h"



 void Sensor(void*);
 
 /* 
  * \brief Called in case of an overflow during input capture. This function is called from an interrupt!
  * \param UserDataPtr Pointer to user structure
  */
 void US_EventEchoOverflow(LDD_TUserData *UserDataPtr);

 /*
  * \brief Called by the input capture interrupt for a raising or falling edge of the Echo pin
  * \param UserDataPtr Pointer to user structure
  */
 void US_EventEchoCapture(LDD_TUserData *UserDataPtr);

 /* 
  * \brief Convert measured microseconds to centimeters.
  * \param[in] temperatureCelsius Air temperature in degree Celsius
  */
 uint16_t US_usToMillimeters(uint16_t microseconds, uint8_t temperatureCelsius);

 uint16_t calcAirspeed_dms(uint8_t temperatureCelsius);
 
 uint16_t US_Measure_us(uint8_t i);
 

/*
 * @param n 0-4 deaktiviert Sensor 
 */
	

void deletsens(uint8_t n); 

/*
 * @param n 0-4 aktivert Sensor
 */

uint16_t getsens(uint8_t n); 
/*
 * Berechnet den Durchschnitt der letzten Messwerte ohne null Werte
 * 
 */

 void durchschnitt(void); 
 /*
  * \brief Driver initialization routine.
  */
 void US_Init(void);
 
 void Measure(void); 


#endif /* SENSOR_H_ */
