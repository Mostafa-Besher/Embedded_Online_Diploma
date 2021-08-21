/*
 * Unit8_Lesson2_UART.c
 *
 * Created: 8/20/2021 9:00:10 PM
 * Author : MOSTAFA
 */ 

#include "MCAL/GPIO.h"
#include "MCAL/UART.h"
#include "HAL/LCD_Driver/lcd.h"


int main(void)
{
	//char recieved_data;
	char * prec_str;
    lcd_init();
	UART_Init();
	lcd_goto_xy(1,4);
	lcd_write_string("UART TEST");
	lcd_goto_xy(2,0);
	/*Send characters*/
	//UART_send_data('M');
	//UART_send_data('H');
	//UART_send_data('B');
	/*Send string*/
	UART_send_string(" HELLO");
    while (1) 
    {
		/*Receive character and print it on LCD*/
		//recieved_data = UART_recieve_data();
		//lcd_write_char(recieved_data);
		
		/*Receive string and print it on LCD*/
		prec_str = UART_recieve_string();
		lcd_write_string(prec_str);
    }
}

