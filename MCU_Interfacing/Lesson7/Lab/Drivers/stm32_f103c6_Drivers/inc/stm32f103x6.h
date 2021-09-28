/*
 * stm32f103x6.h
 *
 *  Created on: Jul 18, 2021
 *      Author: MostafaBesher
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_


//----------------------------
//Includes
//----------------------------

#include <stdint.h>
#include <stdlib.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_memory_BASE								0x08000000UL
#define SRAM_BASE										0x20000000UL
#define System_memory_BASE								0x1FFFF000UL


#define Peripherals_BASE								0x40000000UL

#define Cortex_m3_internal_peripherals_BASE				0xE0000000UL

#define NVIC_BASE										0xE000E100UL

#define NVIC_ISER0			*(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1			*(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2			*(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0			*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1			*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2			*(volatile uint32_t *)(NVIC_BASE + 0x88)

//=========================================================================

//-----------------------------
//Base addresses for AHB BUS Peripherals
//-----------------------------

//RCC
#define	RCC_BASE				0x40021000UL

//-----------------------------
//Base addresses for APB2 BUS Peripherals
//-----------------------------

//GPIO
//A, B fully included in LQFP48 package
#define	GPIOA_BASE				0x40010800UL
#define	GPIOB_BASE				0x40010C00UL
//C, D partially included in LQFP48 package
#define	GPIOC_BASE				0x40011000UL
#define	GPIOD_BASE				0x40011400UL
//E not included in LQFP48 package
#define	GPIOE_BASE				0x40011800UL
//--------

//EXTI
#define	EXTI_BASE				0x40010400UL

//AFIO
#define	AFIO_BASE				0x40010000UL

//USART1
#define USART1_BASE				0x40013800UL

//SPI1
#define SPI1_BASE				0x40013000UL


//-----------------------------
//Base addresses for APB1 BUS Peripherals
//-----------------------------

//USART2
#define USART2_BASE				0x40004400UL

//USART3
#define USART3_BASE				0x40004800UL

//SPI2
#define SPI2_BASE				0x40003800UL

//I2C1
#define I2C1_BASE				0x40005400UL

//I2C2
#define I2C2_BASE				0x40005800UL


//=========================================================================

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
//	volatile uint32_t EXTICR1;
//	volatile uint32_t EXTICR2;
//	volatile uint32_t EXTICR3;
//	volatile uint32_t EXTICR4;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
}I2C_TypeDef;





//=========================================================================

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA		((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE		((GPIO_TypeDef *)GPIOE_BASE)

#define RCC			((RCC_TypeDef *)RCC_BASE)

#define EXTI		((EXTI_TypeDef *)EXTI_BASE)

#define AFIO		((AFIO_TypeDef *)AFIO_BASE)

#define USART1		((USART_TypeDef *)USART1_BASE)

#define USART2		((USART_TypeDef *)USART2_BASE)

#define USART3		((USART_TypeDef *)USART3_BASE)

#define SPI1		((SPI_TypeDef *)SPI1_BASE)

#define SPI2		((SPI_TypeDef *)SPI2_BASE)

#define I2C1		((I2C_TypeDef *)I2C1_BASE)

#define I2C2		((I2C_TypeDef *)I2C2_BASE)

//=========================================================================

//-*-*-*-*-*-*-*-*-*-*-*
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define RCC_GPIOA_CLK_EN()		(RCC ->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()		(RCC ->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()		(RCC ->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()		(RCC ->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()		(RCC ->APB2ENR |= 1<<6)

//AFIO
#define RCC_AFIO_CLK_EN()		(RCC ->APB2ENR |= 1<<0)

//USART clock enable
#define RCC_USART1_CLK_EN()		(RCC ->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN()		(RCC ->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN()		(RCC ->APB1ENR |= 1<<18)
//USART reset mechanism
#define RCC_USART1_RESET()		(RCC ->APB2RSTR |= 1<<14)
#define RCC_USART2_RESET()		(RCC ->APB1RSTR |= 1<<17)
#define RCC_USART3_RESET()		(RCC ->APB1RSTR |= 1<<18)

//SPI clock enable
#define RCC_SPI1_CLK_EN()		(RCC ->APB2ENR |= 1<<12)
#define RCC_SPI2_CLK_EN()		(RCC ->APB1ENR |= 1<<14)
//SPI reset mechanism
#define RCC_SPI1_RESET()		(RCC ->APB2RSTR |= 1<<12)
#define RCC_SPI2_RESET()		(RCC ->APB1RSTR |= 1<<14)

//I2C clock enable
#define RCC_I2C1_CLK_EN()		(RCC ->APB1ENR |= 1<<21)
#define RCC_I2C2_CLK_EN()		(RCC ->APB1ENR |= 1<<22)
//I2C reset mechanism
#define RCC_I2C1_RESET()		(RCC ->APB1RSTR |= 1<<21)
#define RCC_I2C2_RESET()		(RCC ->APB1RSTR |= 1<<22)

//-*-*-*-*-*-*-*-*-*-*-*
//IVT:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI

#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40

//USART
#define USART1_IRQ		37
#define USART2_IRQ		38
#define USART3_IRQ		39

//SPI
#define SPI1_IRQ		35
#define SPI2_IRQ		36

//I2C
#define I2C1_EV_IRQ		31
#define I2C1_ER_IRQ		32
#define I2C2_EV_IRQ		33
#define I2C2_ER_IRQ		34



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//NVIC ENABLE/DISABLE IRQ Macros:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//EXTI

//ENABLE IRQ
#define NVIC_IRQ6_EXTI0_ENABLE				(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_ENABLE				(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_ENABLE				(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_ENABLE				(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_ENABLE				(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_ENABLE			(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_ENABLE			(NVIC_ISER1 |= 1<<8)
//DISABLE IRQ
#define NVIC_IRQ6_EXTI0_DISABLE				(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_DISABLE				(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_DISABLE				(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_DISABLE				(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_DISABLE			(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DISABLE			(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_DISABLE		(NVIC_ICER1 |= 1<<8)

//USART
//ENABLE IRQ
#define NVIC_IRQ37_USART1_ENABLE			(NVIC_ISER1 |= 1<<(USART1_IRQ - 32)) //37-32
#define NVIC_IRQ38_USART2_ENABLE			(NVIC_ISER1 |= 1<<(USART2_IRQ - 32)) //38-32
#define NVIC_IRQ39_USART3_ENABLE			(NVIC_ISER1 |= 1<<(USART3_IRQ - 32)) //39-32

//DISABLE IRQ
#define NVIC_IRQ37_USART1_DISABLE			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32)) //37-32
#define NVIC_IRQ38_USART2_DISABLE			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32)) //38-32
#define NVIC_IRQ39_USART3_DISABLE			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32)) //39-32

//SPI
//ENABLE IRQ
#define NVIC_IRQ35_SPI1_ENABLE			(NVIC_ISER1 |= 1<<(SPI1_IRQ - 32)) //35-32
#define NVIC_IRQ36_SPI2_ENABLE			(NVIC_ISER1 |= 1<<(SPI2_IRQ - 32)) //36-32

//DISABLE IRQ
#define NVIC_IRQ35_SPI1_DISABLE			(NVIC_ICER1 |= 1<<(SPI1_IRQ - 32)) //35-32
#define NVIC_IRQ36_SPI2_DISABLE			(NVIC_ICER1 |= 1<<(SPI2_IRQ - 32)) //36-32

//I2C
//ENABLE IRQ
#define NVIC_IRQ31_I2C1_EV_ENABLE			(NVIC_ISER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_ENABLE			(NVIC_ISER1 |= 1<<(I2C1_ER_IRQ - 32)) //32-32
#define NVIC_IRQ33_I2C2_EV_ENABLE			(NVIC_ISER1 |= 1<<(I2C2_EV_IRQ - 32)) //33-32
#define NVIC_IRQ34_I2C2_ER_ENABLE			(NVIC_ISER1 |= 1<<(I2C2_ER_IRQ - 32)) //34-32

//DISABLE IRQ
#define NVIC_IRQ31_I2C1_EV_DISABLE			(NVIC_ICER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_DISABLE			(NVIC_ICER1 |= 1<<(I2C1_ER_IRQ - 32)) //32-32
#define NVIC_IRQ33_I2C2_EV_DISABLE			(NVIC_ICER1 |= 1<<(I2C2_EV_IRQ - 32)) //33-32
#define NVIC_IRQ34_I2C2_ER_DISABLE			(NVIC_ICER1 |= 1<<(I2C2_ER_IRQ - 32)) //34-32










#endif /* INC_STM32F103X6_H_ */
