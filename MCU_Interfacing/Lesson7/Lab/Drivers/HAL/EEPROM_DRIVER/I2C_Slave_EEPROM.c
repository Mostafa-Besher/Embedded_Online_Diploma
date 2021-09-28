/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Sep 27, 2021
 *      Author: MostafaBesher
 */


#include "I2C_Slave_EEPROM.h"



void EEPROM_Init(void)
{
	//================ I2C1 INIT ====================
	//SCL -------> PB6
	//SDA -------> PB7

	//I2C Controller act as a master
	I2C_Config_t I2C_cfg;
	I2C_cfg.I2C_Mode = I2C_Mode_I2C_MODE;
	I2C_cfg.clock_stretching = clock_stretching_Enable;
	I2C_cfg.General_Call = General_Call_Enable;
	I2C_cfg.I2C_Master_Mode = I2C_Master_Mode_SM;
	I2C_cfg.clock_speed = CLOCK_SPEED_100KHZ;
	I2C_cfg.I2C_ACK_Control = I2C_ACK_Control_Enable;
	MCAL_I2C_Init(I2C1, &I2C_cfg);
	MCAL_I2C_GPIO_Set_Pins(I2C1);
}



uint8_t EEPROM_write_NBytes(uint32_t Memory_address, uint8_t *Byte, uint32_t Data_Length)
{
	int i = 0;
	uint8_t Buffer[256];
	Buffer[0] = (uint8_t)(Memory_address >> 8);		//high address
	Buffer[1] = (uint8_t)(Memory_address);					//low address
	for(i=2; i<(Data_Length+2); i++)
	{
		Buffer[i]= Byte[i-2];
	}
	MCAL_I2C_MASTER_TX(I2C1, EEPROM_ADDRESS, Buffer, (Data_Length+2), With_STOP, START);
	return 0;
}



uint8_t EEPROM_Read_NBytes(uint32_t Memory_address, uint8_t *Byte, uint32_t Data_Length)
{
	uint8_t Buffer[2];
	Buffer[0] = (uint8_t)(Memory_address >> 8);		//high address
	Buffer[1] = (uint8_t)(Memory_address);			//low address
	MCAL_I2C_MASTER_TX(I2C1, EEPROM_ADDRESS, Buffer, 2, Without_STOP, START);
	MCAL_I2C_MASTER_RX(I2C1, EEPROM_ADDRESS, Byte, Data_Length, With_STOP, Repeated_START);
	return 0;
}












