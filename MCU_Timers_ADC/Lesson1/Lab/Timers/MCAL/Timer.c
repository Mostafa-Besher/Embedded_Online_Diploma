/*
 * Timer.c
 *
 * Created: 10/11/2021 2:40:31 AM
 *  Author: MostafaBesher
 */ 


/*
 *=======================================================================
 *						INCLUDES
 *=======================================================================
 *
*/

#include "Timer.h"


/*
 *=======================================================================
 *						GLOBAL VARIABLES
 *=======================================================================
 *
*/

void (*GP_CallBack)(void) = NULL;

TIMER_CONFIG_t Global_Timer_Config;



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/


/**================================================================
 * @Fn 				-	MCAL_Timer_Init
 * @brief 			-	Initializes TIMER0 according to the specified parameters in Timer_Cfg
 * @param [in] 		- 	Timer_Cfg : a pointer to TIMER_CONFIG_t structure that contains
 * 									the configuration information for the specified TIMER Module
 * @retval 			-	none
 * Note 			-	Supported for TIMER0 ONLY
 *
 */
void MCAL_Timer_Init(TIMER_CONFIG_t *Timer_Cfg)
{
	Global_Timer_Config = *Timer_Cfg;
	
	//Select Timer Mode
	TCCR0 |= Timer_Cfg->Timer_Mode;
	if(Timer_Cfg->Timer_Mode == TIMER_MODE_FAST_PWM_INVERTING || Timer_Cfg->Timer_Mode == TIMER_MODE_FAST_PWM_NONINVERTING)
	{
		//Configure (OC0)PINB3 as output
		DDRB |= (1<<3);
	}
	
	//Select Clock Source
	TCCR0 |= Timer_Cfg->Clock_Source;
	if(Timer_Cfg->Clock_Source == CLOCK_SOURCE_EXTERNAL_FALLING_EDGE || Timer_Cfg->Clock_Source == CLOCK_SOURCE_EXTERNAL_RISING_EDGE)
	{
		//Configure T0 (pinB0) As input
		DDRB &= ~(1<<0);
	}
	
	//Enable Or Disable IRQ
	TIMSK |= Timer_Cfg->IRQ_Enable;
	if(Timer_Cfg->IRQ_Enable != IRQ_ENABLE_NONE)
	{
		//Enable Global Interrupt
		ENABLE_GLOBAL_INTERRUPT;
	}
	else
	{
		//Disable Global Interrupt
		DISABLE_GLOBAL_INTERRUPT;
	}
	
	//call back function address
	GP_CallBack = Timer_Cfg->P_CallBack;
	
}


/**================================================================
 * @Fn 				-	MCAL_Timer_Stop
 * @brief 			-	Stop Timer0 Operation By Disable Timer Clock
 * @retval 			-	none
 * Note 			-	Supported for TIMER0 ONLY
 *
 */
void MCAL_Timer_Stop(void)
{
	TCCR0 &= ~((1<<0) | (1<<1) | (1<<2));
}



/**================================================================
 * @Fn 				-	MCAL_SetTimer_compare_val
 * @brief 			-	Set OCR Register compare Value in Compare Match Mode(CTC)
 * @param [in] 		- 	count : Value to Set in OCR(compare value must not exceed 255)
 * @retval 			-	none
 * Note 			-	Supported for Compare Match Mode(CTC) only & compare value must not exceed 255
 *
 */
void MCAL_SetTimer_compare_val(uint8_t count)
{
	OCR0 = count;
}



/**================================================================
 * @Fn 				-	MCAL_TIMER_Get_Counterval
 * @brief 			-	Get Timer counter value
 * @param [in] 		- 	countVal : value of counter value from counter register (TCNT0)
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_TIMER_Get_Counterval(uint8_t *countVal)
{
	*countVal = TCNT0;
}



/**================================================================
 * @Fn 				-	MCAL_PWM_DutyCycle
 * @brief 			-	Set PWM duty cycle in Fast PWM Mode
 * @param [in] 		- 	duty_cycle : Value of PWM duty cycle (from 0 to 255)
 * @retval 			-	none
 * Note 			-	Supported for Fast PWM Mode only & count value must not exceed 255
 *
 */
void MCAL_PWM_DutyCycle(uint8_t duty_cycle)
{
	if(Global_Timer_Config.Timer_Mode == TIMER_MODE_FAST_PWM_NONINVERTING)
		OCR0 = duty_cycle;
	else if(Global_Timer_Config.Timer_Mode == TIMER_MODE_FAST_PWM_INVERTING)
		OCR0 = (uint8_t)(255 - duty_cycle);
}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

//OVERFLOW ISR
ISR(TIMER0_OVF_vect)
{
	GP_CallBack();
}

//COMPARE MATCH ISR
ISR(TIMER0_COMP_vect)
{
	GP_CallBack();
}