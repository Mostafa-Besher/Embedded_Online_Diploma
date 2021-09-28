/*
 * stm32_f103c6_RCC_driver.h
 *
 *  Created on: Aug 26, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"


//-----------------------------
//MACROS
//-----------------------------
#define HSI_RC_CLOCK		((uint32_t)8000000)
#define HSE_CLOCK			((uint32_t)16000000)


/*
* ===================================================================================
* 						APIs Supported by "MCAL RCC DRIVER"
* ===================================================================================
*/
uint32_t MCAL_RCC_getPCLK1Freq(void);
uint32_t MCAL_RCC_getPCLK2Freq(void);
uint32_t MCAL_RCC_getHCLKFreq(void);
uint32_t MCAL_RCC_getSysCLKFreq(void);


#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
