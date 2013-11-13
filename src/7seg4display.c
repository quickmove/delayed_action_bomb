#include <avr/io.h>
#include <util/delay.h>

#include "7seg4display.h"
#include "74164.h"


// ==== ��������λ���� ===
// ������4�����ڵĵ�Ƭ��PORT
#define CASCODE_PORT		PORTC
#define CASCODE_DDR			DDRC
// ��������ʼ��λ
#define CASCODE_BIT_0		2

// ��λmask����������ʱȡ������4��˳���λ
// ��������λmask		0111100
#define CASCODE_MASK	0x3c
// ��������λ��umask 	1000011
#define CASCODE_UMASK	0x43


// LED����ʾλ��
const uint8_t LED_NUMBER_DATA[] = { 
							  0xfc, // 0
							  0x60, // 1
							  0xda, // 2
							  0xf2, // 3
							  0x66, // 4
							  0xb6, // 5
							  0xbe, // 6
							  0xe0, // 7
							  0xfe, // 8
							  0xf6	// 9
							 };

uint8_t dotflag = 0;

#define DOT_PORT		PORTD
#define DOT_DDR			DDRD
#define DOT_BIT			3

#define SET_DOT			DOT_PORT |= (1 << DOT_BIT)
#define CLR_DOT			DOT_PORT &= ~(1 << DOT_BIT)


/**
* ����4λ7������ܵ�λ��ƽ���͵�ƽ����
* PORTC ��2λ��ʼ��4λΪ������
*
* position 4λ��7������ܣ���Ϊָ��ĳλ��0��ʼ
*/
void Display7Seg4SetPosition(uint8_t position);


void Display7Seg4Init() {
	uint8_t i = 0;
	for(i = 0; i < 4; i++) {
		CASCODE_DDR |= (1 << (CASCODE_BIT_0 + i));
	}

	DOT_DDR |= (1 << DOT_BIT);
}


void Display7Seg4SetPosition(uint8_t position) {
	uint8_t tmp1 = CASCODE_MASK;
	uint8_t tmp2 = CASCODE_UMASK;

	tmp1 |= CASCODE_PORT;	// ȡ��������λ���ڵ�PORT������λ������tmp1
	tmp2 |= ~(1 << (CASCODE_BIT_0 + position));	//ָ��λ�õ͵�ƽ

	CASCODE_PORT = tmp1 & tmp2;
}

void Display7Seg4SetPositionNumber(uint8_t number, uint8_t position) {
	Display7Seg4SetPosition(position);
	IC164SendData(LED_NUMBER_DATA[number]);
}

void Flash7Seg4Dot(void) {
	if(dotflag) {
		CLR_DOT;
		dotflag = 0;
	}
	else {
		SET_DOT;
		dotflag = 1;
	}
}
