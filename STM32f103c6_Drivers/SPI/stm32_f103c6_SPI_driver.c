/*
 * stm32_f103c6_SPI_driver.c
 *
 *  Created on: Sep 6, 2021
 *      Author: MostafaBesher
 */

#include "stm32_f103c6_SPI_drivers.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

SPI_Pinconfig_t * Global_SPI_Config[2] = {NULL,NULL};



/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/

#define SPI1_INDEX				0
#define SPI2_INDEX				1


#define SPI_SR_TXE				((uint32_t)(1<<1))
#define SPI_SR_RXNE				((uint32_t)(1<<0))


/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/


/**================================================================
 * @Fn 				-	MCAL_SPI_Init
 * @brief 			-	Initializes SPIx according to the specified parameters in SPI_config
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- 	SPI_Config : a pointer to SPI_Pinconfig_t structure that contains
 * 									the configuration information for the specified SPI Module
 * @retval 			-	none
 * Note 			-	Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 * 					-	You have to configure RCC to select clock for the selected SPI Module
 *
 */
void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Pinconfig_t * SPI_Config)
{
	//Enable Clock for the selected SPI Module
	if(SPIx == SPI1)
	{
		RCC_SPI1_CLK_EN();
		//store BackUpdata of each SPI module in Global Variable
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
	}
	else if (SPIx == SPI2)
	{
		RCC_SPI2_CLK_EN();
		//store BackUpdata of each SPI module in Global Variable
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
	}

	//Select SPI Mode
	SPIx->SPI_CR1 |= SPI_Config->SPI_MODE;

	//select SPI Frame Format(LSB First/MSB First)
	SPIx->SPI_CR1 |= SPI_Config->FRAME_FORMAT;

	//Select Data Frame Size(8bit/16bit)
	SPIx->SPI_CR1 |= SPI_Config->FRAME_SIZE;

	//Select SPI Communication Mode
	SPIx->SPI_CR1 |= SPI_Config->COMMUNICATION_MODE;

	//Select Clock Polarity
	SPIx->SPI_CR1 |= SPI_Config->CLK_POLARITY;

	//Select Clock Phase
	SPIx->SPI_CR1 |= SPI_Config->CLK_PHASE;

	//Select NSS
	if(SPI_Config->NSS_MANGEMENT == NSS_MANGEMENT_SOFTWARE_SSI_SET || SPI_Config->NSS_MANGEMENT == NSS_MANGEMENT_SOFTWARE_SSI_RESET)
		SPIx->SPI_CR1 |= SPI_Config->NSS_MANGEMENT;
	else
		SPIx->SPI_CR2 |= SPI_Config->NSS_MANGEMENT;

	//Select Clock BAUDRATE for Master only
	if(SPI_Config->SPI_MODE == SPI_MODE_MASTER)
		SPIx->SPI_CR1 |= SPI_Config->BAUDERATE_PRESCALER;

	//Enable or Disable IRQ
	if(SPI_Config->IRQ_ENABLE != IRQ_ENABLE_NONE)
	{
		SPIx->SPI_CR2 |= SPI_Config->IRQ_ENABLE;
		//Enable NVIC IRQ
		if(SPIx == SPI1)
			NVIC_IRQ35_SPI1_ENABLE;
		else if(SPIx == SPI2)
			NVIC_IRQ36_SPI2_ENABLE;
	}

	//Enable the selected SPI Module
	SPIx->SPI_CR1 |= 1<<6;
}

/**================================================================
 * @Fn 				-	MCAL_SPI_DeInit
 * @brief 			-	Resets Selected SPI Module
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			-	none
 * Note 			-	Reset The Module By RCC & Disable NVIC
 *
 */
void MCAL_SPI_DeInit(SPI_TypeDef * SPIx)
{
	if(SPIx == SPI1)
	{
		RCC_SPI1_RESET();
		NVIC_IRQ35_SPI1_DISABLE;
	}

	else if(SPIx == SPI2)
	{
		RCC_SPI2_RESET();
		NVIC_IRQ36_SPI2_DISABLE;
	}
}

/**================================================================
 * @Fn 				-	MCAL_SPI_GPIO_Set_Pins
 * @brief 			-	Initializes GPIO Pins to be connected with the selected SPI
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @retval 			-	none
 * Note 			-	Must open clock for AFIO & GPIO After GPIO Initialization
 * 					-	Supported for SPI FULL DUPLEX Master/Slave only & NSS Hardware/Software
 *
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	GPIO_Pinconfig_t SPI_GPIO_Config;
	//*************************************SPI1***************************************
	if(SPIx == SPI1)
	{
		//===========================MASTER=========================================
		if(Global_SPI_Config[SPI1_INDEX]->SPI_MODE == SPI_MODE_MASTER)
		{
			//================Configure SCK pin====================
			//for Master -->Alternate function push-pull
			SPI_GPIO_Config.PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure MOSI pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure MISO pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure NSS pin====================
			if(Global_SPI_Config[SPI1_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_ENABLED)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;		//Alternate function push-pull
				SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
			}
			else if(Global_SPI_Config[SPI1_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_DISABLED)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;		//Input Floating
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
			}
		}

		//===========================SLAVE=========================================
		else if (Global_SPI_Config[SPI1_INDEX]->SPI_MODE == SPI_MODE_SLAVE)
		{
			//================Configure SCK pin====================
			//for Slave -->Input Floating
			SPI_GPIO_Config.PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure MOSI pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure MISO pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			//================Configure NSS pin====================
			if (Global_SPI_Config[SPI1_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_SLAVE_HARDWARE)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;		//Input Floating
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
			}
		}
	}

	//*************************************SPI2***************************************
	else if(SPIx == SPI2)
	{
		//===========================MASTER=========================================
		if(Global_SPI_Config[SPI2_INDEX]->SPI_MODE == SPI_MODE_MASTER)
		{
			//================Configure SCK pin====================
			//for Master -->Alternate function push-pull
			SPI_GPIO_Config.PinNumber = GPIO_PIN_13;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure MOSI pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_15;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure MISO pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_14;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure NSS pin====================
			if(Global_SPI_Config[SPI2_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_ENABLED)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_12;
				SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;		//Alternate function push-pull
				SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
			}
			else if(Global_SPI_Config[SPI2_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_MASTER_HARDWARE_SS_OUTPUT_DISABLED)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_12;
				SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;		//Input Floating
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
			}
		}

		//===========================SLAVE=========================================
		else if (Global_SPI_Config[SPI2_INDEX]->SPI_MODE == SPI_MODE_SLAVE)
		{
			//================Configure SCK pin====================
			//for Slave -->Input Floating
			SPI_GPIO_Config.PinNumber = GPIO_PIN_13;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure MOSI pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_15;
			SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure MISO pin====================
			SPI_GPIO_Config.PinNumber = GPIO_PIN_14;
			SPI_GPIO_Config.Mode = GPIO_MODE_Output_AF_PP;
			SPI_GPIO_Config.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			//================Configure NSS pin====================
			if (Global_SPI_Config[SPI2_INDEX]->NSS_MANGEMENT == NSS_MANGEMENT_SLAVE_HARDWARE)
			{
				SPI_GPIO_Config.PinNumber = GPIO_PIN_12;
				SPI_GPIO_Config.Mode = GPIO_MODE_Input_FLU;		//Input Floating
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
			}
		}
	}
}

/**================================================================
 * @Fn 				-	MCAL_SPI_Send_Data
 * @brief 			-	Send Buffer With SPI
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- 	TxBuffer : Buffer Which holds the TX data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_SPI_Send_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_enable)
	{
		//Wait for Transmit Buffer to be Empty
		while(! (SPIx->SPI_SR & SPI_SR_TXE));
	}
	//send data
	SPIx->SPI_DR = *(pTxBuffer);
}

/**================================================================
 * @Fn 				-	MCAL_SPI_Recieve_Data
 * @brief 			-	Receive Buffer With SPI
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- 	pTxBuffer : Buffer which holds Received data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_SPI_Recieve_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_enable)
	{
		//Wait for Transmit Buffer to be Empty
		while(! (SPIx->SPI_SR & SPI_SR_RXNE));
	}
	*(pTxBuffer) = SPIx->SPI_DR;
}

/**================================================================
 * @Fn 				-	MCAL_SPI_TX_RX
 * @brief 			-	Transmit and Receive Data
 * @param [in] 		- 	SPIx : where x can be (1..2 depending on device used) to select SPI peripheral
 * @param [in] 		- 	pTxBuffer : Buffer which holds Transmit and Received data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_enable)
	{
		//Wait for Transmit Buffer to be Empty
		while(! (SPIx->SPI_SR & SPI_SR_TXE));
	}
	//send data
	SPIx->SPI_DR = *(pTxBuffer);

	if(Polling_En == Polling_enable)
	{
		//Wait for Receive buffer not empty flag
		while(! (SPIx->SPI_SR & SPI_SR_RXNE));
	}
	//Receive Data
	*(pTxBuffer) = SPIx->SPI_DR;
}





/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

void SPI1_IRQHandler(void)
{
	struct S_IRQ_Src irq;
	irq.TXE = ((SPI1->SPI_SR & (1<<1)) >> 1);
	irq.RXNE = ((SPI1->SPI_SR & (1<<0)) >> 0);
	irq.ERRI = ((SPI1->SPI_SR & (1<<4)) >> 4);
	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq);
}


void SPI2_IRQHandler(void)
{
	struct S_IRQ_Src irq;
	irq.TXE = ((SPI2->SPI_SR & (1<<1)) >> 1);
	irq.RXNE = ((SPI2->SPI_SR & (1<<0)) >> 0);
	irq.ERRI = ((SPI2->SPI_SR & (1<<4)) >> 4);
	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq);
}
