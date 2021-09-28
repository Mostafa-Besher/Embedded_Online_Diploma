/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Sep 27, 2021
 *      Author: MostafaBesher
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_

#include "stm32_f103c6_I2C_driver.h"



#define EEPROM_ADDRESS					0x2A


//APIS
void EEPROM_Init(void);
uint8_t EEPROM_write_NBytes(uint32_t Memort_address, uint8_t *Byte, uint32_t Data_Length);
uint8_t EEPROM_Read_NBytes(uint32_t Memory_address, uint8_t *Byte, uint32_t Data_Length);







#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
