/*
 * state.h
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#ifndef STATE_H_
#define STATE_H_


//automatic state function generate
#define state_define(_state_func_)		void st_##_state_func_()
#define state(_state_func_)				st_##_state_func_



#endif /* STATE_H_ */
