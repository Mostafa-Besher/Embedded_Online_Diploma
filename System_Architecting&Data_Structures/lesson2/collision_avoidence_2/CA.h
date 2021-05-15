/*
 * CA.h
 *
 *  Created on: May 11, 2021
 *      Author: MostafaBesher
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

//define states
enum
{
	waiting,
	driving
}state_id;


//functions prototypes
STATE_DEFINE(CA_waiting);
STATE_DEFINE(CA_driving);


//global pointer to function
extern void (*CA_state)();


#endif /* CA_H_ */
