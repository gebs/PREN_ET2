/*
 * Steuerung.c
 *
 *  Created on: Apr 27, 2017
 *      Author: famga
 */
# include "Steuerung.h"



uint16_t abstand; 
uint16_t soll = 130; 
uint8_t Sensorn = 0; 
uint8_t Parcourshaelfte = 0; 
uint8_t Parcourseite = 0; 
uint8_t parcour2 = 0; 
uint8_t start = 0; 
/* Konstanten */



int16_t Kp = 2; 
int16_t Ti = 1000; 
int16_t Td = 0; 
int16_t  e; 
int16_t u_min = -100; 
int16_t u_max = 100; 
uint16_t T = 1; 

int16_t e_1 = 0; 
int16_t ui_1 = 0; 
uint16_t ei_1 = 0; 



void Steuerung(void *pvParameters) {
	(void) pvParameters; 
 
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	
	int16_t up; 	
	int16_t ui; 
	int16_t ud; 
	int16_t v_k; 
	int16_t u_k; 
	for(;;){
		TickType_t xFrequency = 200;
		FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
/*		

}*/
 if(Parcourseite == 0){   // Parcour rechts

	 if(start == 0){
	 	 setSpeedR(1); 
	 	 setSpeedL(1); 
	 	 setSensor(3);
	 	 TickType_t xFrequency = 5000;
	 	 FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	 	 start = 1;  
	 }
	 
 setsens(Sensorn); 
 abstand = getsens(Sensorn); 
 setSpeedR(1); 
 setSpeedL(1); 
 
 
 if (Parcourshaelfte == 0){
	 
	 
	if(abstand < (soll - 10)){
		setSpeedR(2); 
		setSpeedL(1);
	}
	if(abstand > (soll + 10)){
		setSpeedL(2);
		setSpeedR(1);    
	}
 }
 if (Parcourshaelfte == 1){
		if(abstand < (soll - 10)){
			setSpeedR(1); 
			setSpeedL(2);
		}
		if(abstand > (soll + 10)){
			setSpeedL(1);
			setSpeedR(2);  
		}
			 
 }

 if((abstand > 250) && (parcour2 == 0)){
	    setSpeedL(1);
	 	setSpeedR(1);
	 	xFrequency = 5000; 
	 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	 	xFrequency = 5500;
	 	setSpeedL(1000);
	 	setSpeedR(1);
	 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	 	xFrequency = 4500;
	 	setSpeedR(1);
	 	setSpeedL(1);
	 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	 	xFrequency = 5500;
	 	setSpeedL(1000);
	 	setSpeedR(1);
	 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	 	setSpeedL(1); 
	 	setSensor(1); 
	 	xFrequency = 1000; 
	 	Parcourshaelfte = 1; 
	 	deletsens(3); 
	 	parcour2 = 1; 
	 }

 }
	if (Parcourseite == 1){                 // Parcour links
		 if(start == 0){
		 	 setSpeedR(1); 
		 	 setSpeedL(1); 
		 	 setSensor(1);
		 	 TickType_t xFrequency = 5000;
		 	 FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
		 	 start = 1;  
		 }
		
		
		
		 setsens(Sensorn); 
		 abstand = getsens(Sensorn); 
		 setSpeedR(1); 
		 setSpeedL(1); 
		 
		 
		 if (Parcourshaelfte == 0){
			 
			 
			if(abstand < (soll - 10)){
				setSpeedR(1); 
				setSpeedL(2);
			}
			if(abstand > (soll + 10)){
				setSpeedL(1);
				setSpeedR(2);    
			}
		 }
		 if (Parcourshaelfte == 1){
				if(abstand < (soll - 10)){
					setSpeedR(2); 
					setSpeedL(1);
				}
				if(abstand > (soll + 10)){
					setSpeedL(2);
					setSpeedR(1);  
				}
					 
		 }

		 if((abstand > 250) && (parcour2 == 0)){
			    setSpeedL(1);
			 	setSpeedR(1);
			 	xFrequency = 5000; 
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 5500;
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 4500;
			 	setSpeedR(1);
			 	setSpeedL(1);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 5500;
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	setSpeedL(1); 
			 	setSensor(3); 
			 	xFrequency = 1000; 
			 	Parcourshaelfte = 1; 
			 	deletsens(1); 
			 	parcour2 = 1; 
			 }
	}
 
	}
	
	
//e = soll - getsens(Sensorn); 
 // up = e * Kp;      /* e: aktueller Fehler, Kp : P-faktor */
  //ui = ui_1 + Kp/Ti * e_1 * T; /*ui_1: ianteil vorher, Ti: faktor, e_1: Fehler vorher,T: abtastzeit */  
  //ud = Kp * Td *(e -e_1)/T;   /* Kd: D-faktor, e: aktueller Fehler, e_1: Fehler vorherh, T: abtastzeit */
	  /* 
	ui_1 = ui;
	e_1 = e;
		    
	v_k = up + ui + ud;
		    
		    if (v_k > u_max){
		        u_k = u_max;}
		    
		    else{
		    	if( v_k < u_min){
		    
		        u_k = u_min;}
		    else{
		        u_k = v_k;}
		    }
		    
  setspeed(u_k);  */

}
		   
	  
		    
	    
void setsoll(uint16_t s){
  if ((s < 200) & (s > 25)){
	  soll = s; 
  }
}

void setSensor(uint8_t s){
	if((s < 5) & (s >= 0)){
		Sensorn = s; 
		setsens(s); 
	}
}
	
void setspeed(int16_t uk){
	if((uk < 20) & (uk > -20)){
		setSpeedR(2); 
	}
	else{	
	
	if(uk>0){
		
		setSpeedR(3); 
	}
	else{
		setSpeedR(1); 
	}
}
}


