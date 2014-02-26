#include <avr/io.h>
#include <stdint.h>

#include "button.h"

// ����
#define KEYSTATE_IDLE					0
// �ȴ�����ȷ��(����)
#define KEYSTATE_WAIT_DOWN_VALID		1
// �ȴ������ͷ�
#define KEYSTATE_WAIT_DOWN_RELEASE		2
// �ȴ������ͷ�
#define KEYSTATE_WAIT_BURST_RELEASE	3

///////////////////////////
// ��λ����

#define BTN1_PIN		PIND
#define BTN1_DDR		DDRD
#define BTN1_BIT		5

#define BTN2_PIN		PIND
#define BTN2_DDR		DDRD
#define BTN2_BIT		6

#define BTN3_PIN		PIND
#define BTN3_DDR		DDRD
#define BTN3_BIT		7

///////////////////////////
// ��λȡֵ

// IOȡֵ
//#define VAL_BTN1		(BTN1_PIN & (1 << BTN1_BIT))
//#define VAL_BTN2		(BTN2_PIN & (1 << BTN2_BIT))
//#define VAL_BTN3		(BTN3_PIN & (1 << BTN3_BIT))

// ��������ڰ���1��bitλ��ƫ����Ϊindex��...
// �����е���ֵ�д��û�ҵ�����д����...
#define BTN_GLOBAL_PIN		PIND
#define VAL_BTN(index)		(BTN_GLOBAL_PIN & (1 << (BTN1_BIT + index)))

// ��������������ڵ�0������
#define KEYINDEX_MODE_BUTTON	2
#define KEYINDEX_ADD_BUTTON	1
#define KEYINDEX_SUB_BUTTON	0

// mode����صĻص����
callback_mode_button_keydown_t modeBtnKeyDownFunc;
callback_mode_button_keyup_t modeBtnKeyUpFunc;
callback_mode_button_keybursh_t modeBtnKeyBurshFunc;
callback_mode_button_keyburshup_t modeBtnKeyBurshUpFunc;

// add����صĻص����
callback_add_button_keydown_t addBtnKeyDownFunc;
callback_add_button_keyup_t addBtnKeyUpFunc;
callback_add_button_keybursh_t addBtnKeyBurshFunc;
callback_add_button_keyburshup_t addBtnKeyBurshUpFunc;

// sub����صĻص����
callback_sub_button_keydown_t subBtnKeyDownFunc;
callback_sub_button_keyup_t subBtnKeyUpFunc;
callback_sub_button_keybursh_t subBtnKeyBurshFunc;
callback_sub_button_keyburshup_t subBtnKeyBurshUpFunc;

void ButtonInit() {
	BTN1_DDR &= ~(1 << BTN1_BIT);
	BTN2_DDR &= ~(1 << BTN2_BIT);
	BTN3_DDR &= ~(1 << BTN3_BIT);

}

static uint8_t _keystate[] = { 0, 0, 0 };

uint8_t ButtonCheckBtnValue(uint8_t btnIndex) {

	uint8_t ret = 0;

	switch (_keystate[btnIndex]) {
	case KEYSTATE_IDLE:
		if (!VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_VALID;
		}
		break;
	case KEYSTATE_WAIT_DOWN_VALID:
		if (VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_IDLE;
		} else {
			_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_RELEASE;
			// keydown
			if (btnIndex == KEYINDEX_MODE_BUTTON) {
				if (modeBtnKeyDownFunc)
					modeBtnKeyBurshFunc();
			} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
				if (addBtnKeyDownFunc)
					addBtnKeyDownFunc();
			} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
				if (subBtnKeyDownFunc)
					subBtnKeyDownFunc();
			}
		}
		break;
	case KEYSTATE_WAIT_DOWN_RELEASE:
		if (!VAL_BTN(btnIndex)) {
			ret = 2;
			_keystate[btnIndex] = KEYSTATE_WAIT_BURST_RELEASE;
		} else {
			_keystate[btnIndex] = KEYSTATE_IDLE;
			// keyup
			if (btnIndex == KEYINDEX_MODE_BUTTON) {
				if (modeBtnKeyUpFunc)
					modeBtnKeyUpFunc();
			} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
				if (addBtnKeyUpFunc)
					addBtnKeyUpFunc();
			} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
				if (subBtnKeyUpFunc)
					subBtnKeyUpFunc();
			}
		}
		break;
	case KEYSTATE_WAIT_BURST_RELEASE:
		//TODO: �Ӹ���ʱ������Ȼ���ڴ�bursh
		//bursh
		if (btnIndex == KEYINDEX_MODE_BUTTON) {
			if (modeBtnKeyBurshFunc)
				modeBtnKeyBurshFunc();
		} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
			if (addBtnKeyBurshFunc)
				addBtnKeyBurshFunc();
		} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
			if (subBtnKeyBurshFunc)
				subBtnKeyBurshFunc();
		}

		if (VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_IDLE;
			// burshup
			if (btnIndex == KEYINDEX_MODE_BUTTON) {
				if (modeBtnKeyBurshUpFunc)
					modeBtnKeyBurshUpFunc();
			} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
				if (addBtnKeyBurshUpFunc)
					addBtnKeyBurshUpFunc();
			} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
				if (subBtnKeyBurshUpFunc)
					subBtnKeyBurshUpFunc();
			}
		}
		break;
	}
	return ret;
}

void ButtonRegisterModeButtonKeyDownFunc(callback_mode_button_keydown_t func) {
	modeBtnKeyDownFunc = func;
}
void ButtonRegisterModeButtonKeyUpFunc(callback_mode_button_keyup_t func) {
	modeBtnKeyUpFunc = func;
}
void ButtonRegisterModeButtonKeyBurshFunc(callback_mode_button_keybursh_t func) {
	modeBtnKeyBurshFunc = func;
}
void ButtonRegisterModeButtonKeyBurshUpFunc(
		callback_mode_button_keyburshup_t func) {
	modeBtnKeyBurshUpFunc = func;
}

void ButtonRegisterAddButtonKeyDownFunc(callback_add_button_keydown_t func) {
	addBtnKeyDownFunc = func;
}

void ButtonRegisterAddButtonKeyUpFunc(callback_add_button_keyup_t func) {
	addBtnKeyUpFunc = func;
}
void ButtonRegisterAddButtonKeyBurshFunc(callback_add_button_keybursh_t func) {
	addBtnKeyBurshFunc = func;
}

void ButtonRegisterAddButtonKeyBurshUpFunc(
		callback_add_button_keyburshup_t func) {
	addBtnKeyBurshUpFunc = func;
}

void ButtonRegisterSubButtonKeyDownFunc(callback_sub_button_keydown_t func) {
	subBtnKeyDownFunc = func;
}

void ButtonRegisterSubButtonKeyUpFunc(callback_sub_button_keyup_t func) {
	subBtnKeyUpFunc = func;
}

void ButtonRegisterSubButtonKeyBurshFunc(callback_sub_button_keybursh_t func) {
	subBtnKeyBurshFunc = func;
}

void ButtonRegisterSubButtonKeyBurshUpFunc(
		callback_sub_button_keyburshup_t func) {
	subBtnKeyBurshUpFunc = func;
}
