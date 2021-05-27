/*
 * algorithm.h
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "driver.h"
#include "state.h"
#include "pressure_sensor.h"
#include "alarm.h"

STATE_DEFINE(check_high_pressure);


enum
{
	alg_High_pressure_detect
}alg_state_id;


extern void (*alg_state)();



#endif	/* ALGORITHM_H_ */