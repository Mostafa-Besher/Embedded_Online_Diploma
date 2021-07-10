/*
 * Utils.h
 *
 * Created: 7/9/2021 12:30:05 AM
 *  Author: mostafa
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define Set_bit(reg, bit_no)		reg |= 1<<bit_no
#define Clear_bit(reg, bit_no)		reg &= ~(1<<bit_no)
#define Toggle_bit(reg, bit_no)		reg ^= 1<<bit_no
#define Read_bit(reg, bit_no)		((reg & 1<<bit_no) >>bit_no)


#endif /* UTILS_H_ */