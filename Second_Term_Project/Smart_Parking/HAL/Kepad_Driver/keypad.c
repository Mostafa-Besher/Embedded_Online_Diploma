/*
 * keypad.c
 *
 * Created: 3/8/2021 3:06:37 PM
 *  Author: Mostafa
 */ 

#include "keypad.h"
#include "stdint.h"

uint16_t col[] = {C0,C1,C2};
uint16_t row[] = {R0,R1,R2,R3};


void keypad_init(void)
{
	GPIO_Pinconfig_t  pin_cfg;
	//select rows as input internal pull-down
	int k;
	for(k=0; k<4; k++)
	{
		pin_cfg.PinNumber = row[k];
		pin_cfg.Mode = GPIO_MODE_Input_PD;
		MCAL_GPIO_Init(KEYPAD_Dir, &pin_cfg);
	}
	//select columns as output push-pull
	for(k=0; k<3; k++)
	{
		pin_cfg.PinNumber = col[k];
		pin_cfg.Mode = GPIO_MODE_Output_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(KEYPAD_Dir, &pin_cfg);
	}
}


char keypad_get_key(void)
{
	int i, j;
	int k;
	char keypad_keys[4][3] = {{'*','0','#'},
							  {'7','8','9'},
							  {'4','5','6'},
						      {'1','2','3'}};
							  
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 4; j++)
		{
			//clear all columns
			for(k=0; k<3; k++)
			{
				MCAL_GPIO_WritePin(KEYPAD_PORT, col[k], WRITE_PIN_LOW);
			}
			//set specific column
			MCAL_GPIO_WritePin(KEYPAD_PORT, col[i], WRITE_PIN_HIGH);
			//check pressed key
			if(MCAL_GPIO_ReadPin(KEYPAD_Pin, row[j]) == READ_PIN_HIGH)
			{
				//single pressing
				while(MCAL_GPIO_ReadPin(KEYPAD_Pin, row[j]) == READ_PIN_HIGH);
				return keypad_keys[j][i];
			}
		}
	}
	return 'N';
}
