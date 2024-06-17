/*
 * LCD_4bit.c
 *
 * Created: 2024-04-11 오후 3:16:34
 * Author : user
 */ 

#include "LCD_4bit.h"
#include <stdio.h>

int main(void)
{
	char buff[30];
	LCD_Init();
	sprintf(buff, "Hello AVR");
	LCD_WriteStringXY(0,0,buff);
	int count = 0;
	
	while (1)
	{
		sprintf(buff, "count : %d", count++);
		LCD_WriteStringXY(1,0,buff);
		_delay_ms(200);
	}
}

