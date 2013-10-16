#include <util/delay.h>

#include "7seg4display.h"
#include "74164.h"


// ==== ��������λ���� ===
// ������4�����ڵĵ�Ƭ��PORT
#define CASCODE_PORT		PORTC
#define CASCODE_DDR			DDRC
// ��������ʼ��λ
#define CASCODE_BIT_0		2


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

void init7seg4display() {
	uint8_t i = 0;
	for(i = 0; i < 4; i++) {
		CASCODE_DDR |= (1 << (CASCODE_BIT_0 + i));
	}
}


void set_led_number_position(uint8_t position) {
	uint8_t tmp1 = 0x3c;	// 0111100
	uint8_t tmp2 = 0x43;	// 1000011

	tmp1 |= CASCODE_PORT;	// ȡ��������λ���ڵ�PORT������λ������tmp1
	tmp2 |= ~(1 << (CASCODE_BIT_0 + position));	//ָ��λ�õ͵�ƽ

	CASCODE_PORT = tmp1 & tmp2;
}

void set_led_number(uint8_t number, uint8_t position) {
	set_led_number_position(position);
	send164data(LED_NUMBER_DATA[number]);
}
