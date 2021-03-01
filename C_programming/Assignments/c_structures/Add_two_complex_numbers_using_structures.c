/*
 * Add_two_complex_numbers_using_structures.c
 *
 *  Created on: Feb 28, 2021
 *      Author: mostafa
 */

#include <stdio.h>
struct scomplex Add_complex(struct scomplex c1, struct scomplex c2);

struct scomplex
{
	float real;
	float imaginary;
}gcomplex1, gcomplex2, gsum;

int main()
{
	printf("Enter 1st complex number : \n");
	printf("Enter real and imaginary respectively :");
	fflush(stdin);	fflush(stdout);
	scanf("%f%f", &gcomplex1.real, &gcomplex1.imaginary);

	printf("Enter 2nd complex number : \n");
	printf("Enter real and imaginary respectively :");
	fflush(stdin);	fflush(stdout);
	scanf("%f%f", &gcomplex2.real, &gcomplex2.imaginary);

	gsum = Add_complex(gcomplex1, gcomplex2);
	printf("Sum = %.1f + %.1fi", gsum.real, gsum.imaginary);
	return 0;
}

struct scomplex Add_complex(struct scomplex c1, struct scomplex c2)
{
	struct scomplex sum;

	sum.real = c1.real + c2.real;
	sum.imaginary = c1.imaginary + c2.imaginary;
	return sum;
}

