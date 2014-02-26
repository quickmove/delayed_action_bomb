#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint.h>

// ���������ص�
typedef void (*callback_keydown_t) (uint8_t btnIndex);
typedef void (*callback_keyup_t) (uint8_t btnIndex);
typedef void (*callback_keybursh_t) (uint8_t btnIndex);
typedef void (*callback_keyburshup_t) (uint8_t btnIndex);


// ����code����(���index)
// key3 ModeButton
#define KEYCODE_MODE	2
// key2 AddButton
#define KEYCODE_ADD	1
// key1 SubButton
#define KEYCODE_SUB	0

/**
* ��ʼ�����ư�ť�Ĺܽ�
*
*/
void ButtonInit();

/**
 * ע��ص�keydown
 */
void ButtonRegisterKeyDownFunc(callback_keydown_t func);
/**
 * ע��ص�keyup
 */
void ButtonRegisterKeyUpFunc(callback_keyup_t func);
/**
 * ע��ص�keybursh
 */
void ButtonRegisterKeyBurshFunc(callback_keybursh_t func);
/**
 * ע��ص�keyburshup
 */
void ButtonRegisterKeyBurshUpFunc(callback_keyburshup_t func);

/**
 * �������
 */
uint8_t ButtonCheckBtnValue(uint8_t btnIndex);


#endif
