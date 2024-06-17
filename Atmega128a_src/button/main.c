
#include "button_2.h"

int main(void)
{
	LED_DDR = 0xff;
	Button btnOn;
	Button btnOff;
	Button btnToggle;
	
	Button_Init(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);
	Button_Init(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
	Button_Init(&btnToggle, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE);
	
    while (1) // 버튼을 눌렀다가 떼야 조건이 만족해서 출력값이 나오는것, 
    {
		if (BUTTON_getState(&btnOn) == ACT_RELEASED)
		{
			LED_PORT = 0xff;
		}
		if (BUTTON_getState(&btnOff) == ACT_RELEASED)
		{
			LED_PORT = 0x00;
		}
		if (BUTTON_getState(&btnToggle) == ACT_RELEASED)
		{
			LED_PORT ^= 0xff;
		}
    }
}

