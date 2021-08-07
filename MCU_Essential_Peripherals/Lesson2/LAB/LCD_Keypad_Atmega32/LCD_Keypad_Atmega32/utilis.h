/*
 * utilis.h
 *
 * Created: 7/17/2021 2:36:38 PM
 *  Author: mostafa
 */ 


#ifndef UTILIS_H_
#define UTILIS_H_

#define Set_bit(reg, bit_no)		reg |= 1<<bit_no
#define Clear_bit(reg, bit_no)		reg &= ~(1<<bit_no)
#define Toggle_bit(reg, bit_no)		reg ^= 1<<bit_no
#define Read_bit(reg, bit_no)		((reg>>bit_no)&1)



#endif /* UTILIS_H_ */