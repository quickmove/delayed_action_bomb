#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "74164.h"
#include "7seg4display.h"
#include "ds1302.h"
#include "button.h"


void onKeyDown(uint8_t btnIndex);
void onKeyUp(uint8_t btnIndex);
void onKeyBursh(uint8_t btnIndex);
void onKeyBurshUp(uint8_t btnIndex);

uint8_t led_number_left = 0;	// 7������ܣ�������ֵ�ֵ
uint8_t led_number_right = 0;	// 7������ܣ��ұ����ֵ�ֵ


/**
* ��ʼ�����豸��Ӧ��Ƭ��I/O��
*
*/
void init() {
	IC164Init();
	Display7Seg4Init();
	DS1302Init();

	ButtonInit();
	// ע�ᰴ���ص�����
	ButtonRegisterKeyDownFunc(onKeyDown);
	ButtonRegisterKeyUpFunc(onKeyUp);
	ButtonRegisterKeyBurshFunc(onKeyBursh);
	ButtonRegisterKeyBurshUpFunc(onKeyBurshUp);
}

int main(void) {
	init();
	DS1302SetSecond(0x58);
	DS1302SetMinute(0x13);
	DS1302SetHour(0);

	uint8_t dotLedCountFlag = 0;
	Flash7Seg4Dot();

	while(1) {
		uint8_t leftnum = DS1302GetHour();
		uint8_t rightnum = DS1302GetMinute();
		uint8_t numbers[4];
	
		numbers[0] = leftnum / 16;
		numbers[1] = leftnum % 16;
		numbers[2] = rightnum / 16;
		numbers[3] = rightnum % 16;
	
		uint8_t i = 0;
		for(i = 0; i < 4; i++) {
			Display7Seg4SetPositionNumber(numbers[i], i);
			_delay_ms(5);
		}

		dotLedCountFlag++;
		if(dotLedCountFlag > 0x20) {
			Flash7Seg4Dot();
			dotLedCountFlag = 0;
		}
	}
}

void onKeyDown(uint8_t btnIndex) {
	if(btnIndex == KEYCODE_MODE) {

	} else if(btnIndex == KEYCODE_ADD) {

	} else if(btnIndex == KEYCODE_SUB) {

	}
}

void onKeyUp(uint8_t btnIndex) {

}

void onKeyBursh(uint8_t btnIndex) {

}

void onKeyBurshUp(uint8_t btnIndex) {

}
