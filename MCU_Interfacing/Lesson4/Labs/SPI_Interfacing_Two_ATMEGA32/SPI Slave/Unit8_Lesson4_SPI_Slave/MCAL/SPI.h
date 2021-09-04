/*
 * SPI.h
 *
 * Created: 9/3/2021 7:42:26 PM
 *  Author: MOSTAFA
 */ 


#ifndef SPI_H_
#define SPI_H_


//================================
//			INCLUDES
//================================

#include "MCAL/GPIO.h"
#include <stdint.h>

//================================
//			MACROS
//================================

//Registers Macros
#define SPCR	*((volatile unsigned char *)(0x2D))
#define SPSR	*((volatile unsigned char *)(0x2E))
#define SPDR	*((volatile unsigned char *)(0x2F))

//pins macros
#define SS				4
#define MOSI			5
#define MISO			6
#define SCK				7

//SPI mode selection macros
//#define MASTER_MODE	
#define SLAVE_MODE	

//================================
//			APIS
//================================
void SPI_INIT(void);
void SPI_Send_Data(uint8_t data);
uint8_t SPI_Recieve_Data(void);





#endif /* SPI_H_ */