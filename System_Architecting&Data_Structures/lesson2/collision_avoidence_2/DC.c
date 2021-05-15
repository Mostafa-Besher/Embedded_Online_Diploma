/*
 * DC.c
 *
 *  Created on: May 12, 2021
 *      Author: MostafaBesher
 */
#include "stdio.h"
#include "DC.h"
#include "state.h"

void (*DC_state)();
unsigned int DC_speed = 0;

void DC_init()
{
	printf("DC init\n");
}


void DC_set_speed(int s)
{
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA-----------speed = %d-------------->DC\n", DC_speed);

}


STATE_DEFINE(DC_idle)
{
	//state name
	DC_state_id = dc_idle;
	//call pwm
	printf("DC_idle state : speed = %d \n", DC_speed);

}


STATE_DEFINE(DC_busy)
{
	//state name
	DC_state_id = dc_busy;

	//state action
	DC_state = STATE(DC_idle);
	//call PWM to make speed = DC_speed
	printf("DC_busy state : speed = %d \n", DC_speed);

}
