/*
 * US.h
 *
 *  Created on: May 12, 2021
 *      Author: MostafaBesher
 */

#ifndef US_H_
#define US_H_


#include "state.h"

//define states
enum
{
	us_busy
}US_state_id;


//functions prototypes
STATE_DEFINE(US_busy);

void US_init();

//global pointer to function
extern void (*US_state)();


#endif /* US_H_ */
