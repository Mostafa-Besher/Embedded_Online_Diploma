/*
 * keypad.c
 *
 * Created: 7/28/2021 2:35:53 PM
 *  Author: mostafa
 */ 

#include "Keypad_Driver/keypad.h"

void keypad_init(void)
{
	//select rows as input
	KEYPAD_Dir &= ~(1<<R0);
	KEYPAD_Dir &= ~(1<<R1);
	KEYPAD_Dir &= ~(1<<R2);
	KEYPAD_Dir &= ~(1<<R3);
	//activate internal pull-up resistors for rows
	KEYPAD_PORT |= 1<< R0;
	KEYPAD_PORT |= 1<< R1;
	KEYPAD_PORT |= 1<< R2;
	KEYPAD_PORT |= 1<< R3;
	//select columns as output
	KEYPAD_Dir |= 1<<C0;
	KEYPAD_Dir |= 1<<C1;
	KEYPAD_Dir |= 1<<C2;
	KEYPAD_Dir |= 1<<C3;
	//make all columns have logic 1
	KEYPAD_PORT |= 1<<C0;
	KEYPAD_PORT |= 1<<C1;
	KEYPAD_PORT |= 1<<C2;
	KEYPAD_PORT |= 1<<C3;
}

char keypad_get_key(void)
{
	int i, j;
	char col[] = {C0,C1,C2,C3};
	char row[] = {R0,R1,R2,R3};
	char keypad_keys[4][4] = {{'7','8','9','/'},
							  {'4','5','6','*'},	
							  {'1','2','3','-'},
						      {'?','0','=','+'}};
							  
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			//set all columns 
			KEYPAD_PORT |= ( (1<<col[0]) | (1<<col[1]) | (1<<col[2]) | (1<<col[3])) ;
			//clear specific column(make it ground)
			KEYPAD_PORT &= ~(1<<col[i]);
			//check pressed key
			if(Read_bit(KEYPAD_Pin, row[j]) == 0)
			{
				//single pressing
				while(Read_bit(KEYPAD_Pin, row[j]) == 0);
				return keypad_keys[j][i];
			}
		}
	}
	return 'N';
}