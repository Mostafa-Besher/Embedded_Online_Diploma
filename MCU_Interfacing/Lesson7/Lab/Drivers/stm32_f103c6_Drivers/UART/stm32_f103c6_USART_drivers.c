/*
 * stm32_f103c6_USART_drivers.c
 *
 *  Created on: Aug 26, 2021
 *      Author: MostafaBesher
 */


#include  "stm32_f103c6_USART_drivers.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/


USART_CONFIG_t * Global_UART_config = NULL;
void (* GP_IRQ_CallBack)(void);



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/



/**================================================================
 * @Fn 				-	MCAL_UART_Init
 * @brief 			-	Initializes USARTx according to the specified parameters in UART_config
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	UART_config : a pointer to USART_CONFIG_t structure that contains
 * 									the configuration information for the specified USART Module
 * @retval 			-	none
 * Note 			-	Supported for Asynchronous Mode & Clock = 8 MHz
 *
 */
void MCAL_UART_Init(USART_TypeDef *USARTx, USART_CONFIG_t * UART_config)
{
	Global_UART_config = UART_config;
	//Enable clock for given USART peripheral
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if(USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if(USARTx == USART3)
		RCC_USART3_CLK_EN();

	//1-Enable USART MODULE
	//Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//2-select UART MODE
	//Bit 3 TE: Transmitter enable, Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_config->USART_Mode;

	//3-set baud rate value
	uint32_t Pclk, BRR;
	if(USARTx == USART1)
		Pclk = MCAL_RCC_getPCLK2Freq();
	else
		Pclk = MCAL_RCC_getPCLK1Freq();

	BRR = UART_BRR_Register(Pclk,UART_config->BaudRate_Speed);
	USARTx->BRR = BRR;

	//4-set data size
	//Bit 12 M: Word length
	USARTx->CR1 |= UART_config->PayLoad_Data;

	//5-set no of stop bits
	//Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= UART_config->Stop_bits;

	//6-set parity
	//Bit 9 PS: Parity selection, Bit 10 PCE: Parity control enable
	USARTx->CR1 |= UART_config->Parity;

	//7-set HardWare flow CTRL
	USARTx->CR3 |= UART_config->FLOW_CTRL;

	//8-Enable/Disable IRQ
	if(UART_config->IRQ_ENABLE != UART_IRQ_ENABLE_NONE)
	{
		USARTx->CR1 |= UART_config->IRQ_ENABLE;
		//ENABLE NVIC for USARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_ENABLE;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_ENABLE;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_ENABLE;
	}

	//9-set IRQ CallBack Function
	GP_IRQ_CallBack = UART_config->P_IRQ_CallBack;
}


/**================================================================
 * @Fn 				-	MCAL_UART_DeInit
 * @brief 			-	Resets UART(supported Mode Asynchronous Only)
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	Reset The Module By RCC
 *
 */
void MCAL_UART_DeInit(USART_TypeDef *USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE;
	}

	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE;
	}

	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE;
	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_GPIO_Set_Pins
 * @brief 			-	Initializes GPIO Pins to be connected with the selected UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	Must open clock for AFIO & GPIO After GPIO Initialization
 *
 */
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef *USARTx)
{
	GPIO_Pinconfig_t pin_cfg;
	if(USARTx == USART1)
	{
		//TX pin at PA9
		pin_cfg.PinNumber = GPIO_PIN_9;
		pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pin_cfg);
		//RX pin at PA10
		pin_cfg.PinNumber = GPIO_PIN_10;
		pin_cfg.Mode = GPIO_MODE_Input_FLU;
		MCAL_GPIO_Init(GPIOA, &pin_cfg);
		//Check for Flow Control when Enabled
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_CTS || Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_CTS_RTS)
		{
			//CTS at Pin PA11
			pin_cfg.PinNumber = GPIO_PIN_11;
			pin_cfg.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOA, &pin_cfg);
		}
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_RTS || Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_CTS_RTS)
		{
			//RTS at Pin PA12
			pin_cfg.PinNumber = GPIO_PIN_12;
			pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
			pin_cfg.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_cfg);
		}
	}

	else if(USARTx == USART2)
	{
		//TX pin at PA2
		pin_cfg.PinNumber = GPIO_PIN_2;
		pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pin_cfg);
		//RX pin at PA3
		pin_cfg.PinNumber = GPIO_PIN_3;
		pin_cfg.Mode = GPIO_MODE_Input_FLU;
		MCAL_GPIO_Init(GPIOA, &pin_cfg);
		//Check for Flow Control when Enabled
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_CTS || UART_FLOWCTRL_CTS_RTS)
		{
			//CTS at Pin PA0
			pin_cfg.PinNumber = GPIO_PIN_0;
			pin_cfg.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOA, &pin_cfg);
		}
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_RTS || UART_FLOWCTRL_CTS_RTS)
		{
			//RTS at Pin PA1
			pin_cfg.PinNumber = GPIO_PIN_1;
			pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
			pin_cfg.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pin_cfg);
		}
	}

	else if(USARTx == USART3)
	{
		//TX pin at PB10
		pin_cfg.PinNumber = GPIO_PIN_10;
		pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pin_cfg);
		//RX pin at PB11
		pin_cfg.PinNumber = GPIO_PIN_11;
		pin_cfg.Mode = GPIO_MODE_Input_FLU;
		MCAL_GPIO_Init(GPIOB, &pin_cfg);
		//Check for Flow Control when Enabled
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_CTS || UART_FLOWCTRL_CTS_RTS)
		{
			//CTS at Pin PB13
			pin_cfg.PinNumber = GPIO_PIN_13;
			pin_cfg.Mode = GPIO_MODE_Input_FLU;
			MCAL_GPIO_Init(GPIOB, &pin_cfg);
		}
		if(Global_UART_config->FLOW_CTRL == UART_FLOWCTRL_RTS || UART_FLOWCTRL_CTS_RTS)
		{
			//RTS at Pin PB14
			pin_cfg.PinNumber = GPIO_PIN_14;
			pin_cfg.Mode = GPIO_MODE_Output_AF_PP;
			pin_cfg.Output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pin_cfg);
		}
	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_SendData
 * @brief 			-	Send Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	TxBuffer : Buffer Which holds the TX data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_SendData(USART_TypeDef *USARTx, uint16_t *TxBuffer, enum Polling_mechanism PollingEN)
{
	if(PollingEN == enable)
	{
		//wait for transmit data register to be empty
		while(!(USARTx->SR & 1<<7));
	}
//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
//	because it is replaced by the parity.
//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
//	bit
	//check data transmitted is 9BIT OR 8BIT
	if(Global_UART_config->PayLoad_Data == UART_PAYLOAD_DATA_9BIT)
	{
		USARTx->DR = (*((uint16_t *)TxBuffer) & (uint16_t)0x01ff);
	}
	else if(Global_UART_config->PayLoad_Data == UART_PAYLOAD_DATA_8BIT)
	{
		USARTx->DR = (*((uint16_t *)TxBuffer) & (uint8_t)0xff);
	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_ReceiveData
 * @brief 			-	Receive Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	RxBuffer : Buffer which holds Received data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx, uint16_t *RxBuffer, enum Polling_mechanism PollingEN)
{
	if(PollingEN == enable)
	{
		//wait for Received data to be ready for read
		while(!(USARTx->SR & 1<<5));
	}
	//check data Received is 9BIT OR 8BIT
	//9 BIT Received Data
	if(Global_UART_config->PayLoad_Data == UART_PAYLOAD_DATA_9BIT)
	{
		if(Global_UART_config->Parity == UART_PARITY_DISABLE)
		{
			*((uint16_t *)RxBuffer) = USARTx->DR;
		}
		else
		{
			*((uint16_t *)RxBuffer) = (USARTx->DR & (uint8_t)0xff);
		}

	}
	//8 BIT Received Data
	else if(Global_UART_config->PayLoad_Data == UART_PAYLOAD_DATA_8BIT)
	{
		if(Global_UART_config->Parity == UART_PARITY_DISABLE)
		{
			*((uint16_t *)RxBuffer) = (USARTx->DR & (uint8_t)0xff);
		}
		else
		{
			*((uint16_t *)RxBuffer) = (USARTx->DR & (uint8_t)0x7f);
		}

	}
}


/**================================================================
 * @Fn 				-	MCAL_UART_WAIT_TC
 * @brief 			-	Waits for transmission complete flag for last data transmitted
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx)
{
	while(!(USARTx->SR >> 6) & 0x01);
}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

void USART1_IRQHandler(void)
{
	GP_IRQ_CallBack();
}


void USART2_IRQHandler(void)
{
	GP_IRQ_CallBack();
}


void USART3_IRQHandler(void)
{
	GP_IRQ_CallBack();
}





