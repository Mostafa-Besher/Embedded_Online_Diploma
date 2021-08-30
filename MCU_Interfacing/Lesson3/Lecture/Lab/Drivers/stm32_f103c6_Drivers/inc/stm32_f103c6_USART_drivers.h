/*
 * stm32_f103c6_USART_drivers.h
 *
 *  Created on: Aug 26, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32_F103C6_USART_DRIVERS_H_
#define INC_STM32_F103C6_USART_DRIVERS_H_



//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_f103c6_RCC_driver.h"
#include "stm32_f103c6_gpio_drivers.h"


//----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t		USART_Mode;				//select TX/RX Enable/Disable
										//This parameter must be set according to @ref USART_MODE_DEFINE

	uint32_t	BaudRate_Speed;			//set the baud rate speed value
										//This parameter must be set according to @ref UART_BAUDRATE_SPEED_DEFINE

	uint16_t 	PayLoad_Data;			//select size of data bits transmitted or received in a frame
										//This parameter must be set according to @ref UART_PAYLOAD_DATA_DEFINE

	uint16_t 	Stop_bits;				//select the number of stop bits
										//This parameter must be set according to @ref UART_STOP_BITS_DEFINE

	uint16_t	Parity;					//select even parity or odd parity or disable parity
										//This parameter must be set according to @ref UART_PARITY_DEFINE

	uint16_t	FLOW_CTRL;				//Specifies whether hardware flow control is disabled/enabled
										//This parameter must be set according to @ref UART_FLOWCTRL_DEFINE

	uint16_t    IRQ_ENABLE;				//Select ENABLE/DISABLE interrupt
										//This parameter must be set according to @ref UART_IRQ_ENABLE_DEFINE

	void (* P_IRQ_CallBack)(void);		//set the C Function which will be called once IRQ Happens

}USART_CONFIG_t;







//----------------------------
//Macros Configuration References
//-----------------------------

//@ref USART_MODE_DEFINE
#define USART_MODE_TX						((uint32_t)(1<<3))
#define USART_MODE_RX						((uint32_t)(1<<2))
#define USART_MODE_TX_RX					((uint32_t)(1<<3 | 1<<2))

//@ref UART_BAUDRATE_SPEED_DEFINE
#define UART_BAUDRATE_SPEED_2400			2400
#define UART_BAUDRATE_SPEED_9600			9600
#define UART_BAUDRATE_SPEED_19200			19200
#define UART_BAUDRATE_SPEED_57600			57600
#define UART_BAUDRATE_SPEED_115200			115200
#define UART_BAUDRATE_SPEED_230400			230400
#define UART_BAUDRATE_SPEED_460800			460800
#define UART_BAUDRATE_SPEED_921600			921600
#define UART_BAUDRATE_SPEED_2250000			2250000
#define UART_BAUDRATE_SPEED_4500000			4500000

//@ref UART_PAYLOAD_DATA_DEFINE
#define UART_PAYLOAD_DATA_8BIT				(uint32_t)(0)
#define UART_PAYLOAD_DATA_9BIT				(uint32_t)(1<<12)

//@ref UART_STOP_BITS_DEFINE
#define UART_STOP_BITS_1BIT					(uint32_t)(0)
#define UART_STOP_BITS_HALFBIT				(uint32_t)(1<<12)
#define UART_STOP_BITS_2BIT					(uint32_t)(3<<12)
#define UART_STOP_BITS_1_HALFBIT			(uint32_t)(2<<12)

//@ref UART_PARITY_DEFINE
#define UART_PARITY_DISABLE					(uint32_t)(0)
#define UART_PARITY_EVEN					(uint32_t)(1<<10)
#define UART_PARITY_ODD						(uint32_t)(1<<10 | 1<<9)

//@ref UART_FLOWCTRL_DEFINE
#define UART_FLOWCTRL_NONE					(uint32_t)(0)
#define UART_FLOWCTRL_CTS					(uint32_t)(1<<9)
#define UART_FLOWCTRL_RTS					(uint32_t)(1<<8)
#define UART_FLOWCTRL_CTS_RTS				(uint32_t)(1<<8 | 1<<9)

//@ref UART_IRQ_ENABLE_DEFINE
#define UART_IRQ_ENABLE_NONE				(uint32_t)(0)
#define UART_IRQ_ENABLE_TXE					(uint32_t)(1<<7)	//Transmit data register empty
#define UART_IRQ_ENABLE_TCIE				(uint32_t)(1<<6)	//Transmission complete
#define UART_IRQ_ENABLE_RXNE				(uint32_t)(1<<5)	//Received data ready to be read
#define UART_IRQ_ENABLE_PE					(uint32_t)(1<<8)	//Parity error


enum Polling_mechanism
{
	disable,
	enable
};


//BaudRate Calculations
//USARTDiv = fclk / (16 * BaudRate)
//USARTDIV_MUL100 = uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100

#define USARTDiv(_pclk,_Baud)				(uint32_t)( _pclk / (16 * _Baud) )
#define USARTDiv_Mul100(_pclk,_Baud)		(uint32_t)((25 * _pclk) / (4 * _Baud))
#define Mantissa_Mul100(_pclk,_Baud)		(uint32_t)(USARTDiv(_pclk,_Baud) * 100)
#define Mantissa(_pclk,_Baud)				(uint32_t)(USARTDiv(_pclk,_Baud))
#define Div_Fraction(_pclk,_Baud)			(uint32_t)(((USARTDiv_Mul100(_pclk,_Baud) - Mantissa_Mul100(_pclk,_Baud)) * 16) / 100)
#define UART_BRR_Register(_pclk,_Baud)		((Mantissa(_pclk,_Baud)) << 4) | (Div_Fraction(_pclk,_Baud) & 0xf)




/*
* ==============================================================================
* 				  APIs Supported by "MCAL USART DRIVER"
* ==============================================================================
*/

void MCAL_UART_Init(USART_TypeDef *USARTx, USART_CONFIG_t * UART_config);
void MCAL_UART_DeInit(USART_TypeDef *USARTx);

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef *USARTx);

void MCAL_UART_SendData(USART_TypeDef *USARTx, uint16_t *TxBuffer, enum Polling_mechanism PollingEN);
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx, uint16_t *RxBuffer, enum Polling_mechanism PollingEN);

void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx);





#endif /* INC_STM32_F103C6_USART_DRIVERS_H_ */
