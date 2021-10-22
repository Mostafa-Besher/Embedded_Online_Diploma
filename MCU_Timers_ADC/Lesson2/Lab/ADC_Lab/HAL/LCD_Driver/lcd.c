/*
 * lcd.c
 *
 * Created: 7/28/2021 2:35:53 PM
 *  Author: Mostafa
 */ 

#include "LCD_Driver/lcd.h"


void lcd_init(void)
{
	_delay_ms(20);
	//LCD data set as output
	lcd_data_dir |= (0xFF << Data_shift);
	//set RS,RW,E as output
	Set_bit(lcd_ctrl_dir, EN);
	Set_bit(lcd_ctrl_dir, RS);
	Set_bit(lcd_ctrl_dir, RW);
	lcd_ctrl_port &= ~((1 << EN) | (1 << RS) | (1 << RW));
	lcd_write_command(0x30);
	_delay_ms(10);
	lcd_write_command(0x30);
	_delay_us(200);
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
	Set_bit(lcd_ctrl_port, EN);
	_delay_ms(20);
	Clear_bit(lcd_ctrl_port, EN);
}

void lcd_write_char(unsigned char data)
{
	#ifdef EIGHT_BIT_MODE
	lcd_is_busy();
	//make LCD in write mode
	set_RS;
	clear_RW;
	//write data
	lcd_data_port = data;
	lcd_kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
	//lcd_is_busy();
	_delay_ms(10);
	//send last four bits of data
	set_RS;
	clear_RW;
	lcd_data_port = ((lcd_data_port & 0x0F) | (data & 0xF0));
	lcd_kick();
	//send first four bits of data
	set_RS;
	clear_RW;
	lcd_data_port = ((lcd_data_port & 0x0F) | (data << 4));
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
	lcd_data_dir &= ~(0xFF<<Data_shift);
	//make LCD in read mode RS = 0, RW = 1
	Clear_bit(lcd_ctrl_port, RS);	
	Set_bit(lcd_ctrl_port, RW);	
	lcd_kick();
	//make data lines as output
	lcd_data_dir |= (0xFF<<Data_shift);
}

void lcd_write_command(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE	
	lcd_is_busy();
	//switch to write mode and select instruction reg to send command
	clear_RS;
	clear_RW;
	lcd_data_port = command;
	lcd_kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
	//lcd_is_busy();
	_delay_ms(10);
	//send last four bits of command
	clear_RS;
	clear_RW;
	lcd_data_port = ((lcd_data_port & 0x0F) | (command & 0xF0));
	lcd_kick();
	//send first four bits of command
	clear_RS;
	clear_RW;
	lcd_data_port = ((lcd_data_port & 0x0F) | (command << 4));
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


void lcd_Write_Number(unsigned int number)
{
	unsigned int num_length = 0, i = 0,temp_num = number, rem ;
	char str_arr[11];
	//Calculate Length of number
	while(temp_num != 0)
	{
		temp_num /= 10;
		num_length++;
	}
	//split each digit of number
	//temp_num = number;
	for(i=0; i<num_length; i++)
	{
		rem = number % 10;
		number = number / 10;
		str_arr[num_length - (i+1)] = rem + '0';	
	}
	str_arr[i] = '\0';
	lcd_write_string(str_arr);
}