/*
 * Unit7_lesson1_section_assignment2.c
 *
 * Created: 7/9/2021 12:57:01 AM
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
	//make portC pin0 as input
	Clear_bit(DDRC, 0);
	//activate internal pull-up
	Set_bit(PORTC, 0);
    while (1) 
    {
		//check if button connected to pinC0 is pressed
		if(Read_bit(PINC, 0) == 0)
		{
			//turn on 8 LEDS one by one from first pin on all portA pins
			for(i=0; i<8; i++)
			{
				Set_bit(PORTA, i);
				_delay_ms(250);
			}
			PORTA = 0x00;
		}
    }
}

