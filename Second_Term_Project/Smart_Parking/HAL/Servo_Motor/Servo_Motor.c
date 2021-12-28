/*
 * Sorce_Motor.c
 *
 *  Created on: Nov 12, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */

#include "Servo_Motor.h"





//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_Pinconfig_t PinCinfg;
	PinCinfg.PinNumber=GPIO_PIN_8;
	PinCinfg.Mode = GPIO_MODE_Output_PP;
	PinCinfg.Output_speed =GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}
	if(Direction == Down)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_Pinconfig_t PinCinfg;
	PinCinfg.PinNumber=GPIO_PIN_9;
	PinCinfg.Mode = GPIO_MODE_Output_PP;
	PinCinfg.Output_speed =GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

}
