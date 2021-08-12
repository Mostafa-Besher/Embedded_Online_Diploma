/*
 * stm32_f103c6_gpio_drivers.c
 *
 *  Created on: Jul 18, 2021
 *      Author: MostafaBesher
 */

#include "stm32_f103c6_gpio_drivers.h"


uint8_t get_position(uint16_t pin_number)
{
	switch(pin_number)
	{
	case  GPIO_PIN_0 :
		return 0;
		break;
	case  GPIO_PIN_1 :
		return 4;
		break;
	case  GPIO_PIN_2 :
		return 8;
		break;
	case  GPIO_PIN_3 :
		return 12;
		break;
	case  GPIO_PIN_4 :
		return 16;
		break;
	case  GPIO_PIN_5 :
		return 20;
		break;
	case  GPIO_PIN_6 :
		return 24;
		break;
	case  GPIO_PIN_7 :
		return 28;
		break;
	case  GPIO_PIN_8 :
		return 0;
		break;
	case  GPIO_PIN_9 :
		return 4;
		break;
	case  GPIO_PIN_10 :
		return 8;
		break;
	case  GPIO_PIN_11 :
		return 12;
		break;
	case  GPIO_PIN_12 :
		return 16;
		break;
	case  GPIO_PIN_13 :
		return 20;
		break;
	case  GPIO_PIN_14 :
		return 24;
		break;
	case  GPIO_PIN_15 :
		return 28;
		break;
	}
	return 0;
}


/**================================================================
 * @Fn 				-	MCAL_GPIO_Init
 * @brief 			-	Initializes GPIOx PINy according to the specified parameters in pinConfig
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	pinconfig : a pointer to GPIO_Pinconfig_t structure that contains
 * 									the configuration information for the specified GPIO pin
 * @retval 			-	none
 * Note 			-	STM32f103c6 MCU has GPIO A,B,B,D,E modules
 *                      but LQFP48 Package has only A,B, Part of C,D
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_Pinconfig_t * pinconfig)
{
	//Port configuration register low (GPIOx_CRL) pins 0 >>> 7
	//Port configuration register high (GPIOx_CRH) pins 8 >>> 15
	volatile uint32_t * configreg = NULL;
	uint8_t PIN_Config = 0;
	configreg = (pinconfig->PinNumber < GPIO_PIN_8)? &GPIOx->CRL: &GPIOx->CRH;
	//clear CNFy[1:0] , MODEy[1:0]
	*(configreg) &= ~(0xf << get_position(pinconfig->PinNumber));
	//if pin is output
	if ( (pinconfig ->Mode == GPIO_MODE_Output_PP || pinconfig ->Mode == GPIO_MODE_Output_OD || pinconfig ->Mode == GPIO_MODE_Output_AF_PP || pinconfig ->Mode == GPIO_MODE_Output_AF_OD) )
	{
		PIN_Config = ( ((pinconfig ->Mode - 4) << 2) | (pinconfig ->Output_speed  & 0x0f) );
	}
	//if pin is input
	else	//MODEy[1:0] = 00: Input mode (reset state)
	{
		//Input with pull-up / pull-down mode
		if( pinconfig ->Mode == GPIO_MODE_Input_PD || pinconfig ->Mode == GPIO_MODE_Input_PU )
		{
			PIN_Config = ( ((GPIO_MODE_Input_PU << 2) | 0x0) & 0x0f );
			//check if mode is pull-down
			if( pinconfig ->Mode == GPIO_MODE_Input_PD )
			{
				//According to Table 20. Port bit configuration table : PxODR = 0
				GPIOx ->ODR  &= ~(pinconfig ->PinNumber);
			}
			//check if mode is pull-up
			else if( pinconfig ->Mode == GPIO_MODE_Input_PU )
			{
				//According to Table 20. Port bit configuration table : PxODR = 1
				GPIOx ->ODR  |= (pinconfig ->PinNumber);
			}
		}
		else if ( pinconfig ->Mode == GPIO_MODE_AF_Input)	//consider it  as input floating
		{
			PIN_Config = ( ((GPIO_MODE_Input_FLU << 2) | 0x0) & 0x0f );
		}
		else	//Analog mode , input floating
		{
			PIN_Config = ( ((pinconfig ->Mode << 2) | 0x0) & 0x0f );
		}
	}
	//Write on CRL or CRH
	*(configreg) |= ( (PIN_Config) << get_position(pinconfig ->PinNumber) );
}


/**================================================================
 * @Fn 				-	MCAL_GPIO_DeInit
 * @brief 			-	Reset all the GPIO registers
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @retval 			-	none
 * Note 			-	none
 */

void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx)
{
	if(GPIOx == GPIOA)
	{
		//Reset GPIOA Registers
		RCC ->APB2RSTR |= 1 << 2;
		RCC ->APB2RSTR &= ~(1 << 2);
	}
	else if(GPIOx == GPIOB)
	{
		//Reset GPIOB Registers
		RCC ->APB2RSTR |= 1 << 3;
		RCC ->APB2RSTR &= ~(1 << 3);
	}
	else if(GPIOx == GPIOC)
	{
		//Reset GPIOC Registers
		RCC ->APB2RSTR |= 1 << 4;
		RCC ->APB2RSTR &= ~(1 << 4);
	}
	else if(GPIOx == GPIOD)
	{
		//Reset GPIOD Registers
		RCC ->APB2RSTR |= 1 << 5;
		RCC ->APB2RSTR &= ~(1 << 5);
	}
	else if(GPIOx == GPIOE)
	{
		//Reset GPIOE Registers
		RCC ->APB2RSTR |= 1 << 6;
		RCC ->APB2RSTR &= ~(1 << 6);
	}
}

/**================================================================
 * @Fn 				-	MCAL_GPIO_ReadPin
 * @brief 			-	Read specific GPIOx Pin value
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	PinNumber : set pin number to read according to @ref GPIO_PIN_DEFINE
 * @retval 			-	The Reading value of the input pin according to @ref READ_PIN_RETURN
 * Note 			-	none
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
	uint8_t Read_val = 0;
	if( (GPIOx ->IDR & PinNumber) != (uint32_t)READ_PIN_LOW )
	{
		Read_val = READ_PIN_HIGH;
	}
	else
	{
		Read_val = READ_PIN_LOW;
	}
	return Read_val;
}


/**================================================================
 * @Fn 				-	MCAL_GPIO_ReadPort
 * @brief 			-	Read the input GPIOx port value
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @retval 			-	The input port value
 * Note 			-	none
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx)
{
	return ((uint16_t)GPIOx ->IDR);
}


/**================================================================
 * @Fn 				-	MCAL_GPIO_WritePin
 * @brief 			-	Write a value on specific GPIOx Pin
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	PinNumber : specifies pin number according to @ref GPIO_PIN_DEFINE
 * @param [in] 		- 	value : Set the write value according to @ref WRITE_PIN_DEFINE
 * @retval 			-	none
 * Note 			-	none
 */

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value == READ_PIN_HIGH)
		GPIOx ->ODR |= PinNumber;
	else
		GPIOx ->ODR &= ~(PinNumber);
	// or
//	if(Value == READ_PIN_HIGH)
//		GPIOx ->BSRR = (uint32_t)PinNumber;
//	else
//		GPIOx ->BRR = (uint32_t)PinNumber;

}


/**================================================================
 * @Fn 				-	MCAL_GPIO_WritePort
 * @brief 			-	Write a value for GPIOx Port
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	value : Set the write value for GPIO port
 * @retval 			-	none
 * Note 			-	none
 */

void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx, uint16_t Value)
{
	GPIOx ->ODR = (uint32_t)Value ;
}


/**================================================================
 * @Fn 				-	MCAL_GPIO_TogglePin
 * @brief 			-	Toggle GPIOx specific Pin
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	PinNumber : specifies pin number according to @ref GPIO_PIN_DEFINE
 * @retval 			-	none
 * Note 			-	none
 */

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
	GPIOx ->ODR ^= (uint32_t)PinNumber ;
}


/**================================================================
 * @Fn 				-	MCAL_Lock_Pin
 * @brief 			-	Locking specific pin make pin to be frozen
 * @param [in] 		- 	GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- 	PinNumber : specifies pin number according to @ref GPIO_PIN_DEFINE
 * @retval 			-	Return (OK) if pin config is locked (ERROR) if not locked @ref GPIO_LOCK_PIN_DEFINE
 * Note 			-	When the LOCK sequence has been applied on a port bit it is no longer possible to modify
 * 						the value of the port bit until the next reset.
 */

uint16_t MCAL_LockPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber)
{
//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked.

	volatile uint32_t tmp = 1 << 16;
	//set LCKy
	tmp |= PinNumber ;
	//	LOCK key writing sequence:
	//	Write 1
	GPIOx ->LCKR = tmp;
	//	Write 0
	GPIOx ->LCKR = PinNumber;
	//	Write 1
	GPIOx ->LCKR = tmp;
	//	Read 0
	tmp = GPIOx ->LCKR;
	if((GPIOx ->LCKR) & (1 << 16))
		return GPIO_LOCK_PIN_ENABLE;
	else
		return GPIO_LOCK_PIN_ERROR;
}
