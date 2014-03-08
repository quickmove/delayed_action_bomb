//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

// ds1302驱动

#ifndef _DS1302_H
#define _DS1302_H

#include <stdint.h>

/**
* 初始化ds1302
*
*/
void DS1302Init();

/**
* 获取时间
*
*/
uint8_t DS1302GetHour();
uint8_t DS1302GetMinute();
uint8_t DS1302GetSecond();

/**
* 设置时间
*
*/
void DS1302SetHour(uint8_t hour);
void DS1302SetMinute(uint8_t minute);
void DS1302SetSecond(uint8_t second);


#endif
