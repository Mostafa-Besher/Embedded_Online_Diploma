/*
 * SPI_EIGHT_7Segments.c
 *
 * Created: 9/4/2021 5:47:30 PM
 * Author : MOSTAFA
 */ 

#define F_CPU	1000000UL
#include "MCAL/SPI.h"
#include <util/delay.h>



void SPI_Decoder_Send_Data(uint8_t cmd, uint8_t data)
{
	//Send Command
	Clear_bit(PORTB, SS);		//make slave_select(SS) low
	SPI_Send_Data(cmd);
	//Send Data
	SPI_Send_Data(data);
	Set_bit(PORTB,SS);			//make slave_select(SS) high
}

int main(void)
{
	int seg_no, seg_data = 0;
	SPI_INIT();
	SPI_Decoder_Send_Data(0x09,0xFF);		//decode all displays
	SPI_Decoder_Send_Data(0x0B,0x07);		//Set scan limit(from digit 0 to digit 7)
	SPI_Decoder_Send_Data(0x0A,0x0F);		//Max intensity
	SPI_Decoder_Send_Data(0x0C,0x01);		//Normal Operation Mode (Turn on Display)
    while (1) 
    {
		for(seg_no=1; seg_no <=8; seg_no++,seg_data++)
		{
			SPI_Decoder_Send_Data(seg_no,seg_data);
			_delay_ms(500);
		}
    }
}

