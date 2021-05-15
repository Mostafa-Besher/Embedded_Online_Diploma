/*
 * CA.c
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#include <stdio.h>
#include <stdlib.h>
#include "CA.h"
#include "state.h"


//global variables
unsigned int speed = 0;
unsigned int distance = 0;
unsigned int threshold = 50;

//global pointer to function
void (*CA_state)();



STATE_DEFINE(CA_waiting)
{
	//state name
	state_id = waiting;
	printf("CA Waiting state : distance = %d speed = %d\n", distance, speed);
	//state action
	speed = 0;
	DC_set_speed(speed);

}


STATE_DEFINE(CA_driving)
{
	//state name
	state_id = driving;
	printf("CA Driving state : distance = %d speed = %d\n", distance, speed);
	//state action
	speed = 30;
	DC_set_speed(speed);
}


void US_set_distance(int d)
{
	distance = d;
	//check event
	(distance <= threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	printf("US-----------distance = %d-------------->CA\n", distance);
}


