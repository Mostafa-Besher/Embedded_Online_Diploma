/*
 * main.c
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#include <stdio.h>
#include <stdlib.h>
#include "CA.h"


void setup ();


int main()
{
	volatile int d;

	setup();

	while(1)
	{
		//call state for each block
		CA_state();
		for(d=0; d<=1000; d++);
	}

	return 0;
}


void setup ()
{
	//initialize all drivers
	//initialize IRQ
	//initialize HAL US_DRIVER DC_DRIVER
	//set states pointers for each block
	CA_state = state(CA_waiting);
}
