/*
 * algorithm.c
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */
#include "algorithm.h"


volatile int pval = 0;
volatile int threshold = 20;
void (*alg_state)();

void set_pressure_value (int pvalue)
{
	pval = pvalue;
}

STATE_DEFINE(check_high_pressure)
{
	alg_state_id = alg_High_pressure_detect;
	//check high pressure detection to start alarm
	if((pval <= threshold))
	{
		alg_state = STATE(check_high_pressure);
	}
		
	else
	{
		High_pressure_detect();
		alg_state = STATE(check_high_pressure);
	}
}