/*
 * pressure_sensor.c
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#include "pressure_sensor.h"


volatile int ps_val = 0;
void (*ps_state)();


STATE_DEFINE(pressure_reading)
{
	ps_state_id = ps_pressure_reading;
	ps_val = getPressureVal();
	set_pressure_value (ps_val);
	ps_state = STATE(pressure_reading);
}


