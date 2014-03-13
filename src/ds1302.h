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

// ds1302驱动

#ifndef _DS1302_H
#define _DS1302_H

#include <stdint.h>


void DS1302Init();

uint8_t DS1302GetHour();
uint8_t DS1302GetMinute();
uint8_t DS1302GetSecond();

void DS1302SetHour(uint8_t hour);
void DS1302SetMinute(uint8_t minute);
void DS1302SetSecond(uint8_t second);


#endif
