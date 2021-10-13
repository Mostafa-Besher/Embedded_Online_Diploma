/*
 * GPIO.h
 *
 * Created: 8/20/2021 9:01:20 PM
 *  Author: MOSTAFA
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#define DDRA	*((volatile unsigned char *)(0x3A))
#define PORTA	*((volatile unsigned char *)(0x3B))
#define PINA	*((volatile unsigned char *)(0x39))
#define DDRC	*((volatile unsigned char *)(0x34))
#define PORTC	*((volatile unsigned char *)(0x35))
#define PINC	*((volatile unsigned char *)(0x33))
#define DDRD	*((volatile unsigned char *)(0x31))
#define PORTD	*((volatile unsigned char *)(0x32))
#define PIND	*((volatile unsigned char *)(0x30))



//UTILITS
#define Set_bit(reg, bit_no)		reg |= 1<<bit_no
#define Clear_bit(reg, bit_no)		reg &= ~(1<<bit_no)
#define Toggle_bit(reg, bit_no)		reg ^= 1<<bit_no
#define Read_bit(reg, bit_no)		((reg>>bit_no)&(0x01))



#endif /* GPIO_H_ */