/*
 * keypad.h
 *
 * Created: 3/8/2021 3:06:53 PM
 *  Author: Mostafa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"
#include <stdlib.h>


#define KEYPAD_PORT		GPIOB
#define KEYPAD_Dir		GPIOB
#define KEYPAD_Pin		GPIOB
#define R0				GPIO_PIN_0
#define R1				GPIO_PIN_1
#define R2				GPIO_PIN_3
#define R3				GPIO_PIN_4
#define C0				GPIO_PIN_5
#define C1				GPIO_PIN_6
#define C2				GPIO_PIN_7
#define C3				GPIO_PIN_8

//APIS
void keypad_init(void);
char keypad_get_key(void);




#endif /* KEYPAD_H_ */
