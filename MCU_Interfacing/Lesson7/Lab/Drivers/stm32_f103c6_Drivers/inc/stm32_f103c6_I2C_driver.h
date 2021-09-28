/*
 * stm32_f103c6_I2C_driver.h
 *
 *  Created on: Sep 24, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"




//--------------------------------------
//User type definitions (structures)
//--------------------------------------

typedef struct
{
	uint32_t	Enable_Dual_Address;		  //Enable	 1		Disable		0
	uint8_t		Slave_First_Address;
	uint8_t		Slave_Second_Address;
	uint32_t	Slave_Address_Mode;			  // This parameter must be set based on @ref Slave_Address_Mode_DEFINE
}I2C_slave_address_t;



typedef enum
{
	I2C_EV_STOP,
	I2C_EV_ADD_MATCHED,
	I2C_EV_DATA_REQ,							//APP_Layer should send data (I2C slave send data)
	I2C_EV_DATA_RCV								//APP_Layer should receive data (I2C slave receive data)
}Slave_State;



typedef struct
{
	uint32_t	clock_speed;					// specifies I2C clock speed
												// This parameter must be set based on @ref CLOCK_SPEED_DEFINE

	uint32_t	clock_stretching;				// specifies Enable or Disable clock stretching in slave mode only
												// This parameter must be set based on @ref clock_stretching_DEFINE

	uint32_t	General_Call;					// specifies Enable or Disable General_Call
												// This parameter must be set based on @ref General_Call_DEFINE

	uint32_t	I2C_Master_Mode;				// specifies I2C Master mode SM mode or FM mode
												// This parameter must be set based on @ref I2C_Master_Mode_DEFINE

	uint32_t	I2C_Mode;						// specifies I2C SMBUS mode or I2C mode
												// This parameter must be set based on @ref I2C_Mode_DEFINE

	uint32_t	I2C_ACK_Control;				// Enable ACK by Hardware or Disable ACK
												// This parameter must be set based on @ref I2C_ACK_Control_DEFINE

	I2C_slave_address_t		Slave_Address;		//slave address information from user


	void (* Slave_CallBack)(Slave_State state); 	//set the C Function which will be called once IRQ Happens

}I2C_Config_t;





//-----------------------------------
//Macros Configuration References
//-----------------------------------


//@ref @ref CLOCK_SPEED_DEFINE
#define CLOCK_SPEED_50KHZ							(50000U)
#define CLOCK_SPEED_100KHZ							(100000U)

//@ref clock_stretching_DEFINE
//I2C_CR1
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
//it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled
#define clock_stretching_Enable						(uint32_t)(0)
#define clock_stretching_Disable					(uint32_t)(1<<7)

//@ref General_Call_DEFINE
//I2C_CR1
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed
#define General_Call_Enable							(uint32_t)(1<<6)
#define General_Call_Disable						(uint32_t)(0)

// @ref I2C_Master_Mode_DEFINE
//I2C_CCR
//Bit 15 F/S: I2C master mode selection
//0: Sm mode I2C
//1: Fm mode I2C
#define I2C_Master_Mode_SM							(uint32_t)(0)
#define I2C_Master_Mode_FM							(uint32_t)(1<<15)

//@ref I2C_Mode_DEFINE
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C_MODE							(uint32_t)(0)
#define I2C_Mode_SMBUS_MODE							(uint32_t)(1<<1)

//@ref Slave_Address_Mode_DEFINE
//I2C_OAR1
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define Slave_Address_Mode_7bit						(uint32_t)(0)
#define Slave_Address_Mode_10bit					(uint32_t)(1<<15)

//@ref I2C_ACK_Control_DEFINE
//I2C_CR1
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Control_Enable						(uint32_t)(1<<10)
#define I2C_ACK_Control_Disable						(uint32_t)(0)


/*==================================================================================*/

//I2C MODE SELECTION
#define I2C_MASTER_MODE
//#define I2C_SLAVE_MODE


typedef enum
{
	RESET,
	SET
}Flagstatus;


typedef enum
{
	BUS_BUSY,	//BUSY: Bus busy 1: Communication ongoing on the bus
	SB,			//SB: Start bit (Master mode) 1: Start condition generated.
	ADDR,		//ADDR: Address sent (master mode)/matched (slave mode)
	TXE,		//TxE: Data register empty (transmitters)
	RXNE,		//RxNE: Data register not empty (receivers)
	Master_Transmitter_Event = ((uint32_t)(0x00070080))		//check if BUSY,TRA,MSL,TXE flags are all set
}status;


typedef enum
{
	With_STOP,
	Without_STOP
}STOP_Condition;


typedef enum
{
	START,
	Repeated_START
}START_Condition;


typedef enum
{
	Disable,
	Enable
}functional_state;


typedef enum
{
	Transmitter,
	Receiver
}I2C_Direction;





/*
* ==============================================================================
* 				  APIs Supported by "MCAL I2C DRIVER"
* ==============================================================================
*/

void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Config_t *I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef *I2Cx);


void MCAL_I2C_MASTER_TX(I2C_TypeDef *I2Cx, uint16_t device_address, uint8_t *data, uint8_t data_len, STOP_Condition Stop, START_Condition start);
void MCAL_I2C_MASTER_RX(I2C_TypeDef *I2Cx, uint16_t device_address, uint8_t *data, uint8_t data_len, STOP_Condition Stop, START_Condition start);


//slave interrupt mechanism
void MCAL_I2C_Slave_SendData(I2C_TypeDef *I2Cx, uint8_t data);
uint8_t MCAL_I2C_Slave_ReceiveData(I2C_TypeDef *I2Cx);


//Generic APIS
Flagstatus I2C_Get_FlagStatus(I2C_TypeDef *I2Cx, status flag);
void I2C_Generate_Start(I2C_TypeDef *I2Cx,START_Condition start, functional_state new_state);
void I2C_Send_Address(I2C_TypeDef *I2Cx, uint16_t device_address,I2C_Direction direction);
void I2C_Stop(I2C_TypeDef *I2Cx, functional_state new_state);
void I2C_ACKConfig(I2C_TypeDef *I2Cx, functional_state new_state);






#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
