/*
 * ADC.c
 *
 * Created: 10/20/2021 5:58:27 PM
 *  Author: mostafa
 */ 


/*
 *=======================================================================
 *						INCLUDES
 *=======================================================================
 *
*/

#include "ADC.h"


/*
 *=======================================================================
 *						GLOBAL VARIABLES
 *=======================================================================
 *
*/


ADC_CONFIG_t Global_Config;



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/


/**================================================================
 * @Fn 				-	MCAL_ADC_Init
 * @brief 			-	Initializes ADC according to the specified parameters in ADC_Cfg
 * @param [in] 		- 	ADC_Cfg : a pointer to ADC_CONFIG_t structure that contains
 * 									the configuration information for the specified ADC Module
 * @retval 			-	none
 * Note 			-	Supported for Single conversion mode or Free running mode ONLY
 *					-	ADC requires Clock Between 50khz and 200khz
 *
 */
void MCAL_ADC_Init(ADC_CONFIG_t * ADC_Cfg)
{
	Global_Config = *ADC_Cfg;
	
	//1-Select ADC Mode
	ADCSRA |= ADC_Cfg->ADC_MODE;
	
	//2-Select VREF Source
	ADMUX |= ADC_Cfg->ADC_Voltage_REF;
	
	//3-Select Result Presentation
	ADMUX |= ADC_Cfg->ADC_Result_Presentation;
	
	//4-Select ADC Clock PreScaler
	ADCSRA |= ADC_Cfg->ADC_PRESCALER;
	
	//5-Configure Enable or Disable IRQ
	ADCSRA |= ADC_Cfg->IRQ_Enable;
	if(ADC_Cfg->IRQ_Enable == IRQ_ENABLE_ADIE)
	{
		ENABLE_GLOBAL_INTERRUPT;
	}
	else
	{
		DISABLE_GLOBAL_INTERRUPT;
	}
	
	//6-Enable ADC Module
	Set_bit(ADCSRA, 7);
	
	//7-start Conversion With ADC FREE Running mode
	if(ADC_Cfg->ADC_MODE == ADC_MODE_FREE_RUNNING)
	{
		Set_bit(ADCSRA, 6);
	}
}


/**================================================================
 * @Fn 				-	MCAL_ADC_Start_Conversion
 * @brief 			-	Start ADC conversion in Single conversion mode
 * @param [in] 		- 	none
 * @retval 			-	none
 * Note 			-	only use for Single conversion mode 
 *
 */
void MCAL_ADC_Start_Conversion(void)
{
	if(Global_Config.ADC_MODE == ADC_MODE_SINGLE_CONVERSION)
	{
		Set_bit(ADCSRA, 6);
	}
}


/**================================================================
 * @Fn 				-	MCAL_ADC_Get_Result_Data
 * @brief 			-	Get ADC conversion Result
 * @param [in] 		- 	data : pointer to variable that holds ADC converted data
 * @param [in] 		- 	Polling : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_ADC_Get_Result_Data(Channel_Select_t channel, uint16_t * data, Polling_Mechanism_t Polling)
{
	uint16_t ADCL_VAL, ADCH_VAL;
	
	ADMUX &= ~(0x1F);
	//select ADC Channel
	ADMUX |= ((uint8_t)channel);
	//Configure Selected Channel To be Input
	Clear_bit(DDRA, channel);
	
	//start conversion
	if(Global_Config.ADC_MODE == ADC_MODE_SINGLE_CONVERSION)
	{
		Set_bit(ADCSRA, 6);
	}
	
	//Check for using Polling Mechanism
	if(Polling == Polling_ENABLE)
	{
		//polling for ADIF flag
		while(! (Read_bit(ADCSRA, 4)) );
	}
	
	//Read Converted Data
	if(Global_Config.ADC_Result_Presentation == ADC_Result_Presentation_RIGHT_ADJUSTED)
	{
		ADCL_VAL = ADCL;
		ADCH_VAL = ((ADCH & (0x03)) << 8);
	}
	else if(Global_Config.ADC_Result_Presentation == ADC_Result_Presentation_LEFT_ADJUSTED)
	{
		ADCL_VAL = ((ADCL & (0xC0)) >> 6);
		ADCH_VAL = (ADCH << 2);
	}
	
	*data = (ADCL_VAL |  ADCH_VAL);
	
	//Clear ADIF flag
	Clear_bit(ADCSRA, 4);
}


/**================================================================
 * @Fn 				-	MCAL_ADC_DeInit
 * @brief 			-	Reset ADC Registers
 * @param [in] 		- 	none
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_ADC_DeInit(void)
{
	ADMUX = 0X00;
	ADCSRA = 0X00;
	SFIOR &= ~( (1<<5) | (1<<6) | (1<<7) );
}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

ISR(ADC_vect)
{
	Global_Config.P_CallBack();
}