/*
 * Raspi.c
 *
 *  Created on: May 11, 2017
 *      Author: Martina M
 */

#include "Raspi.h"


int getRaspiSignal(){
	bool Rasp0;
	bool Rasp1;
	bool Rasp2;
	int value = 0;
	Rasp0 = Rasp0_GetVal();
	Rasp1 = Rasp1_GetVal();
	Rasp2 = Rasp2_GetVal();
	
	if(Rasp0){				// Umrechnung in eine Integer Zahl
		value = value + 1;
	}
	if(Rasp1){
		value = value + 2;
	}
	if(Rasp2){
		value = value + 4;
	}						// 
	return value;
}
