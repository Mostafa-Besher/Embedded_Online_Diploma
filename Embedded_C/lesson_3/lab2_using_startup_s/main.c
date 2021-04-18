#include "Header_Platform.h"

#define RCC_BASE	0x40021000
#define PORTA_BASE	0x40010800

#define APB2ENB				*((vuint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRH			*((vuint32_t *)(PORTA_BASE + 0x04))
#define GPIOA_ODR			*((vuint32_t *)(PORTA_BASE + 0x0c))

uint8_t g_variables[]={1,2,3};
uint8_t const const_variables[]={1,2,3};
uint32_t bss_var[7];

int main(void)
{
	APB2ENB |= 1<<2;
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;

	while(1)
	{
		vuint32_t i;
		GPIOA_ODR |= 1<<13;
		for(i=0; i<5000; i++);		//delay
		GPIOA_ODR &= ~(1<<13);
		for(i=0; i<5000; i++);		//delay
	}
	return 0;
}