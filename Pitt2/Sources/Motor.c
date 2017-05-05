/*
 * Motor.c
 *
 *  Created on: Mar 3, 2017
 *      Author: Martina M
 */

#include "Motor.h"


TickType_t speedR = 1;
TickType_t speedL = 1;

uint8_t dirR;
uint8_t dirL;
uint8_t stopRL;

void setSpeedR(TickType_t speed)
{
	speedR = speed;
}

void setSpeedL(TickType_t speed)
{
	speedL = speed;
}

void setDirR(uint8_t dir)
{
	dirR = dir;
}

void setDirL(uint8_t dir)
{
	dirL = dir;
}
void setStop(uint8_t stop)
{
	stopRL = stop;
}

 void MotorR(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  
  TickType_t xLastWakeTime;
  TickType_t xFrequency = 10;
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;) {
 // do something
<<<<<<< HEAD
	  xFrequency = speedR;
	  //xFrequency = 1; //Test Wert
	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
	  speed_R_SetVal(speed_R_DeviceData);									// pos Flanke
	  											
	  xFrequency = 1; //Test Wert
	   FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait short
	  
	  speed_R_ClrVal(speed_R_DeviceData);									// neg Flanke
=======
	  if(stopRL == 0){  
		  xFrequency = speedR;
		  xFrequency = 1; //Test Wert
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
		  speed_R_SetVal(speed_R_DeviceData);									// pos Flanke
	  											
		  xFrequency = 1; //Test Wert
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait short
	  	  speed_R_ClrVal(speed_R_DeviceData);									// neg Flanke
>>>>>>> origin/master
	  
	  	  dirR= 0; // Test-Wert 
	  
	  	  if(dirR > 0){						  // Richtung definineren
	  		  DIR_R_SetVal(DIR_R_DeviceData); // Richtung definieren 1
	  	  }else{
	  		  DIR_R_ClrVal(DIR_R_DeviceData); // Richtung definieren 0  
	  	  }
	  }else{
		  xFrequency = 10; 
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
	  }
  }
}
 
 
 void MotorL(void *pvParameters) {
   (void)pvParameters; /* parameter not used */
   
   TickType_t xLastWakeTime;
   TickType_t xFrequency = 10;
   xLastWakeTime = xTaskGetTickCount();
   
   for(;;) {
  // do something
<<<<<<< HEAD
 	  xFrequency = speedL;
 	//  xFrequency =1; //Test Wert
=======
	  if(stopRL == 0){
		  xFrequency = speedL;
		  xFrequency =1; //Test Wert
>>>>>>> origin/master
 	  
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
		  speed_L_SetVal(speed_L_DeviceData);									// pos Flanke
 	  
													
<<<<<<< HEAD
 	//  xFrequency = 1; //Test Wert
 	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait short
 	  speed_L_ClrVal(speed_L_DeviceData);									// neg Flanke
=======
		  xFrequency = 1; //Test Wert
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait short
		  speed_L_ClrVal(speed_L_DeviceData);									// neg Flanke
>>>>>>> origin/master
 	  
		  dirL = 0;  //Test-Wert
 			  
		  if(dirL > 0){						  // Richtung definineren
			  DIR_L_ClrVal(DIR_L_DeviceData); // Richtung definieren 0  
		  }else{
			  DIR_L_SetVal(DIR_L_DeviceData); // Richtung definieren 1
		  }
	  }else{
		  xFrequency = 10; 
		  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait  
	  }
	
   }
 }

 // Test Task
 void Motor(void *pvParameters) {
  (void)pvParameters; /* parameter not used */
  
  TickType_t xLastWakeTime;
  TickType_t xFrequency = 10;
  xLastWakeTime = xTaskGetTickCount();
  
  
  for(;;) {
	  
	  xFrequency = 400; //Test Wert
	  
	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
					
	  LED1_Neg(); // für Testzweck
	  												
	  xFrequency = 200; //Test Wert
	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS);	// wait short
	  									// neg Flanke
	  LED1_Neg(); // für Testzweck
  }
}
 
 
 
 
/*void StateMachine(void *pvParameters) {
	(void)pvParameters; //parameter not used 
    
    TickType_t xLastWakeTime;
    TickType_t xFrequency = 10;		//muss die Statemaschine "ausgebremst" werden?
    xLastWakeTime = xTaskGetTickCount(); 
    
    uint8_t state = 1;	
    
    for(;;) {
   // do something
  	  
  	  xFrequency = 800; //Test Wert
  	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
  	  
  	  switch(state){
  	  case 1:
  		  setDirL(1); 	//Vorwärts
  		  setDirR(1);
  		  setSpeedR(2);	//Geschwindigkeit 2
  		  setSpeedL(2);
  		  
  	  	  // Linker oder Rechter Parcour? 
  	  	  // Hardware Schalter einlesen
  		  
  	  	  state = 2;
  	  	  break;
  	  case 2:
  		  // If Startsymbol via USB erhalten
  		  	  //Starte MotorTask
  		  	  state = 3;
  		  // Else 
  		  	  state = 2;
  		  break;
  	  case 3:
  		  // If zu rechts 
  		  //	fahre bizi links
  		  // If zu links
  		  // 	fahre bizi rechts
  		  // Else 
  		  // 	fahre gerade aus
  		  
  		  // If Kurve erreicht
  		  //  	fahre Kurve
  		  state = 4;
  		  break;
  	  case 4:

  		  state = 5;
  		  break;
  	  case 5:
  		  // IF Zahl erkannt
  		  // 	fahre korrekten abstand
  		  break;
  	
  	  
  	  }
  	  
  	  
  	  
  	 
    }
  }
*/
 
