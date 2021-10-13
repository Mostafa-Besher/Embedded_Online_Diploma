/*
 * Timers.c
 *
 * Created: 10/10/2021 11:48:57 PM
 * Author : MostafaBesher
 */ 

#define F_CPU	8000000UL
#include "Timer.h"
#include "util/delay.h"

uint32_t timer_counter = 0;


void Timer_OverFlow_Interrupt_Handler(void)
{
	timer_counter++;
	if(timer_counter == 3921)
	{
		//Toggle Led every one second
		Toggle_bit(PORTD, 0);
		//Clear Counter
		timer_counter = 0;
	}
}

void Timer_CompareMatch_Interrupt_Handler(void)
{
	timer_counter++;
	if(timer_counter == 10000)
	{
		//Toggle Led every one second
		Toggle_bit(PORTD, 0);
		//Clear Counter
		timer_counter = 0;
	}
}


int main(void)
{
	//Configure PIND0 as Output
    Set_bit(DDRD, 0);
	//set compare value
	MCAL_SetTimer_compare_val(100);
	//set timer configuration
	TIMER_CONFIG_t timer_cfg;
	timer_cfg.Timer_Mode = TIMER_MODE_CTC;
	timer_cfg.Clock_Source = CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_8;
	timer_cfg.IRQ_Enable = IRQ_ENABLE_OCIE0;
	timer_cfg.P_CallBack = Timer_CompareMatch_Interrupt_Handler;
	MCAL_Timer_Init(&timer_cfg);
    while (1) 
    {
		
    }
}

