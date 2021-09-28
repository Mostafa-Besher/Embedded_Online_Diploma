/*
 * stm32_f103c6_SPI_drivers.h
 *
 *  Created on: Sep 6, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32_F103C6_SPI_DRIVERS_H_
#define INC_STM32_F103C6_SPI_DRIVERS_H_


//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"



//--------------------------------------
//User type definitions (structures)
//--------------------------------------

struct S_IRQ_Src
{
	uint8_t		TXE:1;						//TX Buffer Empty Interrupt
	uint8_t		RXNE:1;						//RX Buffer Not Empty Interrupt
	uint8_t		ERRI:1;						//Error Interrupt
	uint8_t		Reserved:5;
};



typedef struct
{
	uint16_t 	SPI_MODE;					// specifies SPI MODE Master/Slave
											// This parameter must be set based on @ref SPI_MODE_DEFINE

	uint16_t	FRAME_FORMAT;				// specifies Data MSB transmit first or LSB transmit first
											// This parameter must be set based on @ref FRAME_FORMAT_DEFINE

	uint16_t	FRAME_SIZE;					// specifies Data frame size 8-bit or 16_bit
											// This parameter must be set based on @ref FRAME_SIZE_DEFINE

	uint16_t	COMMUNICATION_MODE;			// specifies SPI Communication mode
											// This parameter must be set based on @ref COMMUNICATION_MODE_DEFINE

	uint16_t	CLK_POLARITY;				// specifies SPI clock Polarity idle on low or idle on high
											// This parameter must be set based on @ref CLK_POLARITY_DEFINE

	uint16_t	CLK_PHASE;					// specifies SPI clock Phase,first clock capture or second clock capture
											// This parameter must be set based on @ref @ref CLK_PHASE_DEFINE

	uint16_t	NSS_MANGEMENT;				// specifies slave select mangement by hardware or by software
											// This parameter must be set based on @ref NSS_MANGEMENT_DEFINE

	uint16_t	BAUDERATE_PRESCALER;		// specifies SPI clock Phase,first clock capture or second clock capture
											// This parameter must be set based on @ref BAUDERATE_PRESCALER_DEFINE

	uint16_t	IRQ_ENABLE;					// specifies SPI clock Phase,first clock capture or second clock capture
											// This parameter must be set based on @ref IRQ_ENABLE_DEFINE

	void (* P_IRQ_CallBack)(struct S_IRQ_Src IRQ_src);			//set the C Function which will be called once IRQ Happens


}SPI_Pinconfig_t;






//-----------------------------------
//Macros Configuration References
//-----------------------------------


//@ref SPI_MODE_DEFINE
#define SPI_MODE_MASTER											(uint32_t) (1<<2)
#define SPI_MODE_SLAVE											(uint32_t) (0)


//@ref FRAME_FORMAT_DEFINE
#define FRAME_FORMAT_MSB_FIRST									(uint32_t) (0)
#define FRAME_FORMAT_LSB_FIRST									(uint32_t) (1<<7)


//@ref FRAME_SIZE_DEFINE
#define FRAME_SIZE_8BIT											(uint32_t) (0)
#define FRAME_SIZE_16BIT										(uint32_t) (1<<11)

//@ref COMMUNICATION_MODE_DEFINE
#define COMMUNICATION_MODE_1LINE_RECIEVE_ONLY					(uint32_t) (1<<15)
#define COMMUNICATION_MODE_1LINE_TRANSMIT_ONLY					(uint32_t) ((1<<15) | (1<<14))
#define COMMUNICATION_MODE_2LINE_FULL_DUPLEX					(uint32_t) (0)
#define COMMUNICATION_MODE_2LINE_RECIEVE_ONLY					(uint32_t) (1<<10)

//@ref CLK_POLARITY_DEFINE
#define CLK_POLARITY_IDLE_LOW									(uint32_t) (0)
#define CLK_POLARITY_IDLE_HIGH									(uint32_t) (1<<1)

//@ref CLK_PHASE_DEFINE
#define CLK_POLARITY_FIRST_CLK_CAPTURE							(uint32_t) (0)
#define CLK_POLARITY_SECOND_CLK_CAPTURE							(uint32_t) (1<<0)

//@ref NSS_MANGEMENT_DEFINE
//HARDWARE(SPI_CR2 Register)
#define NSS_MANGEMENT_SLAVE_HARDWARE							(uint32_t) (0)
#define NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_ENABLED			(uint32_t) (1<<2)		//cannot work in a MultiMaster environment
#define NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_DISABLED		(uint32_t) (0)			//can work in MultiMaster configuration

//SOFTWARE(NSS is driven by software for master or slave)
#define NSS_MANGEMENT_SOFTWARE_SSI_SET							(uint32_t) ((1<<9) | (1<<8))
#define NSS_MANGEMENT_SOFTWARE_SSI_RESET						(uint32_t) (1<<9)

//@ref BAUDERATE_PRESCALER_DEFINE
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_2					(uint32_t) (0)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_4					(uint32_t) (1<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_8					(uint32_t) (2<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_16					(uint32_t) (3<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_32					(uint32_t) (4<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_64					(uint32_t) (5<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_128					(uint32_t) (6<<3)
#define BAUDERATE_PRESCALER_FCLK_DIVIDE_BY_256					(uint32_t) (7<<3)

//@ref IRQ_ENABLE_DEFINE
#define IRQ_ENABLE_NONE											(uint32_t) (0)			// IRQ Disable
#define IRQ_ENABLE_TXEIE										(uint32_t) (1<<7)		// TX buffer empty interrupt enable
#define IRQ_ENABLE_RXNEIE										(uint32_t) (1<<6)		// RX buffer not empty interrupt enable
#define IRQ_ENABLE_ERRIE										(uint32_t) (1<<5)		// Error interrupt enable


enum Polling_Mechanism
{
	Polling_disable,
	Polling_enable
};




/*
* ==============================================================================
* 				  APIs Supported by "MCAL SPI DRIVER"
* ==============================================================================
*/

void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Pinconfig_t * SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef * SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_Send_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);
void MCAL_SPI_Recieve_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);








#endif /* INC_STM32_F103C6_SPI_DRIVERS_H_ */
