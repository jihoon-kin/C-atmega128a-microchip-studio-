
#include "button_2.h"

void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	button->ddr = ddr;
	button->pin = pin;
	button->btnPin = pinNum;
	button->prevState = RELEASED;			// 초기화로 아무것도 안누른 상태
	*button->ddr &= ~(1 << button->btnPin);	// 버튼핀을 입력으로 설정
}
// 변수 세개(ddr, pin, pinNum)를 선언해주고 불러온것
// RELEASED로 시작하겠다(초기화).
// 연산자 최상위 우선순위(->) 엔드에 반전한걸로 1을 밀었으니까 0이 들어간다. 버튼에 버튼핀 3번을 넣어준다고 하면, 3번이 제일 밑에 문장으로 오는거다.

// 버튼의 ddr 과 pin 의 주소를 받기 위해
uint8_t BUTTON_getState(Button *button)
{
	uint8_t curState = *button->pin & (1 << button->btnPin); // and 연산을 통해서 상태를 불러오는것.  // 버튼 현재 상태를 읽어옴
	// 2번핀만큼 1을민다. 2번핀하고 2번핀이 갖고있던 value 값(우리가 모르는 정수값)을 and 연산 건거다. 만약에 (Pull up 상태) 누르면 0이고, 안누르면 1이기때문에 그걸 curState에 넣겠다 라는 말이다.
	if ((curState==PUSHED) && (button->prevState==RELEASED)) // 안누른 상태에서 누르면 // 두개의 조건이 둘다 만족한다면 ~~
	{
		_delay_ms(50);
		button->prevState = PUSHED; // 버튼의 상태를 누른 상태로 변환
		return ACT_PUSHED; // 버튼이 눌렸음을 리턴함
	}
	else if((curState != PUSHED) && (button->prevState==PUSHED)) // 버튼을 누른 상태에서 떼면
	{
		_delay_ms(50);
		button->prevState = RELEASED; // 버튼을 뗀 상태로 변환
		return ACT_RELEASED; // 버튼이 떨어졌음을 반환
	}
	return NO_ACT; // 아무것도 안일어남.... 이전 상태가 현재 상태로 계속 이어지는 중인거다. NO ACTION 말그대로임
}
// 위 코드는 현재 상태를 들고와서 변환을 시키기 위한 코드