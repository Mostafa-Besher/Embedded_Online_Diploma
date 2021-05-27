/*
 * pressure_sensor.h
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "driver.h"
#include "state.h"

STATE_DEFINE(pressure_reading);


enum
{
	ps_pressure_reading,
	ps_waiting
}ps_state_id;


extern void (*ps_state)();


#endif /* PRESSURE_SENSOR_H_ */
