/*
 * Unit7_lesson1_section_assingnment3.c
 *
 * Created: 7/10/2021 1:03:10 AM
 * Author : mostafa besher
 */ 

#include "GPIO_reg.h"
#include "Utils.h"
#define  F_CPU	8000000UL
#include <util/delay.h>

static int segment_arr[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xff,0x6f};
int main(void)
{
	int i;
	//make all pins in portC as output
    DDRC = 0xff;
    while (1) 
    {
		//loop to display all numbers from 0 to 9 on 7segment
		for(i=0; i<10; i++)
		{
			PORTC = segment_arr[i];
			_delay_ms(500);
		}
    }
}

