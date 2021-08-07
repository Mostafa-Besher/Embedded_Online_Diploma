/*
 * keypad.h
 *
 * Created: 7/28/2021 3:06:53 PM
 *  Author: mostafa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO.h"
#include "utilis.h"

#define KEYPAD_PORT	PORTA
#define KEYPAD_Dir	DDRA
#define KEYPAD_Pin	PINA
#define R0			0
#define R1			1
#define R2			2
#define R3			3
#define C0			4
#define C1			5
#define C2			6
#define C3			7

//APIS
void keypad_init(void);
char keypad_get_key(void);




#endif /* KEYPAD_H_ */