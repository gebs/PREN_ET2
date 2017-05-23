/*
 * Motor.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Martina M
 */

#ifndef MOTOR_H_
#define MOTOR_H_



#include "DIR_R.h"
#include "DIR_L.h"
#include "speed_R.h"
#include "speed_L.h"
#include "WAIT1.h"
#include "LED1.h"

#include "FRTOS1.h"



#endif /* MOTOR_H_ */

 // Seter - Methoden
void motorstop(void);
void motorstart(void);
 void setSpeedR(TickType_t);
 void setSpeedL(TickType_t);
 void setDirR(uint8_t);
 void setDirL(uint8_t);
 void setStop(uint8_t);
 // Tasks
 void MotorR(void*);
 void MotorL(void*);
 //void StateMachine(void*);
 void Motor(void*);
