/*
 * lcd.c
 *
 * Created: 3/8/2021 2:36:09 PM
 *  Author: Mostafa
 */ 

#include "lcd.h"

#include <stdint.h>

GPIO_Pinconfig_t  pin_cfg;
uint16_t LCD_data_pins[] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,
							GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7};

void delay_ms(uint32_t time)
{
	uint32_t i,j;
	for(i=0; i<time; i++)
		for(j=0; j<255; j++);
}

void lcd_init(void)
{
	delay_ms(20);
	//LCD data set as output
	int i;
	for(i=0; i<8; i++)
	{
		pin_cfg.PinNumber= LCD_data_pins[i];
		pin_cfg.Mode = GPIO_MODE_Output_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd_data_dir, &pin_cfg);
	}

	//set RS SWITCH as output
	pin_cfg.PinNumber = RS;
	pin_cfg.Mode = GPIO_MODE_Output_PP;
	pin_cfg.Output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd_ctrl_dir, &pin_cfg);
	//set RW SWITCH as output
	pin_cfg.PinNumber = RW;
	pin_cfg.Mode = GPIO_MODE_Output_PP;
	pin_cfg.Output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd_ctrl_dir, &pin_cfg);
	//set ENABLE SWITCH as output
	pin_cfg.PinNumber = EN;
	pin_cfg.Mode = GPIO_MODE_Output_PP;
	pin_cfg.Output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd_ctrl_dir, &pin_cfg);
	//clear RS,RW,EN
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, EN, WRITE_PIN_LOW);

	lcd_write_command(0x30);
	delay_ms(10);
	lcd_write_command(0x30);
	delay_ms(1);
	lcd_write_command(0x30);

#ifdef EIGHT_BIT_MODE
//select 8-bit mode
	lcd_write_command(function_set_8bit);
#endif

#ifdef FOUR_BIT_MODE
	//select 4-bit mode
	lcd_write_command(0x02);
	lcd_write_command(function_set_4bit);
	lcd_write_command(0x08);
#endif
	//display off
	lcd_write_command(display_off_cursor_off);
	//clear display
	lcd_clear();
	//entry mode set
	lcd_write_command(Entry_mode);
	//display on cursor blinking
	lcd_write_command(Display_on_Cursor_blinking);
}


void lcd_kick(void)
{
	MCAL_GPIO_WritePin(lcd_ctrl_port, EN, WRITE_PIN_HIGH);
	delay_ms(10);
	MCAL_GPIO_WritePin(lcd_ctrl_port, EN, WRITE_PIN_LOW);
}

void lcd_write_char(unsigned char data)
{
#ifdef EIGHT_BIT_MODE
	lcd_is_busy();
	//make LCD in write mode
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_HIGH);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	//write data
	MCAL_GPIO_WritePort(lcd_data_port, data);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	//lcd_is_busy();
	delay_ms(10);
	//send last four bits of data
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_HIGH);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	unsigned char tmp_data = (data & 0xF0);
	MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
	lcd_kick();
	//send first four bits of data
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_HIGH);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	tmp_data = (data << 4);
	MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
	lcd_kick();
#endif
}

void lcd_write_string(char *str)
{
	int character_counter = 0;
	while(*str != '\0')
	{
		character_counter++;
		if(character_counter == 17)
		{
			//go to second line position 0
			lcd_goto_xy(2,0);
		}
		else if(character_counter > 32)
		{
			//clear display
			lcd_write_command(clear_display);
			//go to first line position 0
			lcd_goto_xy(1,0);
			character_counter = 0;
		}
		lcd_write_char(*str);
		str++;
	}
}

void lcd_is_busy(void)
{
	//make data lines as input
	int i;
	for(i=0; i<8; i++)
	{
		pin_cfg.PinNumber= LCD_data_pins[i];
		pin_cfg.Mode = GPIO_MODE_Input_FLU;
		MCAL_GPIO_Init(lcd_data_dir, &pin_cfg);
	}
	//make LCD in read mode RS = 0, RW = 1
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_HIGH);
	lcd_kick();
	//make data lines as output
	for(i=0; i<8; i++)
	{
		pin_cfg.PinNumber= LCD_data_pins[i];
		pin_cfg.Mode = GPIO_MODE_Output_PP;
		pin_cfg.Output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd_data_dir, &pin_cfg);
	}
}

void lcd_write_command(unsigned char command)
{
#ifdef EIGHT_BIT_MODE
	lcd_is_busy();
	//switch to write mode and select instruction reg to send command
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	MCAL_GPIO_WritePort(lcd_data_port, command);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	//lcd_is_busy();
	delay_ms(10);
	//send last four bits of command
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	char tmp_cmd;
	tmp_cmd = (command & 0xF0);
	MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
	lcd_kick();
	//send first four bits of command
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, WRITE_PIN_LOW);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, WRITE_PIN_LOW);
	tmp_cmd = (command << 4);
	MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
	lcd_kick();
#endif
}


void lcd_goto_xy(int line, int position)
{
	if(line == 1)
	{
		if(position >= 0 && position < 16)
		{
			lcd_write_command(cursor_first_line + position);
		}
	}

	else if (line == 2)
	{
		if(position >= 0 && position < 16)
		{
			lcd_write_command(cursor_second_line + position);
		}
	}
}

void lcd_clear(void)
{
	lcd_write_command(clear_display);
}

void lcd_shift_right(void)
{
	lcd_write_command(shift_display_right);
}


