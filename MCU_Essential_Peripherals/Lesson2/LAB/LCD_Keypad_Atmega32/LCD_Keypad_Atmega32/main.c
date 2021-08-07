/*
 * LCD_Keypad_Atmega32.c
 *
 * Created: 7/28/2021 2:35:53 PM
 * Author : Mostafa
 */ 

#include "LCD_Driver/lcd.h"
#include "Keypad_Driver/keypad.h"

void set_project_start(void)
{
	lcd_clear();
	lcd_write_string("PRESS A KEY");
	lcd_goto_xy(2,0);
}

int main(void)
{
	lcd_init();
	keypad_init();
	lcd_goto_xy(1,0);
	lcd_write_string("PRESS A KEY");
	lcd_goto_xy(2,0);
	char press_key, press_counter = 0;
	while (1)
	{
		
		press_key = keypad_get_key();
		switch(press_key)
		{
			//when pressing clear button
			case '?':
			{
				set_project_start();
				press_counter = 0;
				break;
			}
			//in case of not pressing any key
			case 'N':
			break;
			//when pressing keys
			default:
			{
				press_counter++;
				//check if pressed keys exceeded max LCD columns(16 column)
				if(press_counter >= 16)
				{
					set_project_start();
					press_counter = 0;
				}
				lcd_write_char(press_key);
				break;
			}
		}
	}
}




