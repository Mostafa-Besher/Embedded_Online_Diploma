/*
 * state.h
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#ifndef STATE_H_
#define STATE_H_


//automatic state function generate
#define STATE_DEFINE(_state_func_)		void st_##_state_func_()
#define STATE(_state_func_)				st_##_state_func_


//states connections
void US_set_distance(int d);
void DC_set_speed(int s);


#endif /* STATE_H_ */
