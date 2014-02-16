#include "74164.h"

#include <avr/io.h>


// ==== 164��λ���� ====

#define CP164_PORT		PORTB
#define CP164_DDR		DDRB
#define CP164_BIT		0

#define DATA164_PORT	PORTB
#define DATA164_DDR		DDRB
#define DATA164_BIT		1


// ==== 164��λ���� ====

// 164ʱ��
#define SET_CP164		CP164_PORT |= (1 << CP164_BIT)
#define CLR_CP164		CP164_PORT &= ~(1 << CP164_BIT)

// 164����
#define SET_DATA164		DATA164_PORT |= (1 << DATA164_BIT)
#define CLR_DATA164		DATA164_PORT &= ~(1 << DATA164_BIT)


void IC164Init() {
	CP164_DDR |= (1 << CP164_BIT);
	DATA164_DDR |= (1 << DATA164_BIT);
}

void IC164SendData(uint8_t data) {
	
	uint8_t i = 7;
	for(i = 0; i < 8; i++) {
		
		if((1 << i) & data)
			SET_DATA164;
		else
			CLR_DATA164;

		CLR_CP164;
		SET_CP164;
		
	}
}
