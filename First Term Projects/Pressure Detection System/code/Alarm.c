/*
 * Alarm.c
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#include "Alarm.h"
void (*al_state)();


STATE_DEFINE(start_alarm)
{
	al_state_id = al_start_alarm;
	//start alarm
	Set_Alarm_actuator(0);
	Delay(1000000);
	Set_Alarm_actuator(1);
	al_state = STATE(stop_alarm);
}


STATE_DEFINE(stop_alarm)
{
	al_state_id = al_stop_alarm;
	//stop alarm
	Set_Alarm_actuator(1);
}


void High_pressure_detect()
{
	al_state = STATE(start_alarm);
}






