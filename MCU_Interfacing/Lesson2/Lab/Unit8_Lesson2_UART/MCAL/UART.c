/*
 * UART.c
 *
 * Created: 8/20/2021 9:00:43 PM
 *  Author: MOSTAFA
 */ 


/*===================================================================
					  INCLUDE HEADERS
*===================================================================*/

#include "MCAL/UART.h"



/*===================================================================
					  GLOBAL VARIABLES
*===================================================================*/

char recieve_string[20];


/*===================================================================
					    UART APIS
*===================================================================*/

void UART_Init(void)
{
	//ENABLE TX, RX
	Set_bit(UCSRB, 3);
	Set_bit(UCSRB, 4);
	
	//select asynchronous mode
	Set_bit(UCSRC, 7);		//this bit must be set to select writing to UCSRC register,because
							//it has the same address of UBBRH register
	Clear_bit(UCSRC, 6);
	
	//set baud rate value
	UBBRL = 51;				//set baud rate speed = 9600 bit/sec, hint : FOSC = 8 MHZ
	
	/*===============FRAME CONFIGURATION===============*/
	
	//select 8 bits of data
	//Bit 2:1 – UCSZ1:0: Character Size
	//The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits
	Set_bit(UCSRC, 0);
	Set_bit(UCSRC, 1);
	Clear_bit(UCSRB, 2);
	
	//no parity(parity disabled)
	//• Bit 5:4 – UPM1:0: Parity Mode
	Clear_bit(UCSRC, 4);
	Clear_bit(UCSRC, 5);
	
	//select only one bit for stop
	//Bit 3 – USBS: Stop Bit Select
	//This bit selects the number of Stop Bits to be inserted by the Transmitter.
	//The Receiver ignores this setting
	Clear_bit(UCSRC, 3);
}


void UART_send_data(uint8_t data)
{
	//check for TX data register is empty, if BIT 5 : UDRE is one --> register is empty
	while(Read_bit(UCSRA, 5) == 0);
	//send data
	UDR = data;
}


uint8_t UART_recieve_data(void)
{
	//check for reception complete flag
	while(Read_bit(UCSRA, 7) == 0);
	//receive data
	return UDR;
}


void UART_send_string(char * str)
{
	while(*str != '\0')
	{
		UART_send_data(*str);
		str++;
	}
}


char * UART_recieve_string(void)
{
	uint8_t data= UART_recieve_data();
	int i = 0;
	while(data != '#')
	{
		recieve_string[i] = data;
		data = UART_recieve_data();
		i++;
	}
	recieve_string[i] = '\0';
	return recieve_string;
}

