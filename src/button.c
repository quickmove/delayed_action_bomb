#include "button.h"

///////////////////////////
// 脚位定义

#define BTN1_PIN		PIND
#define BTN1_DDR		DDRD
#define BTN1_BIT		5

#define BTN1_PIN		PIND
#define BTN1_DDR		DDRD
#define BTN1_BIT		6

#define BTN1_PIN		PIND
#define BTN1_DDR		DDRD
#define BTN1_BIT		7

///////////////////////////
// 脚位取值

// IO取值
#define VAL_BTN1		BTN1_PIN & (1 << BTN1_BIT)
#define VAL_BTN2		BTN2_PIN & (1 << BTN2_BIT)
#define VAL_BTN3		BTN3_PIN & (1 << BTN3_BIT)


///////////////////////////
// 内部函数声明

void onButton1Click(void);
void onButton2Click(void);
void onButton3Click(void);

void onButton1Hold(void);
void onButton2Hold(void);
void onButton3Hold(void);


//////////////////////////

void ButtonInit(void) {
	BTN1_DDR &= ~(1 << BTN1_BIT);
	BTN2_DDR &= ~(1 << BTN2_BIT);
	BTN3_DDR &= ~(1 << BTN3_BIT);
}


void ButtonStatCheck(void) {

}
