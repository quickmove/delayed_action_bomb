//////////////////////////////
// ds1302����
//////////////////////////////
#ifndef _DS1302_H
#define _DS1302_H

#include <stdint.h>

/**
* ��ʼ��ds1302
*
*/
void DS1302Init();

/**
* ��ȡʱ��
*
*/
uint8_t DS1302GetHour();
uint8_t DS1302GetMinute();
uint8_t DS1302GetSecond();

/**
* ����ʱ��
*
*/
void DS1302SetHour(uint8_t hour);
void DS1302SetMinute(uint8_t minute);
void DS1302SetSecond(uint8_t second);


#endif
