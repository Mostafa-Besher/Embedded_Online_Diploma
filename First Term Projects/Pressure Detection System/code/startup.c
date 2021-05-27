//startup.c
//Eng:Mostafa Besher

#include <stdint.h>
//prototypes
extern int main(void);
void Default_handler();
void Reset_handler();
void NMI_handler()__attribute__((weak,alias("Default_handler")));;
void HARD_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
void MM_handler()__attribute__((weak,alias("Default_handler")));;
void BUS_handler()__attribute__((weak,alias("Default_handler")));;
void USAGE_FAULT_handler()__attribute__((weak,alias("Default_handler")));;

//declaration of symbols
extern uint32_t _stack_top;
extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;

//.vectors section 
uint32_t vectors[] __attribute__((section(".vectors"))) = {

	(uint32_t)&_stack_top,
	(uint32_t)&Reset_handler,
	(uint32_t)&NMI_handler,
	(uint32_t)&HARD_FAULT_handler,
	(uint32_t)&MM_handler,
	(uint32_t)&BUS_handler,
	(uint32_t)&USAGE_FAULT_handler
};

void Reset_handler()
{
	uint32_t counter = 0;
	//copy .data from flash to sram
	uint32_t data_size = (unsigned char *)&_E_data - (unsigned char *)&_S_data;
	unsigned char *p_source = (unsigned char *)&_E_text;		//starting address of .data in rom
	unsigned char *p_destination = (unsigned char *)&_S_data;	//starting address of .data in ram
	
	while(counter < data_size)
	{
		*((unsigned char *)p_destination++) = *((unsigned char *)p_source++);
		counter++;
	}
	
	//initialize .bss with zero
	uint32_t bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
	p_destination = (unsigned char *)&_S_bss;
	counter = 0;
	
	while(counter < bss_size)
	{
		*((unsigned char *)p_destination++) = (unsigned char) 0;
		counter++;
	}
	
	//jump to main
	main();
}

void Default_handler()
{
	Reset_handler();
}
