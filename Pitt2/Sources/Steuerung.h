/*
 * Steuerung.h
 *
 *  Created on: Apr 27, 2017
 *      Author: famga
 */

#ifndef STEUERUNG_H_
#define STEUERUNG_H_
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
# include "Sensor.h"

void Steuerung(void*); 
void setSensor(uint8_t sensornummer); 
void setsoll(uint16_t s);
void setspeed(int16_t uk); 
void start(uint8_t); 
void StateMachine(void *pvParameters); 

#endif /* STEUERUNG_H_ */

