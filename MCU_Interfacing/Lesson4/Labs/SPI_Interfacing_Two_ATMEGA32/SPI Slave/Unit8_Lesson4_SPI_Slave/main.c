/*
 * Unit8_Lesson4_SPI_Slave.c
 *
 * Created: 9/3/2021 10:04:29 PM
 * Author : mostafa
 */ 

#define F_CPU	1000000UL
#include "MCAL/SPI.h"
#include "util/delay.h"


int main(void)
{
	
	SPI_INIT();
	DDRA = 0xFF; //set PORTA as output
	while (1)
	{
		PORTA = SPI_Recieve_Data();
		_delay_ms(500);
	}
}

