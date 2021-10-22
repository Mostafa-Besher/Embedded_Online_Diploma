/*
 * ADC.h
 *
 * Created: 10/20/2021 5:58:43 PM
 *  Author: mostafa
 */ 


#ifndef ADC_H_
#define ADC_H_


//-----------------------------
//Includes
//-----------------------------

#include <stdint.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#include "GPIO.h"



//-----------------------------
//ADC Registers
//-----------------------------

#define ADCL			*((volatile uint8_t *)(0x24))
#define ADCH			*((volatile uint8_t *)(0x25))
#define ADCSRA			*((volatile uint8_t *)(0x26))
#define ADMUX			*((volatile uint8_t *)(0x27))
#define SFIOR			*((volatile uint8_t *)(0x50))


//SREG register used for enabling Global Interrupt
#define SREG			*((volatile uint8_t *)(0x5F))


//--------------------------------------
//User type definitions (structures)
//--------------------------------------

typedef struct
{
	uint8_t				ADC_MODE;						// specifies ADC Mode (Single conversion mode or Free running mode)
														// This parameter must be set based on @ref ADC_MODE_DEFINE
	
	uint8_t				ADC_Voltage_REF;				// Selects ADC VREF source
														// This parameter must be set based on @ref ADC_Voltage_REF_DEFINE
														
	uint8_t				ADC_Result_Presentation;		// specifies ADC Output result presentation(right adjusted or left adjusted)
														// This parameter must be set based on @ref ADC_Result_Presentation_DEFINE				
														
	uint8_t				ADC_PRESCALER;					// Selects the division factor between the XTAL frequency and the input clock to ADC
														// This parameter must be set based on @ref ADC_PRESCALER_DEFINE
														
	uint8_t				IRQ_Enable;						// Enable interrupt or Disable it and use polling mechanism
														// This parameter must be set based on @ref IRQ_ENABLE_DEFINE
														
	void (*P_CallBack)(void);							//set the C Function which will be called once IRQ Happens when Conversion completed	
							
}ADC_CONFIG_t;



//-----------------------------------
//Macros Configuration References
//-----------------------------------

//@ref ADC_MODE_DEFINE
#define ADC_MODE_SINGLE_CONVERSION							((uint8_t)(0))				//Clear ADATE in ADCSRA
#define ADC_MODE_FREE_RUNNING								((uint8_t)(1<<5))			//set ADATE in ADCSRA

//@ref ADC_Voltage_REF_DEFINE
#define ADC_Voltage_REF_AVCC								((uint8_t)(1<<6))
#define ADC_Voltage_REF_INTERNAL							((uint8_t)((1<<6) | (1<<7)))
#define ADC_Voltage_REF_EXTERNAL_AREF						((uint8_t)(0))

//@ref ADC_Result_Presentation_DEFINE
#define ADC_Result_Presentation_RIGHT_ADJUSTED				((uint8_t)(0))
#define ADC_Result_Presentation_LEFT_ADJUSTED				((uint8_t)(1<<5))			//ADLAR bit in ADMUX

//@ref ADC_PRESCALER_DEFINE	
#define ADC_PRESCALER_DIVUDED_BY_2							((uint8_t)(0x00))
#define ADC_PRESCALER_DIVUDED_BY_4							((uint8_t)(0x02))
#define ADC_PRESCALER_DIVUDED_BY_8							((uint8_t)(0x03))
#define ADC_PRESCALER_DIVUDED_BY_16							((uint8_t)(0x04))
#define ADC_PRESCALER_DIVUDED_BY_32							((uint8_t)(0x05))
#define ADC_PRESCALER_DIVUDED_BY_64							((uint8_t)(0x06))
#define ADC_PRESCALER_DIVUDED_BY_128						((uint8_t)(0x07))

//@ref IRQ_ENABLE_DEFINE
#define IRQ_ENABLE_NONE										((uint8_t)(0))			
#define IRQ_ENABLE_ADIE										((uint8_t)(1<<3))	

//ENABLE/DISABLE GLOBAL INTERRUPT MACROS
#define ENABLE_GLOBAL_INTERRUPT								(SREG |= 1<<7)
#define DISABLE_GLOBAL_INTERRUPT							(SREG &= ~(1<<7))



typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}Channel_Select_t;


typedef enum
{
	Polling_ENABLE,
	Polling_DISABLE
}Polling_Mechanism_t;




/*
* ==============================================================================
* 				  APIs Supported by "MCAL ADC DRIVER"
* ==============================================================================
*/

void MCAL_ADC_Init(ADC_CONFIG_t * ADC_Cfg);
void MCAL_ADC_DeInit(void);
void MCAL_ADC_Start_Conversion(void);
void MCAL_ADC_Get_Result_Data(Channel_Select_t channel, uint16_t * data, Polling_Mechanism_t Polling);




#endif /* ADC_H_ */