/*
 * Steuerung.c
 *
 *  Created on: Apr 27, 2017
 *      Author: famga
 */
# include "Steuerung.h"
# include "Sensor.h"

uint16_t soll = 5; 
uint8_t Sensorn = 1; 

/* Konstanten */

uint16_t Kp = 0; 
uint16_t Ti = 0; 
uint16_t Td = 0; 
uint16_t Tr = 0; 
uint16_t u_min = 0; 
uint16_t u_max = 0; 


uint16_t e_k_1 = 0; 
uint16_t ui_k_1 = 0; 
uint16_t ei_k_1 = 0; 
uint16_t uei_k_1 = 0; 
uint16_t T = 500; 


void Steuerung(void *pvParameters) {
	(void) pvParameters; /* parameter not used */

	TickType_t xLastWakeTime;
	TickType_t xFrequency = T;
	xLastWakeTime = xTaskGetTickCount();
	
		FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
 
	
	uint16_t up_k; 
	int16_t  e_k; 
	uint16_t ui_k; 
	uint16_t ud_k; 
	uint16_t v_k; 
	uint16_t u_k; 
	uint16_t ei_k;
	uint16_t uei_k;

	
e_k = soll - getsens(Sensorn); 
    
  up_k = e_k * Kp;  
  ui_k = ui_k_1 + Kp/Ti * e_k_1 * T;   /* Ti Nachstellzeit*/
  ud_k = Kp*Td*(e_k -e_k_1)/T;    /* Td vorhaltezeit"*/
		    
	ui_k_1 = ui_k;
	e_k_1 = e_k;
		    
	v_k = up_k + ui_k + ud_k + uei_k_1;
		    
		    if (v_k > u_max){
		        u_k = u_max;}
		    
		    else{
		    	if( v_k < u_min){
		    
		        u_k = u_min;}
		    else{
		        u_k = v_k;}
		    }
		    
		    
		    ei_k = u_k - v_k;
		    uei_k = uei_k_1 + ei_k_1 * T * 1/Tr;
		    ei_k_1 = ei_k;
		    uei_k_1 = uei_k;
		    
		    
		    
void setsoll(uint16_t s){
  if ((s < 200) & (s > 25)){
	  soll = s; 
  }
}

void setSensor(uint8_t sensornummer){
	if((sensornummer < 5) & (sensornummer >= 0)){
		Sensorn = sensornummer; 
	}
}
	

}
