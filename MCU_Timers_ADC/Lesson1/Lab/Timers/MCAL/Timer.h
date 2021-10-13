/*
 * Timer.h
 *
 * Created: 10/11/2021 2:40:19 AM
 *  Author: MostafaBesher
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//-----------------------------
//Includes
//-----------------------------

#include <stdint.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#include "GPIO.h"



//-----------------------------
//TIMER Registers
//-----------------------------


#define	TCCR0			*((volatile uint8_t *) (0x53))
#define	TCNT0			*((volatile uint8_t *) (0x52))
#define	OCR0			*((volatile uint8_t *) (0x5c))
#define	TIMSK			*((volatile uint8_t *) (0x59))
#define	TIFR			*((volatile uint8_t *) (0x58))

//SREG register used for enabling Global Interrupt
#define SREG			*((volatile uint8_t *)(0x5F))




//--------------------------------------
//User type definitions (structures)
//--------------------------------------


typedef struct
{
	uint8_t		Timer_Mode;					// specifies Timer Mode (Normal mode or CTC)
											// This parameter must be set based on @ref TIMER_MODE_DEFINE
											
	uint8_t		Clock_Source;				// specifies Timer Clock Source (External / Internal) and PreScaler with internal clock only
											// This parameter must be set based on @ref CLOCK_SOURCE_DEFINE
											
	uint8_t		IRQ_Enable;					// Enable or Disable IRQ
											// This parameter must be set based on @ref IRQ_ENABLE_DEFINE
											
	void (*P_CallBack)(void);				//set the C Function which will be called once IRQ Happens
	
}TIMER_CONFIG_t;





//-----------------------------------
//Macros Configuration References
//-----------------------------------

//@ref TIMER_MODE_DEFINE	
#define TIMER_MODE_NORMAL											((uint8_t)(0))
#define TIMER_MODE_CTC												((uint8_t)(1<<3))
#define TIMER_MODE_FAST_PWM_INVERTING								((uint8_t)(0x78))
#define TIMER_MODE_FAST_PWM_NONINVERTING							((uint8_t)(0x68))

//@ref CLOCK_SOURCE_DEFINE
#define CLOCK_SOURCE_INTERNAL_NO_PRESCALER							((uint8_t)(1<<0))	
#define CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_8				((uint8_t)(1<<1))
#define CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_64				((uint8_t)(0x03))
#define CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_256				((uint8_t)(0x04))
#define CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_1024				((uint8_t)(0x05))			
#define CLOCK_SOURCE_EXTERNAL_FALLING_EDGE							((uint8_t)(0x06))
#define CLOCK_SOURCE_EXTERNAL_RISING_EDGE							((uint8_t)(0x07))


//@ref IRQ_ENABLE_DEFINE
#define IRQ_ENABLE_NONE												((uint8_t)(0))
#define IRQ_ENABLE_TOIE0											((uint8_t)(1<<0))
#define IRQ_ENABLE_OCIE0											((uint8_t)(1<<1))


//ENABLE/DISABLE GLOBAL INTERRUPT MACROS
#define ENABLE_GLOBAL_INTERRUPT										(SREG |= 1<<7)
#define DISABLE_GLOBAL_INTERRUPT									(SREG &= ~(1<<7))




/*
* ==============================================================================
* 				  APIs Supported by "MCAL TIMER DRIVER"
* ==============================================================================
*/


void MCAL_Timer_Init(TIMER_CONFIG_t *Timer_Cfg);
void MCAL_Timer_Stop(void);
void MCAL_SetTimer_compare_val(uint8_t count);
void MCAL_TIMER_Get_Counterval(uint8_t *countVal);
void MCAL_PWM_DutyCycle(uint8_t duty_cycle);








#endif /* TIMER_H_ */