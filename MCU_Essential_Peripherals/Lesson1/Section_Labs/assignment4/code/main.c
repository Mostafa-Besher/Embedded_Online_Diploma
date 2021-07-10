/*
 * Unit7_lesson1_section_assignment4.c
 *display numbers from 0 to 99 using multiplexing 7segment
 * Created: 7/10/2021 1:54:15 PM
 * Author : mostafa besher
 */ 


#include "GPIO_reg.h"
#include "Utils.h"
#define  F_CPU	8000000UL
#include <util/delay.h>

static int segment_arr[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xff,0x6f};
int main(void)
{
	int i,j;
	//make all pins in portC as output
	DDRC = 0xff;
	//make pinA0,pinA1 as output
	Set_bit(DDRA, 0);
	Set_bit(DDRA, 1);
	while (1)
	{
		//loop to display all numbers from 0 to 99 on two 7segment by using multiplexing
		for(i=0; i<10; i++)
		{
			for(j=0; j<10; j++)
			{
				Set_bit(PORTA, 0);
				PORTC = segment_arr[i];
				_delay_ms(30);
				Clear_bit(PORTA, 0);
				Set_bit(PORTA, 1);
				PORTC = segment_arr[j];
				_delay_ms(30);
				Clear_bit(PORTA, 1);
			}
		}
	}
}

