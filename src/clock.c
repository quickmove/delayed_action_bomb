/*         
         _                    _
       /_/\                 /_/\
      /_/\/      _       _ _\_\/
     /_/\/     /_/\     /_/_/\
    /_/\/      \_\/      /_/\/
   /_/\/         _      /_/\/
  /_/\/_ _ _   /_/_ _ _/_/\/
 /_/_/_/_/_/\  \/_/_/_/\_\/  copyright.2014
 \_\_\_\_\_\/   \_\_\_\/       by linjing

*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "74164.h"
#include "7seg4display.h"
#include "ds1302.h"
#include "button.h"

// �����˸LED��ʱ��˸������־��ֵ
#define DOTLED_FLAG_MAXCOUNT		0x20

///////////////////////////////////////////////////////////////////////////////////////////////////

void onModeButtonKeyUp();
void onModeButtonKeyBursh();

/**
 * ��ǰʱ��ģʽ
 * 0 ��ʾģʽ 1 �༭ģʽ
 */
uint8_t current_clockmode = 0;
/**
 * ��ǰ�༭��λ
 * 0 ʱ, 1 ��
 */
uint8_t current_editunit = 0;
/**
 * 7�������,Сʱֵ
 */
uint8_t led_number_hour = 0;
/**
 * 7�������,����ֵ
 */
uint8_t led_number_minute = 0;
/**
 * ����������־ 0 ��, 1 ������
 */
uint8_t mode_bursh_action_flag = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * ��ʼ�����豸��Ӧ��Ƭ��I/O��
 *
 */
void init() {

	IC164Init();

	Display7Seg4Init();

	DS1302Init();
	// ���ó�ʼʱ����
	DS1302SetSecond(0x00);
	DS1302SetMinute(0x13);
	DS1302SetHour(0x03);

	ButtonInit();
	ButtonRegisterModeButtonKeyUpFunc(onModeButtonKeyUp);
	ButtonRegisterModeButtonKeyBurshFunc(onModeButtonKeyBursh);

}

int main(void) {
	init();

	// �����˸led��ʱ��־����
	uint8_t dotLedFlagCount = 0;

	// ����༭ģʽ
//	current_clockmode = 1;
	// ����ֱ༭ģʽ
//	current_editunit = 1;

	while (1) {

		// ģʽ����ʾ����
		led_number_hour = DS1302GetHour();
		led_number_minute = DS1302GetMinute();
		uint8_t numbers[4];

		if(!Display7Seg4GetFlashDotFlag() && current_clockmode && !current_editunit) {
			numbers[0] = 10;
			numbers[1] = 10;
		} else {
			numbers[0] = led_number_hour / 16;
			numbers[1] = led_number_hour % 16;
	
		}
		if(!Display7Seg4GetFlashDotFlag() && current_clockmode && current_editunit) {
			numbers[2] = 10;
			numbers[3] = 10;
		} else {
			numbers[2] = led_number_minute / 16;
			numbers[3] = led_number_minute % 16;
		}

		uint8_t i = 0;
		for (i = 0; i < 4; i++) {
			Display7Seg4SetPositionNumber(numbers[i], i);
			_delay_ms(5);
		}

		// ��㴦��
		dotLedFlagCount++;
		if (dotLedFlagCount > DOTLED_FLAG_MAXCOUNT) {
			Display7Seg4FlashDot();
			dotLedFlagCount = 0;
		}

		// ��������
		for(i=0; i < 3; i++) {
			ButtonCheckBtnValue(i);
		}

	}
}

/**
 * ���� mode ��ť
 *
 * �༭ģʽ�£��л��༭ ʱ���
 * ��ʾģʽ�£��޲���
 *
 */
void onModeButtonKeyUp() {
	if (current_clockmode) { // �༭ģʽ��
		current_editunit = !current_editunit; // �л�ʱ��
	}
}

/**
 * mode ��ť��ס����
 *
 * ��ס���ţ�����������ʱ����������־����ʾ�Ѿ�����
 * �������ͷ�(burshup)�󣬽���ñ�־��
 * ���������ĵ���ִ����ɺ�Ҳ����ñ�־������δ�������ʱ�ͷš�
 *
 * �༭ģʽ�£�д��ds1302�����л�����ʾģʽ
 *
 * ��ʾģʽ�£��л����༭ģʽ
 *
 */
void onModeButtonKeyBursh() {
	// ���������־

	if (current_clockmode) {
		DS1302SetHour(led_number_hour);
		DS1302SetMinute(led_number_minute);
		DS1302SetSecond(0);
	}
	current_clockmode = !current_clockmode;

}
