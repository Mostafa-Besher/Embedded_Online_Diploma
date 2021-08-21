/*
 * lcd.h
 *
 * Created: 7/28/2021 2:35:53 PM
 *  Author: Mostafa
 */ 


#ifndef LCD_H_
#define LCD_H_

#define  F_CPU	1000000UL
#include <util/delay.h>
//#include "utilis.h"
#include "GPIO.h"

//LCD modes
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

//LCD_conrol
#define lcd_data_dir		DDRC
#define lcd_data_port		PORTC
#define lcd_data_pin		PINC
#define lcd_ctrl_dir		DDRD
#define lcd_ctrl_port		PORTD
#define RS					2
#define RW					3
#define EN					4
#define Data_shift			4		/*change it to (zero) when using 8-bit mode OR (4) in 4-bit mode*/

//Utilites
#define clear_RS			Clear_bit(lcd_ctrl_port, RS)
#define set_RS				Set_bit(lcd_ctrl_port, RS)
#define clear_RW			Clear_bit(lcd_ctrl_port, RW)
#define set_RW				Set_bit(lcd_ctrl_port, RW)

//LCD commands
#define clear_display					0x01
#define cursor_first_line				0x80
#define cursor_second_line				0xc0
#define cursor_line1_pos3				0x83
#define activate_second_line			0x3c
#define second_line_pos1				0xc1
#define function_set_8bit				0x38
#define function_set_4bit				0x28
#define Entry_mode						0x06
#define display_off_cursor_off			0x08
#define display_on_cursor_on			0x0e
#define display_on_cursor_off			0x0c
#define Display_on_Cursor_blinking		0x0f
#define shift_display_left				0x18
#define shift_display_right				0x1c
#define move_cursor_left_one_char		0x10
#define move_cursor_right_one_char		0x14



//APIS
void lcd_init(void);
void lcd_is_busy(void);
void lcd_write_command(unsigned char command);
void lcd_write_char(unsigned char data);
void lcd_write_string(char *str);
void lcd_goto_xy(int line, int position);
void lcd_clear(void);
void lcd_shift_right(void);

#endif /* LCD_H_ */