/*
 * main.c
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#include <stdio.h>
#include <stdlib.h>
#include "CA.h"
#include "US.h"
#include "DC.h"

void setup ()
{
	//initialize all drivers
	//initialize IRQ
	//initialize HAL US_DRIVER DC_DRIVER
	//initialize all blocks
	US_init();
	DC_init();
	//set states pointers for each block
	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);

}


int main()
{
	volatile int d;

	setup();

	while(1)
	{
		//call state for each block
		US_state();
		CA_state();
		DC_state();
		for(d=0; d<=1000; d++);
	}

	return 0;
}



