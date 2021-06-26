/*
 * GccApplication1.c
 *
 * Created: 6/26/2021 7:41:54 PM
 * Author : mostafa
 */ 

#define  F_CPU  8000000UL
#include "util/delay.h"
#include <avr/interrupt.h>
#include <stdint.h>
//GPIO adresses
#define	DDRB	*((volatile uint8_t *)(0x37))
#define	DDRD	*((volatile uint8_t *)(0x31))
#define	PORTD	*((volatile uint8_t *)(0x32))
//interrupt_unit adresses
#define	GICR	*((volatile uint8_t *)(0x5B))
#define	SREG	*((volatile uint8_t *)(0x5F))
#define	MCUCR	*((volatile uint8_t *)(0x55))
#define	MCUCSR	*((volatile uint8_t *)(0x54))
#define	GIFR	*((volatile uint8_t *)(0x5A))
//prototypes
void GPIo_init(void);

int main (void)
{
	GPIo_init();
	PORTD = 0x00;
	//Enable external interrupt for INT0,INT1,INT2 in interrupt_unit module
	GICR |= (0b111<<5);
	//Enable interrupt to CPU
	SREG |= 1<<7;
	//configure INT1 as rising edge
	MCUCR |= (0b11<<2);
	//configure INT0 as any logical change
	MCUCR |= 1<<0;
	//configure INT1 as falling edge
	MCUCSR &= ~(1<<6);
	while(1)
	{
		//turn off led at portD pin 7
		PORTD &= ~(1<<5);
		//turn off led at portD pin 6
		PORTD &= ~(1<<6);
		//turn off led at portD pin 7
		PORTD &= ~(1<<7);
	}
}

void GPIo_init(void)
{
	//configure pin PB2 direction as input
	DDRB &= ~(1<<2);
	//configure pins PD2,PD3 direction as input
	DDRD &= ~(0b11<<2);
	//configure pins PD5,PD6,PD7 direction as output
	DDRD |= (0b111<<5);
}

ISR(INT0_vect)
{
	//turn on led at portD pin 5
	PORTD |= 1<<5;
	//delay for 1 sec
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	//turn on led at portD pin 6
	PORTD |= 1<<6;
	//delay for 1 sec
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	//turn on led at portD pin 7
	PORTD |= 1<<7;
	//delay for 1 sec
	_delay_ms(1000);
}








