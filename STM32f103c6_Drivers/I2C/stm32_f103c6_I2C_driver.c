/*
 * stm32_f103c6_I2C_driver.c
 *
 *  Created on: Sep 24, 2021
 *      Author: MostafaBesher
 */

/*
 *=======================================================================
 *						INCLUDES
 *=======================================================================
 *
*/

#include "stm32_f103c6_I2C_driver.h"
#include "stm32_f103c6_RCC_driver.h"


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/


I2C_Config_t	Global_I2C_Config[2];


/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/


#define I2C1_INDEX					0
#define I2C2_INDEX					1




/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/


/**================================================================
 * @Fn 				-	MCAL_I2C_Init
 * @brief 			-	Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- 	I2C_Config : a pointer to I2C_Config_t structure that contains
 * 									the configuration information for the specified I2C Module
 * @retval 			-	none
 * Note 			-	Supported for I2C SM mode only
 * 					-	Support only 7-bit address mode
 *
 */
void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Config_t *I2C_Config)
{
	uint32_t FREQ_Range = 0;

	//Enable RCC Clock For Selected I2C
	if(I2Cx == I2C1)
	{
		RCC_I2C1_CLK_EN();
		Global_I2C_Config[I2C1_INDEX] = *I2C_Config;
	}
	else
	{
		RCC_I2C2_CLK_EN();
		Global_I2C_Config[I2C2_INDEX] = *I2C_Config;
	}


	//Enable or disable stretching mode
	I2Cx->I2C_CR1 |= I2C_Config->clock_stretching;

	//Enable or disable general call
	I2Cx->I2C_CR1 |= I2C_Config->General_Call;

	//select SMBUS mode or I2C Mode
	I2Cx->I2C_CR1 |= I2C_Config->I2C_Mode;

	//Enable or disable Automatic ACK
	I2Cx->I2C_CR1 |= I2C_Config->I2C_ACK_Control;

	#ifdef I2C_MASTER_MODE

	//choose master mode SM or FM
	I2Cx->I2C_CCR |= I2C_Config->I2C_Master_Mode;

	/*****************************configure clock speed*****************************/

	//1- get APB1 clock speed
	//APB1 clock speed must be between 2mhz up to 50mhz
//	Bits 5:0 FREQ[5:0]: Peripheral clock frequency
//	The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
//	connected to APB). The FREQ field is used by the peripheral to generate data setup and
//	hold times compliant with the I2C specifications. The minimum allowed frequency is 2 MHz,
//	the maximum frequency is limited by the maximum APB frequency and cannot exceed
//	50 MHz (peripheral intrinsic maximum limit).
//	0b000000: Not allowed
//	0b000001: Not allowed
//	0b000010: 2 MHz
//	...
//	0b110010: 50 MHz
//	Higher than 0b100100: Not allowed
	FREQ_Range = (uint32_t)((MCAL_RCC_getPCLK1Freq() / 1000000));
	I2Cx->I2C_CR2 |= FREQ_Range;

	//2- set the SCL clock speed
//	Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode)
//	Controls the SCL clock in master mode.
//	Sm mode or SMBus:
//	Thigh = CCR * TPCLK1
//	Tlow = CCR * TPCLK1
	I2Cx->I2C_CCR |= (uint32_t)( (MCAL_RCC_getPCLK1Freq()) / (I2C_Config->clock_speed << 1) );		//(I2C_Config->clock_speed << 1) = 2 * I2C_Config->clock_speed

	//3- configure Maximum rise time in SM mode(TRISE REG)
	//Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
	I2Cx->I2C_TRISE |= (uint32_t)( FREQ_Range + 1 );

	#endif

	#ifdef I2C_SLAVE_MODE

	//select slave address mode(support only 7-bit address mode)
	I2Cx->I2C_OAR1 |= I2C_Config->Slave_Address.Slave_Address_Mode;

	//Set slave address when device is in slave mode
	//set first address
	I2Cx->I2C_OAR1 |= ( (I2C_Config->Slave_Address.Slave_First_Address) << 1);

	//if using 10-bit address mode
	/*
	if(I2C_Config->Slave_Address.Slave_Address_Mode == Slave_Address_Mode_10bit)
	{
		I2Cx->I2C_OAR1 |= ((I2C_Config->Slave_Address.Slave_Second_Address & 0xc0) << 2);
		I2Cx->I2C_OAR1 |= (I2C_Config->Slave_Address.Slave_Second_Address & 0x01);
	}
	*/

	//check for dual address if using 7-bit address mode
	if(I2C_Config->Slave_Address.Slave_Address_Mode == Slave_Address_Mode_7bit)
	{
		//if Enable Dual Address(in 7-bit address mode only)
		if(I2C_Config->Slave_Address.Enable_Dual_Address == 1)
		{
			//Enable Dual Address
			//I2C_OAR2 Register
//			Bit 0 ENDUAL: Dual addressing mode enable
//			0: Only OAR1 is recognized in 7-bit addressing mode
//			1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
			I2Cx->I2C_OAR2 |= 1<<0;
			//Set second address
			I2Cx->I2C_OAR2 |= ((I2C_Config->Slave_Address.Slave_Second_Address) << 1);
		}
	}

	//Enable Interrupt for Slave Mode
	//Enable NVIC IRQ for I2C_Event_interrupt & Error interrupt
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_ENABLE;
		NVIC_IRQ32_I2C1_ER_ENABLE;
	}
	else
	{
		NVIC_IRQ33_I2C2_EV_ENABLE;
		NVIC_IRQ34_I2C2_ER_ENABLE;
	}

	//Enable ITEVFEN, ITBUFEN and ITERREN bits in I2C_CR2
	I2Cx->I2C_CR2 |= (uint32_t)(1<<9);			//ITEVFEN
	I2Cx->I2C_CR2 |= (uint32_t)(1<<10);			//ITBUFEN
	I2Cx->I2C_CR2 |= (uint32_t)(1<<8);			//ITERREN


	#endif


	//Enable Selected I2C peripheral
	I2Cx->I2C_CR1 |= (1<<0);
}


/**================================================================
 * @Fn 				-	MCAL_I2C_DeInit
 * @brief 			-	Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			-	none
 * Note 			-	Reset The Module By RCC & Disable NVIC
 *
 */
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx)
{
	if(I2Cx == I2C1)
	{
		//Reset I2C1
		RCC_I2C1_RESET();
		//Disable NVIC IRQ for I2C1
		NVIC_IRQ31_I2C1_EV_DISABLE;
		NVIC_IRQ32_I2C1_ER_DISABLE;
	}
	else if(I2Cx == I2C2)
	{
		//Reset I2C2
		RCC_I2C2_RESET();
		//Disable NVIC IRQ for I2C2
		NVIC_IRQ33_I2C2_EV_DISABLE;
		NVIC_IRQ34_I2C2_ER_DISABLE;
	}
}


/**================================================================
 * @Fn 				-	MCAL_I2C_GPIO_Set_Pins
 * @brief 			-	Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			-	none
 * Note 			-	Must open clock for AFIO & GPIO After GPIO Initialization
 * 					-	Supported for I2C SM MODE only
 *
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef *I2Cx)
{
	GPIO_Pinconfig_t	GPIO_CFG;
	if(I2Cx == I2C1)
	{
		//I2C1_SCL
		GPIO_CFG.PinNumber = GPIO_PIN_6;
		GPIO_CFG.Mode = GPIO_MODE_Output_AF_OD;
		GPIO_CFG.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &GPIO_CFG);
		//I2C1_SDA
		GPIO_CFG.PinNumber = GPIO_PIN_7;
		GPIO_CFG.Mode = GPIO_MODE_Output_AF_OD;
		GPIO_CFG.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &GPIO_CFG);
	}
	else if(I2Cx == I2C2)
	{
		//I2C2_SCL
		GPIO_CFG.PinNumber = GPIO_PIN_10;
		GPIO_CFG.Mode = GPIO_MODE_Output_AF_OD;
		GPIO_CFG.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &GPIO_CFG);
		//I2C2_SDA
		GPIO_CFG.PinNumber = GPIO_PIN_11;
		GPIO_CFG.Mode = GPIO_MODE_Output_AF_OD;
		GPIO_CFG.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &GPIO_CFG);
	}
}


/**================================================================
 * @Fn 				-	MCAL_I2C_MASTER_TX
 * @brief 			-	Master Send data with I2C
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- 	device_address : slave address
 * @param [in] 		-	data : a pointer to the data which will be send
 * @param [in] 		-	data_len : number of data bytes to be Transmitted
 * @param [in] 		-	Stop : select send stop bit or not
 * @param [in] 		-	start : select send start or repeated start
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_I2C_MASTER_TX(I2C_TypeDef *I2Cx, uint16_t device_address, uint8_t *data, uint8_t data_len, STOP_Condition Stop, START_Condition start)
{
	int i = 0;
	//1- Send start bit
	I2C_Generate_Start(I2Cx, start, Enable);
	//check if start bit is sent
	while(! (I2C_Get_FlagStatus(I2Cx, SB)));

	//2- Send Slave Address(7-bit) + Write
	I2C_Send_Address(I2Cx, device_address, Transmitter);
	//check if Address is sent
	while(! (I2C_Get_FlagStatus(I2Cx, ADDR)));

	//3- check if BUSY,TRA,MSL,TXE are all set (check for busy flag here to handle if master lost Arbitration)
	while(! (I2C_Get_FlagStatus(I2Cx, Master_Transmitter_Event)));

	//4- send data
	for(i=0; i<data_len; i++)
	{
		I2Cx->I2C_DR = data[i];
		//check for EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(! (I2C_Get_FlagStatus(I2Cx, TXE)));
	}

	//5- send stop bit
	if(Stop == With_STOP)
	{
		I2C_Stop(I2Cx, Enable);
	}
}


/**================================================================
 * @Fn 				-	MCAL_I2C_MASTER_RX
 * @brief 			-	Master Receive data with I2C
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- 	device_address : slave address
 * @param [in] 		-	data : a pointer to the data which will be send
 * @param [in] 		-	data_len : number of data bytes to be Received
 * @param [in] 		-	Stop : select send stop bit or not
 * @param [in] 		-	start : select send start or repeated start
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_I2C_MASTER_RX(I2C_TypeDef *I2Cx, uint16_t device_address, uint8_t *data, uint8_t data_len, STOP_Condition Stop, START_Condition start)
{
	int i = 0;
	uint8_t index = I2Cx == I2C1? I2C1_INDEX : I2C2_INDEX;
	//1- Send start bit
	I2C_Generate_Start(I2Cx, start, Enable);
	//check if start bit is sent
	while(! (I2C_Get_FlagStatus(I2Cx, SB)));

	//2- Send Slave Address(7-bit) + Read
	I2C_Send_Address(I2Cx, device_address, Receiver);
	//check if Address is sent
	while(! (I2C_Get_FlagStatus(I2Cx, ADDR)));

	//3- Enable automatic ACK
	I2C_ACKConfig(I2Cx, Enable);

	//4- Read Data
	if(data_len)
	{
		for(i=0; i<data_len; i++)
		{
			//check for EV7 : RXNE=1 cleared by reading DR register
			while(! (I2C_Get_FlagStatus(I2Cx, RXNE)));
			//Read Data
			*data = I2Cx->I2C_DR;
			data++;
		}
	}

	//5- send NACK
	I2C_ACKConfig(I2Cx, Disable);

	//6- send stop bit
	if(Stop == With_STOP)
	{
		I2C_Stop(I2Cx, Enable);
	}

	//7- ReEnable automatic ACK
	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Control_Enable)
		I2C_ACKConfig(I2Cx, Enable);
	else
		I2C_ACKConfig(I2Cx, Disable);

}



/**================================================================
 * @Fn 				-	MCAL_Slave_SendData
 * @brief 			-	Slave send data to master using interrupt mechanism
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- 	data : slave data to be sent to master
 * @retval 			-	none
 * Note 			-	support interrupt mechanism only
 *
 */
void MCAL_I2C_Slave_SendData(I2C_TypeDef *I2Cx, uint8_t data)
{
	I2Cx->I2C_DR = data;
}



/**================================================================
 * @Fn 				-	MCAL_Slave_ReceiveData
 * @brief 			-	Slave Receive data from master using interrupt mechanism
 * @param [in] 		- 	I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			-	Received data
 * Note 			-	support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_Slave_ReceiveData(I2C_TypeDef *I2Cx)
{
	return (I2Cx->I2C_DR);
}





/*
 *=======================================================================
 *							GENERIC APIS
 *=======================================================================
 *
*/


Flagstatus I2C_Get_FlagStatus(I2C_TypeDef *I2Cx, status flag)
{
	//volatile uint32_t dummy_read;
	Flagstatus bit_status = RESET;
	uint32_t flag1 = 0, flag2 = 0, last_event = 0;
	switch(flag)
	{
	case BUS_BUSY :
	{
		if(I2Cx->I2C_SR2 & ((uint32_t)(1<<1)) )
			bit_status = SET;
		else
			bit_status = RESET;
	}
	break;
	case SB :
	{
		if(I2Cx->I2C_SR1 & ((uint32_t)(1<<0)) )
			bit_status = SET;
		else
			bit_status = RESET;
	}
	break;
	case ADDR :
	{
		if(I2Cx->I2C_SR1 & ((uint32_t)(1<<1)) )
			bit_status = SET;
		else
			bit_status = RESET;

		//This bit is cleared by software reading SR1 register followed reading SR2
		//dummy_read = I2Cx->I2C_SR2;
	}
	break;
	case TXE :
	{
		if(I2Cx->I2C_SR1 & ((uint32_t)(1<<7)) )
			bit_status = SET;
		else
			bit_status = RESET;
	}
	break;
	case Master_Transmitter_Event :
	{
		flag1 = Master_Transmitter_Event & (0x0000ffff);
		flag2 =  Master_Transmitter_Event >> 16;
		last_event = ((I2Cx->I2C_SR1 & flag1) | ((I2Cx->I2C_SR2 & flag2) << 16) );
		if(last_event == flag)
			bit_status = SET;
		else
			bit_status = RESET;
	}
	break;
	case RXNE :
	{
		if(I2Cx->I2C_SR1 & ((uint32_t)(1<<6)) )
			bit_status = SET;
		else
			bit_status = RESET;
	}
	break;


	}

	return bit_status;
}



void I2C_Generate_Start(I2C_TypeDef *I2Cx,START_Condition start, functional_state new_state)
{
	//check if bus is busy
	if(start != Repeated_START)
		while(I2C_Get_FlagStatus(I2Cx, BUS_BUSY));
	if(new_state == Enable)
	{
		//Send Start
		I2Cx->I2C_CR1 |= (uint32_t)(1<<8);
	}
	else if(new_state == Disable)
	{
		I2Cx->I2C_CR1 &= ~((uint32_t)(1<<8));
	}

}



void I2C_Send_Address(I2C_TypeDef *I2Cx, uint16_t device_address,I2C_Direction direction)
{
	//support 7-bit address mode only
	if(direction == Receiver)
	{
		I2Cx->I2C_DR = ((device_address<<1) | (0x01));
	}
	else if(direction == Transmitter)
	{
		I2Cx->I2C_DR = (device_address<<1);
	}
}



void I2C_Stop(I2C_TypeDef *I2Cx, functional_state new_state)
{
	if(new_state == Enable)
	{
		//enable stop bit
		I2Cx->I2C_CR1 |= ((uint32_t)(1<<9));
	}
	else
	{
		//disable stop
		I2Cx->I2C_CR1 &= ~(((uint32_t) (1<<9)));
	}
}


void I2C_ACKConfig(I2C_TypeDef *I2Cx, functional_state new_state)
{
	if(new_state == Enable)
	{
		I2Cx->I2C_CR1 |= ((uint32_t)(1<<10));
	}
	else
	{
		I2Cx->I2C_CR1 &= ~((uint32_t)(1<<10));
	}
}




/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummy = 0;
	uint32_t temp1 = 0, temp2 = 0, temp3 = 0;
	temp1 = (I2C1->I2C_CR2 & ((uint32_t)1<<9));		//ITEVTEN
	temp2 = (I2C1->I2C_CR2 & ((uint32_t)1<<10));	//ITBUFEN
	temp3 = (I2C1->I2C_SR1 & ((uint32_t)1<<4));		//STOPF

	//Handle Stop Condition Event
	if(temp1 && temp3)
	{
		//STOPF Cleared by software reading the SR1 register followed by a write in the CR1 register,
		// i have already read SR1 in temp3
		//then next statement i write to CR1
		I2C1->I2C_CR1 |= 0x0000;
		Global_I2C_Config[I2C1_INDEX].Slave_CallBack(I2C_EV_STOP);
	}
	//----------------------------------------------------------
	//Handle Received address matched.
	temp3 = (I2C1->I2C_SR1 & ((uint32_t)1<<1));		//ADDR
	if(temp1 && temp3)
	{
		//clear ADDR flag
		//In slave mode, it is recommended to perform the complete clearing sequence (READ
		//SR1 then READ SR2) after ADDR is set.
		dummy  = I2C1->I2C_SR1;
		dummy  = I2C1->I2C_SR2;
		//check master mode or slave mode
		if( I2C1->I2C_SR2 & ((uint32_t)(1<<0)) )
		{
			//master mode(using polling mechanism not interrupt)
		}
		else
		{
			//slave mode
			Global_I2C_Config[I2C1_INDEX].Slave_CallBack(I2C_EV_ADD_MATCHED);
		}

	}
	//----------------------------------------------------------
	//Handle TxE: Data register empty (master request data from slave)-->slave_transmitter
	temp3 = (I2C1->I2C_SR1 & ((uint32_t)1<<7));		//TXE
	if(temp1 && temp2 && temp3)		//in case TXE=1, ITEVTEN=1, ITBUFEN=1
	{
		//check master mode or slave mode
		if( I2C1->I2C_SR2 & ((uint32_t)(1<<0)) )
		{
			//master mode(using polling mechanism not interrupt)
		}
		else
		{
			//slave mode
			//check if slave in transmit mode
			if(I2C1->I2C_SR2 & ((uint32_t)(1<<2)))		//TRA: Transmitter/receiver: 1: Data bytes transmitted
			{
				Global_I2C_Config[I2C1_INDEX].Slave_CallBack(I2C_EV_DATA_REQ);
			}

		}
	}
	//----------------------------------------------------------
	//Handle RxNE: Data register not empty (slave receive data)-->slave_Receiver
	temp3 = (I2C1->I2C_SR1 & ((uint32_t)1<<6));		//RXNE
	if(temp1 && temp2 && temp3)		//in case RXNE=1, ITEVTEN=1, ITBUFEN=1
	{
		//check master mode or slave mode
		if( I2C1->I2C_SR2 & ((uint32_t)(1<<0)) )
		{
			//master mode(using polling mechanism not interrupt)
		}
		else
		{
			//slave mode
			if(!(I2C1->I2C_SR2 & ((uint32_t)(1<<2))))		//TRA: Transmitter/receiver: 0: Data bytes received
			{
				Global_I2C_Config[I2C1_INDEX].Slave_CallBack(I2C_EV_DATA_RCV);
			}
		}
	}
}


void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}


void I2C2_ER_IRQHandler(void)
{

}


