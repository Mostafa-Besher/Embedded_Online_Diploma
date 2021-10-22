/*
 * ADC_Lab.c
 *
 * Created: 10/20/2021 5:57:34 PM
 * Author : mostafa
 */ 

#define F_CPU	8000000UL
#include "ADC.h"
#include "lcd.h"
#include <string.h>

/*
uint32_t vinput_mv, Temp;
uint32_t ADC_Data, i = 0, bar_size;


void ADC_Interrupt_CallBack(void)
{
	ADC_Data = ((ADC_Data * 100) / 1023);
	lcd_write_string("PERC :    ");
	lcd_Write_Number((uint16_t)ADC_Data);
	lcd_write_char('%');
	lcd_goto_xy(2,0);
	bar_size = (160 / (1000 / ADC_Data));
	for(i=0; i<bar_size; i++)
	lcd_write_char(0xff);
	_delay_ms(1000);
	lcd_clear();
}
*/


int main(void)
{
	/***************ADC Config When Using Interrupt Mechanism*******************/
	/*
	ADC_CONFIG_t ADC_config;
	ADC_config.ADC_MODE = ADC_MODE_SINGLE_CONVERSION;
	ADC_config.ADC_PRESCALER = ADC_PRESCALER_DIVUDED_BY_64;
	ADC_config.ADC_Result_Presentation = ADC_Result_Presentation_RIGHT_ADJUSTED;
	ADC_config.ADC_Voltage_REF = ADC_Voltage_REF_AVCC;
	ADC_config.IRQ_Enable = IRQ_ENABLE_ADIE;
	ADC_config.P_CallBack = ADC_Interrupt_CallBack;
	MCAL_ADC_Init(&ADC_config);
	*/
	
	/***************ADC Config When Using Polling Mechanism*******************/
	
	uint32_t vinput_mv, Temp;
	uint32_t ADC_Data, i = 0, bar_size;
	ADC_CONFIG_t ADC_config;
	ADC_config.ADC_MODE = ADC_MODE_SINGLE_CONVERSION;
	ADC_config.ADC_PRESCALER = ADC_PRESCALER_DIVUDED_BY_64;
	ADC_config.ADC_Result_Presentation = ADC_Result_Presentation_RIGHT_ADJUSTED;
	ADC_config.ADC_Voltage_REF = ADC_Voltage_REF_AVCC;
	ADC_config.IRQ_Enable = IRQ_ENABLE_NONE;
	ADC_config.P_CallBack = NULL;
	MCAL_ADC_Init(&ADC_config);
    lcd_init();
    while (1) 
    {
			
			/***************ADC PERCENTAGE WITH PROGRESS BAR*******************/
			
		/***************Using Polling Mechanism*******************/
		
		MCAL_ADC_Get_Result_Data(ADC1, &ADC_Data, Polling_ENABLE);
		ADC_Data = ((ADC_Data * 100) / 1023);
		lcd_write_string("PERC :    ");
		lcd_Write_Number((uint16_t)ADC_Data);
		lcd_write_char('%');
		lcd_goto_xy(2,0);
		bar_size = (160 / (1000 / ADC_Data));
		for(i=0; i<bar_size; i++)
			lcd_write_char(0xff);
		_delay_ms(1000);
		lcd_clear();
		
		/***************Using Interrupt Mechanism*******************/
		//MCAL_ADC_Get_Result_Data(ADC1, &ADC_Data, Polling_DISABLE);
		
	
			/***************LM35 TEMPERATURE SENSOR*******************/
		/*
		MCAL_ADC_Get_Result_Data(ADC1, &ADC_Data, Polling_ENABLE);
		vinput_mv = ((ADC_Data * 5000) / 1023);
		Temp = (vinput_mv / 10);
		lcd_write_string("TEMP :  ");
		lcd_Write_Number(Temp);
		lcd_write_string(" C");
		_delay_ms(2000);
		lcd_clear();
		*/
    }
	
}

