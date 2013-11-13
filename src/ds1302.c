#include <avr/io.h>
#include <util/delay.h>

#include "ds1302.h"

///////////////////////////
// ds1302脚位设置 

#define DS1302_RST_PORT		PORTD
#define DS1302_RST_DDR		DDRD
#define DS1302_RST_BIT		0

#define DS1302_CLK_PORT		PORTD
#define DS1302_CLK_DDR		DDRD
#define DS1302_CLK_BIT		1

#define DS1302_IO_PORT		PORTD
#define DS1302_IO_PIN		PIND
#define DS1302_IO_DDR		DDRD
#define DS1302_IO_BIT		2


////////////////////////////
// ds1302脚位操作

#define SET_DS1302_RST		DS1302_RST_PORT |= (1 << DS1302_RST_BIT)
#define CLR_DS1302_RST		DS1302_RST_PORT &= ~(1 << DS1302_RST_BIT)

#define SET_DS1302_CLK		DS1302_CLK_PORT |= (1 << DS1302_CLK_BIT)
#define CLR_DS1302_CLK		DS1302_CLK_PORT &= ~(1 << DS1302_CLK_BIT)

// IO赋值
#define SET_DS1302_IO		DS1302_IO_PORT |= (1 << DS1302_IO_BIT)
#define CLR_DS1302_IO		DS1302_IO_PORT &= ~(1 << DS1302_IO_BIT)
// IO取值
#define VAL_DS1302_IO		(DS1302_IO_PIN & (1 << DS1302_IO_BIT))

// 设置IO 读/写
#define DS1302_IO_WRITE		DS1302_IO_DDR |= (1 << DS1302_IO_BIT)
#define DS1302_IO_READ		DS1302_IO_DDR &= ~(1 << DS1302_IO_BIT)

//////////////////////////
// 寄存器地址
#define ADDR_READ_SECOND		0x81
#define ADDR_WRITE_SECOND		0x80
#define ADDR_READ_MINUTE		0x83
#define ADDR_WRITE_MINUTE		0x82
#define ADDR_READ_HOUR			0x85
#define ADDR_WRITE_HOUR			0x84



//////////////////////////
// 函数声明

/**
* 读一个字节数据
*
*/
uint8_t readByte(void);

/**
* 写一个字节数据
*
*/
void writeByte(uint8_t data);

/**
* 写ds1302寄存器
*
*/
void writeReg(uint8_t addr, uint8_t data);

/**
* 读ds1302寄存器
*
*/
uint8_t readReg(uint8_t addr);


/////////////////////////////


uint8_t readByte(void) {
	uint8_t ret = 0;
	
	// 设置读
	DS1302_IO_READ;

	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		ret >>= 1;
		if(VAL_DS1302_IO) {
			ret |= 0x80;
		}

		// 时钟上升~下降
		SET_DS1302_CLK;
		CLR_DS1302_CLK;
	}

	// 恢复写
	DS1302_IO_WRITE;
	return ret;
}

void writeByte(uint8_t data) {
	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		if(data&0x01)
			SET_DS1302_IO;
		else
			CLR_DS1302_IO;

		// 时钟上升~下降
		SET_DS1302_CLK;
		CLR_DS1302_CLK;

		data >>= 1;
	}
}

void writeReg(uint8_t addr, uint8_t data) {
	CLR_DS1302_RST;

	CLR_DS1302_CLK;
	SET_DS1302_RST;

	writeByte(addr);
	writeByte(data);

	SET_DS1302_CLK;
	CLR_DS1302_RST;
}

uint8_t readReg(uint8_t addr) {
	uint8_t ret = 0;

	CLR_DS1302_RST;
	CLR_DS1302_CLK;
	SET_DS1302_RST;
	writeByte(addr|0x01);
	ret = readByte();

	SET_DS1302_CLK;
	CLR_DS1302_RST;
	
	return ret;
}

///////////////////////////////////////////////////////


void DS1302Init() {
	DS1302_RST_DDR |= (1 << DS1302_RST_BIT);
	DS1302_CLK_DDR |= (1 << DS1302_CLK_BIT);
	DS1302_IO_DDR |= (1 << DS1302_IO_BIT);
}

void DS1302SetHour(uint8_t hour) {
	writeReg(ADDR_WRITE_HOUR, hour);
}
void DS1302SetMinute(uint8_t minute) {
	writeReg(ADDR_WRITE_MINUTE, minute);
}
void DS1302SetSecond(uint8_t second) {
	writeReg(ADDR_WRITE_SECOND, second);
}

uint8_t DS1302GetHour(void) {
	return readReg(ADDR_READ_HOUR);
}
uint8_t DS1302GetMinute(void) {
	return readReg(ADDR_READ_MINUTE);
}
uint8_t DS1302GetSecond(void) {
	return readReg(ADDR_READ_SECOND);
}

