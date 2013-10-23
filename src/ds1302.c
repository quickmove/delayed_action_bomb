#include <avr/io.h>
#include <util/delay.h>

#include "ds1302.h"

///////////////////////////
// ds1302��λ���� 

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
// ds1302��λ����

#define SET_DS1302_RST		DS1302_RST_PORT |= (1 << DS1302_RST_BIT)
#define CLR_DS1302_RST		DS1302_RST_PORT &= ~(1 << DS1302_RST_BIT)

#define SET_DS1302_CLK		DS1302_CLK_PORT |= (1 << DS1302_CLK_BIT)
#define CLR_DS1302_CLK		DS1302_CLK_PORT &= ~(1 << DS1302_CLK_BIT)

// IO��ֵ
#define SET_DS1302_IO		DS1302_IO_PORT |= (1 << DS1302_IO_BIT)
#define CLR_DS1302_IO		DS1302_IO_PORT &= ~(1 << DS1302_IO_BIT)
// IOȡֵ
#define VAL_DS1302_IO		DS1302_IO_PIN & (1 << DS1302_IO_BIT)

// ����IO ��/д
#define DS1302_IO_WRITE		DS1302_IO_DDR |= (1 << DS1302_IO_BIT)
#define DS1302_IO_READ		DS1302_IO_DDR &= ~(1 << DS1302_IO_BIT)



//////////////////////////
// ��������

/**
* ��һ���ֽ�����
*
*/
uint8_t DS1302ReadByte(void);

/**
* дһ���ֽ�����
*
*/
void DS1302WriteByte(uint8_t data);

/**
* дds1302�Ĵ���
*
*/
void DS1302WriteReg(uint8_t addr, uint8_t data);

/**
* ��ds1302�Ĵ���
*
*/
uint8_t DS1302ReadReg(uint8_t addr);


/////////////////////////////

void DS1302Init(void) {
	DS1302_RST_DDR |= (1 << DS1302_RST_BIT);
	DS1302_CLK_DDR |= (1 << DS1302_CLK_BIT);
	DS1302_IO_DDR |= (1 << DS1302_IO_BIT);
}


uint8_t DS1302ReadByte(void) {
	uint8_t ret = 0;
	
	// ���ö�
	DS1302_IO_READ;

	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		ret >>= 1;
		if(VAL_DS1302_IO) {
			ret |= 0x80;
		}

		// ʱ������~�½�
		SET_DS1302_CLK;
		CLR_DS1302_CLK;
	}

	// �ָ�д
	DS1302_IO_WRITE;
	return ret;
}

void DS1302WriteByte(uint8_t data) {
	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		if(data&0x01)
			SET_DS1302_IO;
		else
			CLR_DS1302_IO;

		// ʱ������~�½�
		SET_DS1302_CLK;
		CLR_DS1302_CLK;

		data >>= 1;
	}
}

void DS1302WriteReg(uint8_t addr, uint8_t data) {
	CLR_DS1302_RST;

	CLR_DS1302_CLK;
	SET_DS1302_RST;

	DS1302WriteByte(addr);
	DS1302WriteByte(data);

	SET_DS1302_CLK;
	CLR_DS1302_RST;
}

uint8_t DS1302ReadReg(uint8_t addr) {
	uint8_t ret = 0;

	CLR_DS1302_RST;
	CLR_DS1302_CLK;
	SET_DS1302_RST;
	DS1302WriteByte(addr|0x01);
	ret = DS1302ReadByte();

	SET_DS1302_CLK;
	CLR_DS1302_RST;
	
	return ret;
}


