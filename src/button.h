#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint.h>

// 按键触发回调
// mode键
typedef void (*callback_mode_button_keydown_t) ();
typedef void (*callback_mode_button_keyup_t) ();
typedef void (*callback_mode_button_keybursh_t) ();
typedef void (*callback_mode_button_keyburshup_t) ();

// add键
typedef void (*callback_add_button_keydown_t) ();
typedef void (*callback_add_button_keyup_t) ();
typedef void (*callback_add_button_keybursh_t) ();
typedef void (*callback_add_button_keyburshup_t) ();

// sub键
typedef void (*callback_sub_button_keydown_t) ();
typedef void (*callback_sub_button_keyup_t) ();
typedef void (*callback_sub_button_keybursh_t) ();
typedef void (*callback_sub_button_keyburshup_t) ();

/**
* 初始化控制按钮的管脚
*
*/
void ButtonInit();

/**
 * 按键检测
 */
uint8_t ButtonCheckBtnValue(uint8_t btnIndex);

void ButtonRegisterModeButtonKeyDownFunc(callback_mode_button_keydown_t func);
void ButtonRegisterModeButtonKeyUpFunc(callback_mode_button_keyup_t func);
void ButtonRegisterModeButtonKeyBurshFunc(callback_mode_button_keybursh_t func);
void ButtonRegisterModeButtonKeyBurshUpFunc(callback_mode_button_keyburshup_t func);

void ButtonRegisterAddButtonKeyDownFunc(callback_add_button_keydown_t func);
void ButtonRegisterAddButtonKeyUpFunc(callback_add_button_keyup_t func);
void ButtonRegisterAddButtonKeyBurshFunc(callback_add_button_keybursh_t func);
void ButtonRegisterAddButtonKeyBurshUpFunc(callback_add_button_keyburshup_t func);

void ButtonRegisterSubButtonKeyDownFunc(callback_sub_button_keydown_t func);
void ButtonRegisterSubButtonKeyUpFunc(callback_sub_button_keyup_t func);
void ButtonRegisterSubButtonKeyBurshFunc(callback_sub_button_keybursh_t func);
void ButtonRegisterSubButtonKeyBurshUpFunc(callback_sub_button_keyburshup_t func);

#endif
