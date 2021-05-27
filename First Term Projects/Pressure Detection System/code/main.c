/*
 * main.c
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "driver.h"
#include "pressure_sensor.h"
#include "alarm.h"
#include "algorithm.h"


void setup();


int main (){
	
	setup();
	while(1)
	{
		ps_state();
		alg_state();
		al_state();
	}		

}



void setup()
{
	//initialize GPIO driver
	GPIO_INITIALIZATION();
	//initialize all blocks
	//set state pointers intial values
	ps_state  = STATE(pressure_reading);
	alg_state = STATE(check_high_pressure);
	al_state  = STATE(stop_alarm);
}
