/*
 * Unit8_Lesson4_SPI_Master.c
 *
 * Created: 9/3/2021 7:41:11 PM
 * Author : MOSTAFA
 */ 

#define F_CPU	1000000UL
#include "MCAL/SPI.h"
#include "util/delay.h"


int main(void)
{
	uint8_t data;
    SPI_INIT();
	DDRA = 0xFF; //set PORTA as output
    while (1) 
    {
		for(data=0; data<=255; data++)
		{
			SPI_Send_Data(data);
			PORTA = data;
			_delay_ms(500);
		}
	}
}

