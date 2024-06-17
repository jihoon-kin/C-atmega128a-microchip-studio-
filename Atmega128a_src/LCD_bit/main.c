/*
 * LCD_8bit.c
 *
 * Created: 2024-04-11 오전 10:37:29
 * Author : user
 */ 

 #include "LCD.h"
 #include <stdio.h>
 int main(void)
 {
	 //LCD_WriteString("Hello LCD");
	 //LCD_GotoXY(1,0);
	 //LCD_WriteString("Hello AVR");
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
