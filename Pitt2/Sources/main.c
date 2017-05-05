/* ###################################################################
**     Filename    : main.c
**     Project     : Pitt_ET
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-03, 10:37, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         This is a Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main  Hallo*/


/* Including needed modules to compile this module/procedure */
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
//#include "Test.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "FRTOS1.h"
#include "TestFreeRTOS.h"
#include "Motor.h"
#include "Sensor.h"
#include "Steuerung.h"

//Gobale Variablen

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */

{
  /* Write your local variable definition here */
  int i = 0; // Variable ohne Gebrauch
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /******************************************************/
  /*Starting Controller here! */
  
  //Hier müssen alle Tasks gestartet werden.
  
  if (FRTOS1_xTaskCreate(	MotorR,  /* pointer to the task */
		  	  	  	  	  	(signed portCHAR *)"MotorR", /* task name for kernel awareness debugging */
		  	  	  	  	  	configMINIMAL_STACK_SIZE, /* task stack size */
		  	  	  	  	  	(void*)NULL, /* optional task startup argument */
		  	  	  	  	  	tskIDLE_PRIORITY,  /* initial priority */
		  	  	  	  	  	(xTaskHandle*)NULL /* optional task handle to create */
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){}; /* Out of heap memory? */
  }
  
  
  if (FRTOS1_xTaskCreate(	MotorL,  /* pointer to the task */
		  	  	  	  	  	(signed portCHAR *)"MotorL", /* task name for kernel awareness debugging */
		  	  	  	  	  	configMINIMAL_STACK_SIZE, /* task stack size */
		  	  	  	  	  	(void*)NULL, /* optional task startup argument */
		  	  	  	  	  	tskIDLE_PRIORITY,  /* initial priority */
		  	  	  	  	  	(xTaskHandle*)NULL /* optional task handle to create */
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){}; /* Out of heap memory? */
  }
  
  if (FRTOS1_xTaskCreate(	Motor,  /* pointer to the task */
		  	  	  	  	  	(signed portCHAR *)"Motor", /* task name for kernel awareness debugging */
		  	  	  	  	  	configMINIMAL_STACK_SIZE, /* task stack size */
		  	  	  	  	  	(void*)NULL, /* optional task startup argument */
		  	  	  	  	  	tskIDLE_PRIORITY,  /* initial priority */
		  	  	  	  	  	(xTaskHandle*)NULL /* optional task handle to create */
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){}; /* Out of heap memory? */
  }
 
  
  if (FRTOS1_xTaskCreate(	Sensor,  
		  	  	  	  	  	(signed portCHAR *)"Sensor", 
		  	  	  	  	  	configMINIMAL_STACK_SIZE, 
		 	  	  	  	  	(void*)NULL, 
		  	  	  	  	  	tskIDLE_PRIORITY,  
		  	  	  	  	  	(xTaskHandle*)NULL 
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){};  
  }
 
  
  if (FRTOS1_xTaskCreate(	Steuerung,  
		  	  	  	  	  	(signed portCHAR *)"Steuerung",
		  	  	  	  	  	configMINIMAL_STACK_SIZE, 
		  	  	  	  	  	(void*)NULL, 
		  	  	  	  	  	tskIDLE_PRIORITY,  
		  	  	  	  	  	(xTaskHandle*)NULL 
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){}; 
  }
 

  /*if (FRTOS1_xTaskCreate(	StateMachine,  // pointer to the task 
		  	  	  	  	  	(signed portCHAR *)"StateMachine", // task name for kernel awareness debugging 
		  	  	  	  	  	configMINIMAL_STACK_SIZE, // task stack size 
		  	  	  	  	  	(void*)NULL, // optional task startup argument 
		  	  	  	  	  	tskIDLE_PRIORITY,  // initial priority 
		  	  	  	  	  	(xTaskHandle*)NULL // optional task handle to create 
     	 	 	 	 	 	 ) != pdPASS)
  {
     for(;;){}; // Out of heap memory? 
  }*/

  FRTOS1_vTaskStartScheduler();
  
  /*****************************************************/
  while(1){
	  
	  
	  
	  
	  
	  
  }
  
  
  
  
  
  /*Test der Motoren*/

  /*for(;;){
	  
	  
	  
	  
  }*/
  
  
  
  
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
