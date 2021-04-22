/* main.c
   toggle led on coretx m4 microcontroller tm4c123
   Eng: Mostafa Besher
*/


#include "Header_Platform.h"

#define SYSCTL_base 0x400FE000
#define GPIOF_base  0x40025000

#define sysctl_RCGC2 		*((vuint32_t *)(SYSCTL_base + 0x108))
#define GPIO_PORTF_DIR_R 	*((vuint32_t *)(GPIOF_base + 0x400))
#define GPIO_PORTF_DEN_R 	*((vuint32_t *)(GPIOF_base + 0x51c))

typedef union
{
	vuint32_t all_fields;
	struct
	{
		vuint32_t reserved : 3;
		vuint32_t pin3 : 1;
	}pin;
	
}GPIO_PORTF_DATA_R;

volatile GPIO_PORTF_DATA_R * portf = (volatile GPIO_PORTF_DATA_R *)(GPIOF_base + (0x3fc));

int main()
{
	vuint32_t delay_counter;
	sysctl_RCGC2 = 0x00000020;
	//delay to make sure GPIOF is up and running
	for(delay_counter = 0; delay_counter < 200; delay_counter++);
	
	GPIO_PORTF_DIR_R |= 1<<3;	//Dir is output for pin3 portf
	GPIO_PORTF_DEN_R |= 1<<3;
	
	while(1)
	{
		portf ->pin.pin3 = 1;
		for(delay_counter = 0; delay_counter < 200000; delay_counter++);	//delay
		portf -> pin.pin3 = 0;
		for(delay_counter = 0; delay_counter < 200000; delay_counter++);	//delay
	}
	return 0;
}

