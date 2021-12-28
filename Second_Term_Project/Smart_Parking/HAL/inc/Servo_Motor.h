/*
 * Servo_Motor.h
 *
 *  Created on: Nov 12, 2021
 *      Author:  Mostafa Mahmoud Elshiekh
 */



#ifndef SERVO_MOTOR_SERVO_MOTOR_H_
#define SERVO_MOTOR_SERVO_MOTOR_H_

#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"
#include "Timer.h"

//Direction of motion
#define UP   1
#define Down 2

void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);





#endif /* SERVO_MOTOR_SERVO_MOTOR_H_ */
