/*
 * stm32_f103c6_gpio_drivers.h
 *
 *  Created on: Jul 18, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVERS_H_
#define INC_STM32_F103C6_GPIO_DRIVERS_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"

//----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct{
	uint16_t PinNumber ;			// specifies GPIO pins to be configured
									// This parameter must be set based on @ref GPIO_PIN_DEFINE

	uint8_t Mode ;					// specifies the operating mode of a selected pin
									// This parameter must be set based on @ref GPIO_MODE_DEFINE

	uint8_t Output_speed ;			//specifies speed when selected output mode
									// This parameter must be set based on @ref GPIO_SPEED_DEFINE
}GPIO_Pinconfig_t;




//----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PIN_DEFINE

#define GPIO_PIN_0					((uint16_t)0x0001)			/*  Pin 0 selected  */
#define GPIO_PIN_1					((uint16_t)0x0002)			/*  Pin 1 selected  */
#define GPIO_PIN_2					((uint16_t)0x0004)			/*  Pin 1 selected  */
#define GPIO_PIN_3					((uint16_t)0x0008)			/*  Pin 1 selected  */
#define GPIO_PIN_4					((uint16_t)0x0010)			/*  Pin 1 selected  */
#define GPIO_PIN_5					((uint16_t)0x0020)			/*  Pin 1 selected  */
#define GPIO_PIN_6					((uint16_t)0x0040)			/*  Pin 1 selected  */
#define GPIO_PIN_7					((uint16_t)0x0080)			/*  Pin 1 selected  */
#define GPIO_PIN_8					((uint16_t)0x0100)			/*  Pin 1 selected  */
#define GPIO_PIN_9					((uint16_t)0x0200)			/*  Pin 1 selected  */
#define GPIO_PIN_10					((uint16_t)0x0400)			/*  Pin 1 selected  */
#define GPIO_PIN_11					((uint16_t)0x0800)			/*  Pin 1 selected  */
#define GPIO_PIN_12					((uint16_t)0x1000)			/*  Pin 1 selected  */
#define GPIO_PIN_13					((uint16_t)0x2000)			/*  Pin 1 selected  */
#define GPIO_PIN_14					((uint16_t)0x4000)			/*  Pin 1 selected  */
#define GPIO_PIN_15					((uint16_t)0x8000)			/*  Pin 1 selected  */

#define GPIO_PIN_ALL				((uint16_t)0xFFFF)			/*  All pins selected  */


//@ref GPIO_MODE_DEFINE

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8 : Input mode (Floating input)

#define GPIO_MODE_Analog			0x00000000u				//input Analog mode
#define GPIO_MODE_Input_FLU			0x00000001u				//Floating input
#define GPIO_MODE_Input_PU			0x00000002u				//Input with pull-up
#define GPIO_MODE_Input_PD			0x00000003u				//Input with pull-down
#define GPIO_MODE_Output_PP			0x00000004u				//General purpose output push-pull
#define GPIO_MODE_Output_OD			0x00000005u				//General purpose output Open-drain
#define GPIO_MODE_Output_AF_PP		0x00000006u				//Alternate function output Push-pull
#define GPIO_MODE_Output_AF_OD		0x00000007u				//Alternate function output Open-drain
#define GPIO_MODE_AF_Input			0x00000008u				//alternate function input


//@ref GPIO_SPEED_DEFINE

//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define	GPIO_SPEED_10M				0x00000001u				//Output mode, max speed 10 MHz
#define	GPIO_SPEED_2M			    0x00000002u				//Output mode, max speed 2 MHz
#define	GPIO_SPEED_50M				0x00000003u				//Output mode, max speed 50 MHz


//@ref READ_PIN_RETURN

#define READ_PIN_HIGH				1
#define READ_PIN_LOW				0


//@ref WRITE_PIN_DEFINE

#define WRITE_PIN_HIGH				1
#define WRITE_PIN_LOW				0


//@ref GPIO_LOCK_PIN_DEFINE

#define	GPIO_LOCK_PIN_ENABLE		1
#define	GPIO_LOCK_PIN_ERROR			0


/*
* ====================================================================
* 				APIs Supported by "MCAL GPIO DRIVER"
* ====================================================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_Pinconfig_t * pinconfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);

uint16_t MCAL_LockPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);







#endif /* INC_STM32_F103C6_GPIO_DRIVERS_H_ */
