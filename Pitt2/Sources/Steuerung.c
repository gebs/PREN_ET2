/*
 * Steuerung.c
 *
 *  Created on: Apr 27, 2017
 *      Author: famga
 */
# include "Steuerung.h"



typedef enum {
	WAIT, /* device not used */
	START, /* started trigger pulse */
	TREPPE, /* measuring echo pulse */
	VERSCHRAENKUNG, /* measurement took too long */
	KURVE,
	WIPPE, 
	ZIEL, 
	STOP/* measurement finished */
} Estate;


Estate state; 
uint16_t abstand; 
uint16_t soll = 130; 
uint8_t Sensorn = 0; 
uint8_t startsignal = 1; 
/* Konstanten */





void Steuerung(void *pvParameters) {
	(void) pvParameters; 
	TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	

	for(;;){
		xFrequency = 200; 
		FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
		switch (state){
		case WAIT: 
			
			break; 
		case START: 
			motorstart(); 
	  		  if(links == 1){
	  			start(1);   
	  		  }
	  		  if(links == 0){
	  			start(3); 
	  		  }
	  		xFrequency = 3500;
	  	    FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			break; 
		case TREPPE: 
	  		 setSpeedR(2); 
	  		 setSpeedL(2); 
	  		 xFrequency = 9000;
	  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			break; 
		case VERSCHRAENKUNG: 
			  
			 abstand = getsens(Sensorn); 
			 setSpeedR(1); 
			 setSpeedL(1); 
 
				if(abstand < (soll - 10)){
					setSpeedR(2); 
					setSpeedL(1);
				}
				if(abstand > (soll + 10)){
					setSpeedL(2);
					setSpeedR(1);    
				}
			 

						 
			 
			 if(abstand > 250){
				 state = KURVE; 
			 }
			break; 
		case KURVE: 
			if(links == 0){
					setSpeedL(1);
				 	setSpeedR(1);
				 	xFrequency = 2800; 
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	xFrequency = 3600;
				 	setSpeedL(1000);
				 	setSpeedR(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	xFrequency = 3000;
				 	setSpeedR(1);
				 	setSpeedL(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	xFrequency = 3600;
				 	setSpeedL(1000);
				 	setSpeedR(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	setSpeedL(1); 
				 	setSensor(1); 
				 	xFrequency = 2000; 
				 	deletsens(3); 
				 	setsoll(50); 
				 	state = WIPPE;}
			
			if (links == 1){
			    setSpeedL(1);
			 	setSpeedR(1);
			 	xFrequency = 2800; 
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 3600;
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 3000;
			 	setSpeedR(1);
			 	setSpeedL(1);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 3600;
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	setSpeedL(1); 
			 	setSensor(3); 
			 	xFrequency = 2000; 
			 	deletsens(1); 
			 	setsoll(50);     
			 	state = WIPPE; 
			}
			
			break; 
		case WIPPE: 
			 
			setSpeedR(1); 	 
			setSpeedL(1); 
			abstand = getsens(Sensorn); 
			if(abstand < (soll - 10)){
				setSpeedR(1); 
				setSpeedL(2);
			}
			if(abstand > (soll + 10)){
				setSpeedL(1);
				setSpeedR(2);  
			}
			
			break; 
		case ZIEL: 
			 setSpeedR(2); 
			 setSpeedL(2); 
			abstand = getsens(Sensorn); 
			if(abstand < (soll - 5)){
				setSpeedR(2); 
				setSpeedL(4);
			}
			if(abstand > (soll + 5)){
				setSpeedL(2);
				setSpeedR(4);  
			}
			
			break;
		case STOP: 
			motorstop(); 
			break; 
		}

}
		   
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

void setParcourseite(uint8_t s){
	if (s== 0){
	links = s; }
	if (s== 1){
    links = s; 
	}
}
void start(uint8_t sensor){
	 setSpeedR(1); 
	 setSpeedL(1); 
	 setSensor(sensor);
}


void StateMachine(void *pvParameters) {
	(void)pvParameters; //parameter not used 
    
    TickType_t xLastWakeTime;
    TickType_t xFrequency = 10;		//muss die Statemaschine "ausgebremst" werden?
    xLastWakeTime = xTaskGetTickCount(); 
    
    
    
    for(;;) {
   // do something
  	  
  	  xFrequency = 200; //Test Wert
  	  FRTOS1_vTaskDelayUntil(&xLastWakeTime,xFrequency/portTICK_RATE_MS); 	// wait milisec
  	  
  	  switch(state){
  	  case WAIT:
  		  if(startsignal == 1){
  	       state = START; 
  		  }
	
  	  	  
  	  	  break;
  	  case START:

  		 xFrequency = 3500;
  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
  	     
  	     state = TREPPE; 
  		  break;
  	  case TREPPE:

  		 xFrequency = 9000;
  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
  	     state = VERSCHRAENKUNG; 
  	     
  		  break;
  	  case VERSCHRAENKUNG:
          
  		  
  		  break;
  	  case KURVE:

  		  break;
  	  case WIPPE:
  		         xFrequency = 25000;
  		  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
  		  	     state = ZIEL; 
  		  break;
  	  case ZIEL:
	         xFrequency = 8000;
	  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
	  	     state = STOP; 
  		  break;
  	  case STOP:
			setSpeedL(1000);
			setSpeedR(1000); 
  		  break; 
  	  
  	  }
  	  
  	  
  	  
  	 
    }
  }

