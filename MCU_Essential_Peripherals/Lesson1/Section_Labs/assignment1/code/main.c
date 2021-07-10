/*
 * Unit7_lesson1_section_assignment1.c
 *
 * Created: 7/9/2021 12:09:00 AM
 * Author : mostafa besher
 */ 

#include "GPIO_reg.h"
#include "Utils.h"
#define  F_CPU	8000000UL
#include <util/delay.h>


int main(void)
{
	int i;
	//make all portA pins output
	DDRA = 0xff;
    while (1) 
    {
		//turn on 8 LEDS one by one from first pin on all portA pins
		for(i=0; i<8; i++)
		{
			Set_bit(PORTA, i);
			_delay_ms(250);
		}
		//turn off 8 LEDS one by one from last pin on all portA pins
		for(i=7; i>=0; i--)
		{
			Clear_bit(PORTA, i);
			_delay_ms(250);
		}
		
    }
}

