/*
 * stm32_f103c6_EXTI_drivers.c
 *
 *  Created on: Aug 9, 2021
 *      Author: MostafaBesher
 */

#include "stm32_f103c6_EXTI_drivers.h"

/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

void(* GP_IRQ_callback[16])(void) ;



/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/


#define AFIO_EXTI_MAPPING(x)		(	(x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:0	  )


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/

void Enable_NVIC(uint8_t LINE_NO)
{
	switch(LINE_NO)
	{
	case EXTI0  :
	{
		NVIC_IRQ6_EXTI0_ENABLE;
		break;
	}
	case EXTI1  :
	{
		NVIC_IRQ7_EXTI1_ENABLE;
		break;
	}
	case EXTI2  :
	{
		NVIC_IRQ8_EXTI2_ENABLE;
		break;
	}
	case EXTI3  :
	{
		NVIC_IRQ9_EXTI3_ENABLE;
		break;
	}
	case EXTI4  :
	{
		NVIC_IRQ10_EXTI4_ENABLE;
		break;
	}
	case EXTI5  :
	case EXTI6  :
	case EXTI7  :
	case EXTI8  :
	case EXTI9  :
	{
		NVIC_IRQ23_EXTI5_9_ENABLE;
		break;
	}
	case EXTI10  :
	case EXTI11  :
	case EXTI12  :
	case EXTI13  :
	case EXTI14  :
	case EXTI15  :
	{
		NVIC_IRQ40_EXTI10_15_ENABLE;
		break;
	}
	}
}


//=======================================================================

void Disable_NVIC(uint8_t LINE_NO)
{
	switch(LINE_NO)
	{
	case EXTI0  :
	{
		NVIC_IRQ6_EXTI0_DISABLE;
		break;
	}
	case EXTI1  :
	{
		NVIC_IRQ7_EXTI1_DISABLE;
		break;
	}
	case EXTI2  :
	{
		NVIC_IRQ8_EXTI2_DISABLE;
		break;
	}
	case EXTI3  :
	{
		NVIC_IRQ9_EXTI3_DISABLE;
		break;
	}
	case EXTI4  :
	{
		NVIC_IRQ10_EXTI4_DISABLE;
		break;
	}
	case EXTI5  :
	case EXTI6  :
	case EXTI7  :
	case EXTI8  :
	case EXTI9  :
	{
		NVIC_IRQ23_EXTI5_9_DISABLE;
		break;
	}
	case EXTI10  :
	case EXTI11  :
	case EXTI12  :
	case EXTI13  :
	case EXTI14  :
	case EXTI15  :
	{
		NVIC_IRQ40_EXTI10_15_DISABLE;
		break;
	}
	}
}

//=======================================================================

void EXTI_Update(EXTI_PINCONFIG_t * EXTI_Config)
{
	//1- select GPIO pin as AF INPUT --> input floating
	GPIO_Pinconfig_t PIN_cfg;
	PIN_cfg.PinNumber = EXTI_Config->EXTI_PIN.GPIO_Pin;
	PIN_cfg.Mode = GPIO_MODE_Input_FLU;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &PIN_cfg);
	//===============================================================

	//2- Configure AFIO to route the selected pin to EXTI specified line

	uint8_t EXTICR_index = EXTI_Config->EXTI_PIN.EXTI_Line_No / 4 ;
	uint8_t position = (EXTI_Config->EXTI_PIN.EXTI_Line_No % 4) * 4 ;

	//clear four bits for selected EXTI line
	AFIO->EXTICR[EXTICR_index] &= ~(0xf << position);
	//set EXTICR(0,1,2,3) registers value
	AFIO->EXTICR[EXTICR_index] |= ((AFIO_EXTI_MAPPING(EXTI_Config ->EXTI_PIN.GPIO_Port) & 0xF) << position);
	//===============================================================

	//3- select trigger case(RISING, FALLING OR BOTH)
	//reset registers for specified EXTI line
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_Line_No) ;
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_Line_No) ;

	//select trigger case
	if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_RISING)
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
	else if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_FALLING)
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
	else if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_FALLINGAndRISING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
	}
	//===============================================================

	//4- call call_back function in ISR
	GP_IRQ_callback[EXTI_Config->EXTI_PIN.EXTI_Line_No] = EXTI_Config->P_IRQ_callback;
	//===============================================================

	//5- Enable or Disable EXTI IRQ and NVIC
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI ->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Line_No) ;
	}

	else if (EXTI_Config->IRQ_EN == EXTI_IRQ_DISABLE)
	{
		EXTI ->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_Line_No);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Line_No) ;
	}

}


/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/


/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_DeInit
 * @brief 			-	Reset EXTI registers to their initial values and NVIC corresponding IRQ mask
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	//Reset EXTI registers
	EXTI ->IMR = 0x00000000 ;
	EXTI ->EMR = 0x00000000 ;
	EXTI ->RTSR = 0x00000000 ;
	EXTI ->FTSR = 0x00000000;
	EXTI ->SWIER = 0x00000000;
//	Bits 19:0 PRx: Pending bit
//	0: No trigger request occurred
//	1: selected trigger request occurred
//	This bit is set when the selected edge event arrives on the external interrupt line. This bit is
//	cleared by writing a ‘1’ into the bit.
	EXTI ->PR = 0xFFFFFFFF;
	//Disable the EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_DISABLE;
	NVIC_IRQ7_EXTI1_DISABLE;
	NVIC_IRQ8_EXTI2_DISABLE;
	NVIC_IRQ9_EXTI3_DISABLE;
	NVIC_IRQ10_EXTI4_DISABLE;
	NVIC_IRQ23_EXTI5_9_DISABLE;
	NVIC_IRQ40_EXTI10_15_DISABLE;
}



/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_Init
 * @brief 			-	Initializes GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config : includes pin configuration for EXTI
 * 									  set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	STM32f103c6 MCU has GPIO A,B,B,D,E modules
 *                      but LQFP48 Package has only A,B, Part of C,D
 *                      Also mandatory to enable RCC clock for AFIO and the corresponding GPIO
 */
void MCAL_EXTI_GPIO_Init(EXTI_PINCONFIG_t * EXTI_Config)
{
	EXTI_Update(EXTI_Config);
}


/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_Update
 * @brief 			-	Update GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config :includes pin configuration for EXTI
 * 									 set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_GPIO_Update(EXTI_PINCONFIG_t * EXTI_Config)
{
	EXTI_Update(EXTI_Config);
}





/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

void EXTI0_IRQHandler(void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1 << 0 ;
	//call IRQ call_back
	GP_IRQ_callback[0]();
}

void EXTI1_IRQHandler(void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1 << 1 ;
	//call IRQ call_back
	GP_IRQ_callback[1]();
}

void EXTI2_IRQHandler(void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1 << 2 ;
	//call IRQ call_back
	GP_IRQ_callback[2]();
}

void EXTI3_IRQHandler(void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1 << 3 ;
	//call IRQ call_back
	GP_IRQ_callback[3]();
}

void EXTI4_IRQHandler(void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1 << 4 ;
	//call IRQ call_back
	GP_IRQ_callback[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1 << 5)	{EXTI->PR |= (1 << 5) 	;GP_IRQ_callback[5]()	;	}
	if(EXTI->PR & 1 << 6)	{EXTI->PR |= (1 << 6) 	;GP_IRQ_callback[6]()	;	}
	if(EXTI->PR & 1 << 7)	{EXTI->PR |= (1 << 7) 	;GP_IRQ_callback[7]()	;	}
	if(EXTI->PR & 1 << 8)	{EXTI->PR |= (1 << 8) 	;GP_IRQ_callback[8]()	;	}
	if(EXTI->PR & 1 << 9)	{EXTI->PR |= (1 << 9) 	;GP_IRQ_callback[9]()	;	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1 << 10)	{EXTI->PR |= (1 << 10) 	;GP_IRQ_callback[10]()	;	}
	if(EXTI->PR & 1 << 11)	{EXTI->PR |= (1 << 11) 	;GP_IRQ_callback[11]()	;	}
	if(EXTI->PR & 1 << 12)	{EXTI->PR |= (1 << 12) 	;GP_IRQ_callback[12]()	;	}
	if(EXTI->PR & 1 << 13)	{EXTI->PR |= (1 << 13) 	;GP_IRQ_callback[13]()	;	}
	if(EXTI->PR & 1 << 14)	{EXTI->PR |= (1 << 14) 	;GP_IRQ_callback[14]()	;	}
	if(EXTI->PR & 1 << 15)	{EXTI->PR |= (1 << 15) 	;GP_IRQ_callback[15]()	;	}

}



