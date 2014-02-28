//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

// 共阴4位7段数码管 显示控制
// 7段数据 调用74164驱动 做串并转化
// 注：此段程序仅支持 共阴的4位接在单片机某PORT的其中4位，不支持跨PORT

#ifndef _7_SEG_4_DISPLAY_H
#define _7_SEG_4_DISPLAY_H

#include <stdint.h>

void Display7Seg4Init();
void Display7Seg4SetPositionNumber(uint8_t number, uint8_t position);
void Flash7Seg4Dot();


#endif
