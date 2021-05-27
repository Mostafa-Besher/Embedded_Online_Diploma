/*
 * state.h
 *
 *  Created on: May 18, 2021
 *      Author: MostafaBesher
 */

#ifndef STATE_H_
#define STATE_H_


//automatic state function generate
#define STATE_DEFINE(_state_func_)		void st_##_state_func_()
#define STATE(_state_func_)				st_##_state_func_


//states connections
void set_pressure_value (int pvalue);
void High_pressure_detect();


#endif /* STATE_H_ */
