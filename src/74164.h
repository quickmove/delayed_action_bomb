////////////////////////////
// 74164 驱动
////////////////////////////
#ifndef _74164_H
#define _74164_H

#include <stdint.h>

/**
* 初始化164脚位
*
*/
void IC164Init();

/**
* 向74164发送数据
*
* data 数据
*/
void IC164SendData(uint8_t data);


#endif
