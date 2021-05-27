/*
 * Alarm.h
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "driver.h"
#include "state.h"

STATE_DEFINE(start_alarm);
STATE_DEFINE(stop_alarm);


enum
{
	al_start_alarm,
	al_stop_alarm
}al_state_id;

extern void (*al_state)();

#endif /* ALARM_H_ */
