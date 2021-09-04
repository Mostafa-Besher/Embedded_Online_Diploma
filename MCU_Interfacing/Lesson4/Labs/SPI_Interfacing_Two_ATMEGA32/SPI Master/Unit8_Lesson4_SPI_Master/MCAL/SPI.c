/*
 * SPI.c
 *
 * Created: 9/3/2021 7:41:57 PM
 *  Author: MOSTAFA
 */ 

#include "MCAL/SPI.h"


void SPI_INIT(void)
{
	//Enable SPI
	Set_bit(SPCR, 6);
	//bit order -->from LSB to MSB
	Set_bit(SPCR, 5);
	//Select SPI mode Master or Slave
	#ifdef MASTER_MODE
	Set_bit(SPCR, 4);
	Set_bit(DDRB,MOSI);				//set MOSI as output
	Clear_bit(DDRB,MISO);			//set MISO as input
	Set_bit(DDRB,SCK);				//set SCK as output
	Set_bit(DDRB,SS);				//set SS as output
	#endif
	
	#ifdef SLAVE_MODE
	Clear_bit(SPCR, 4);
	Clear_bit(DDRB,MOSI);			//set MOSI as input
	Set_bit(DDRB,MISO);				//set MISO as output
	Clear_bit(DDRB,SCK);			//set SCK as input
	Clear_bit(DDRB,SS);				//set SS as input
	#endif
	//select clock polarity -->leading edge = rising
	Clear_bit(SPCR, 3);		
	//select clock phase -->sample on leading edge
	Clear_bit(SPCR, 2);	
	//select clock rate -->FOSC/4
	Clear_bit(SPCR, 1);
	Clear_bit(SPCR, 0);
}


void SPI_Send_Data(uint8_t data)
{
	SPDR = data;
	//wait for SPIF to be set
	while(! (SPSR & (1<<7)));
}


uint8_t SPI_Recieve_Data(void)
{
	while(! (SPSR & (1<<7)));
	return SPDR;
}