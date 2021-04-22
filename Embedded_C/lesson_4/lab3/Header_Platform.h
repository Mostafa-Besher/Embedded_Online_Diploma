/*
 * Header_Platform.h
 *
 *  Created on: Mar 30, 2021
 *      Author: mostafa
 */

#ifndef HEADER_PLATFORM_H_
#define HEADER_PLATFORM_H_


#define CPU_TYPE		CPU_TYPE_32
#define CPU_BIT_ORDER	MSB_FIRST
#define CPU_BYTE_ORDER	HIGH_BYTE_FIRST

typedef unsigned char		uint8_t;
typedef signed char			sint8_t;
typedef unsigned short		uint16_t;
typedef signed short 		sint16_t;
typedef unsigned int		uint32_t;
typedef signed int			sint32_t;
typedef unsigned long long	uint64_t;
typedef signed long	long	sint64_t;
typedef float				float32_t;
typedef double				float64_t;

typedef volatile unsigned char			vuint8_t;
typedef volatile signed char			vsint8_t;

typedef volatile unsigned short			vuint16_t;
typedef volatile signed short 			vsint16_t;

typedef volatile unsigned int			vuint32_t;
typedef volatile signed int				vsint32_t;

typedef volatile unsigned long long		vuint64_t;
typedef volatile signed long long 		vsint64_t;

typedef volatile float					vfloat32_t;
typedef volatile double					vfloat64_t;


#endif /* HEADER_PLATFORM_H_ */
