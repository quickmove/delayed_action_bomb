//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

// 常规的三个按键 mode, +, -
// 长按按键，带有连发功能， 按键均带有down up bursh burshup 4个事件，需预注册事件回调

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


void ButtonInit();

void ButtonCheckBtnValue(uint8_t btnIndex);


// 注册键盘回调
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
