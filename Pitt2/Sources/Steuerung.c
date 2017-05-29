/*
 * Steuerung.c
 *
 *  Created on: Apr 27, 2017
 *      Author: famga
 */
# include "Steuerung.h"



typedef enum {
	WAIT, 
	START, 
	TREPPE, 
	VERSCHRAENKUNG, 
	KURVE,
	WIPPE, 
	ZIEL, 
	STOP
} Estate;


Estate state; 
uint16_t abstand; 
uint16_t soll = 130; 
uint8_t Sensorn = 0; 
bool links;
uint8_t startsignal = 1; 
int raspiValue;

/* Konstanten */





void Steuerung(void *pvParameters) {
	(void) pvParameters; 
	TickType_t xFrequency = 10;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	int toleranz = 10;

	for(;;){
		xFrequency = 200; 
		FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
		switch (state){
		case WAIT: 
			deletsens(0); 
			deletsens(1); 
			deletsens(2); 
			deletsens(3); 
			deletsens(4); 
			raspiValue = getRaspiSignal(); 	
			if( raspiValue == 7){			
				state = START;
			}
			
			break; 
		case START: 
			getParcourseite();
			motorstart(); 
			
	  		  if(links == 1){
	  			start(2);   
	  			//Sensorn = 1; //TEST 25.05.17
	  		  }
	  		  if(links == 0){
	  			start(3); 
	  			//Sensorn = 3; //TEST 25.05.17
	  	      }
	  		  
	  		xFrequency = 3500;
	  	    FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			break; 
		case TREPPE: 
	  		 setSpeedR(2); 
	  		 setSpeedL(2); 
	  		 xFrequency = 12000;
	  	     FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			break; 
		case VERSCHRAENKUNG: 
	
			 abstand = getsens(Sensorn); 
			 setSpeedR(1); 
			 setSpeedL(1); 
			 if(links){
				if(abstand < (soll - toleranz)){
					setSpeedR(1); 
					setSpeedL(2);
				}
				if(abstand > (soll + toleranz)){
					setSpeedL(1);
					setSpeedR(2);    
				}
			 }else{
					if(abstand < (soll - toleranz)){
						setSpeedR(2); 
						setSpeedL(1);
					}
					if(abstand > (soll + toleranz)){
						setSpeedL(2);
						setSpeedR(1);    
					}
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
				 	xFrequency = 3600; //angepasst original 3600
				 	setSpeedL(1000);
				 	setSpeedR(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	xFrequency = 2700;
				 	setSpeedR(1);
				 	setSpeedL(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	xFrequency = 3600; //angepasst original 3600
				 	setSpeedL(1000);
				 	setSpeedR(1);
				 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
				 	setSpeedL(1); 
				 	deletsens(3);
				 	setSensor(2); 
				 	setsoll(50);
				 	xFrequency = 2000; 
				 	 
				 	 
				 	state = WIPPE;}
			
			if (links == 1){
			    setSpeedL(1);
			 	setSpeedR(1);
			 	xFrequency = 2800; 
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 3600; //angepasst original 3600
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 2700;
			 	setSpeedR(1);
			 	setSpeedL(1);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	xFrequency = 3600;//angepasst original 3600
			 	setSpeedL(1);
			 	setSpeedR(1000);
			 	FRTOS1_vTaskDelayUntil(&xLastWakeTime, xFrequency/portTICK_RATE_MS);
			 	setSpeedL(1); 
			 	deletsens(2); 
			 	setSensor(3); 
			 	setsoll(50);
			 	xFrequency = 2000; 
			 	
			 	     
			 	state = WIPPE; 
			}
			
			break; 
		case WIPPE: 
			raspiValue = getRaspiSignal() - 1; // -1 wegen array index evtl
			raspiValue = 3;		// für Testing
			if(0 <= raspiValue < 5){
				setsoll(getZifferSollAbstand(raspiValue));
			}else{
				setsoll(50);
			}
			setSpeedR(1); 	 
			setSpeedL(1); 
			abstand = getsens(Sensorn); 
			 if(links){
				if(abstand < (soll - toleranz)){
					setSpeedR(2); 
					setSpeedL(1);
				}
				if(abstand > (soll + toleranz)){
					setSpeedL(2);
					setSpeedR(1);    
				}
			 }else{
					if(abstand < (soll - toleranz)){
						setSpeedR(1); 
						setSpeedL(2);
					}
					if(abstand > (soll + toleranz)){
						setSpeedL(1);
						setSpeedR(2);    
					}
			 }
	
			break; 
		case ZIEL: 
			 setSpeedR(2); 
			 setSpeedL(2); 

			abstand = getsens(Sensorn);

			if(links){
				if(abstand < (soll - 5)){
					setSpeedR(4); 
					setSpeedL(2);
				}
				if(abstand > (soll + 5)){
					setSpeedL(4);
					setSpeedR(2);  
				}
			}else{
				if(abstand < (soll - 5)){
					setSpeedR(2); 
					setSpeedL(4);
				}
				if(abstand > (soll + 5)){
					setSpeedL(2);
					setSpeedR(4);  
				}
				
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

/*void setParcourseite(uint8_t s){
	if (s== 0){
	links = s; }
	if (s== 1){
    links = s; 
	}
}*/
void getParcourseite(void){
	links = Parcour_GetVal();
}

uint16_t getZifferSollAbstand(int ziffer){
	uint16_t z ;
	getParcourseite();
	if(links){
		uint16_t zifferAbstand[5] = {78, 133, 48, 108, 171};
		z = zifferAbstand[ziffer];
	}else{
		uint16_t zifferAbstand[5] = {174, 114, 50, 144, 76};
		z = zifferAbstand[ziffer];
	}
	return(z);
	
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
  		  if(startsignal == 1){ //nur für Testphase?? dann eliminieren??
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
			//setSpeedL(1000);
			//setSpeedR(1000); 
  		  	motorstop();
  		  break; 
  	  
  	  }
  	  
  	  
  	  
  	 
    }
  }

