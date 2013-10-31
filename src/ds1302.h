//////////////////////////////
// ds1302����
//////////////////////////////
#ifdef _DS1302_H
#define _DS1302_H

#include <stdint.h>

/**
* ��ʼ��ds1302
*
*/
void DS1302Init(void);

/**
* ��ȡʱ��
*
*/
uint8_t DS1302GetHour(void);
uint8_t DS1302GetMinute(void);
uint8_t DS1302GetSecond(void);

/**
* ����ʱ��
*
*/
void DS1302SetHour(uint8_t hour);
void DS1302SetMinute(uint8_t minute);
void DS1302SetSecond(uint8_t second);


#endif
