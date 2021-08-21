/*
 * UART.h
 *
 * Created: 8/20/2021 9:00:57 PM
 *  Author: MOSTAFA
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "MCAL/GPIO.h"


//UART REGISTERS
#define UDR			*((volatile uint8_t *)(0x2C))	//NOTE: same buffer used with transmitter & receiver
#define UCSRA		*((volatile uint8_t *)(0x2B))
#define UCSRB		*((volatile uint8_t *)(0x2A))
#define UCSRC		*((volatile uint8_t *)(0x40))
#define UBBRH		*((volatile uint8_t *)(0x40))	//NOTE : UBBRH register & UCSRC have the same address
#define UBBRL		*((volatile uint8_t *)(0x29))



//APIS
void UART_Init(void);
void UART_send_data(uint8_t data);
uint8_t UART_recieve_data(void);
void UART_send_string(char * str);
char * UART_recieve_string(void);





#endif /* UART_H_ */