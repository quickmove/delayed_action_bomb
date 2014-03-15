//                   _                    _
//                 /_/\                 /_/\
//                /_/\/      _       _ _\_\/
//               /_/\/     /_/\     /_/_/\
//              /_/\/      \_\/      /_/\/
//             /_/\/         _      /_/\/
//            /_/\/_ _ _   /_/_ _ _/_/\/
//           /_/_/_/_/_/\  \/_/_/_/\_\/  copyright.2014
//           \_\_\_\_\_\/   \_\_\_\/       by linjing
//

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "74164.h"
#include "7seg4display.h"
#include "ds1302.h"
#include "button.h"

// 秒点闪烁LED延时闪烁计数标志阀值
#define DOTLED_FLAG_MAXCOUNT		0x20

// 编辑小时模式
#define IS_EDIT_HOUR_MODE		current_clockmode && !current_editunit
// 编辑分钟模式
#define IS_EDIT_MINUTE_MODE	current_clockmode && current_editunit

///////////////////////////////////////////////////////////////////////////////////////////////////

void onModeButtonKeyUp();
void onModeButtonKeyBursh();
void onModeButtonKeyBurshUp();
void onAddButtonKeyUp();
void onSubButtonKeyUp();

/**
 * 当前时钟模式
 * 0 显示模式 1 编辑模式
 */
uint8_t current_clockmode = 0;
/**
 * 当前编辑单位
 * 0 时, 1 分
 */
uint8_t current_editunit = 0;
/**
 * 7段数码管,小时值
 */
uint8_t led_number_hour = 0;
/**
 * 7段数码管,分钟值
 */
uint8_t led_number_minute = 0;
/**
 * 按键连发标志 0 无, 1 连发中
 */
uint8_t mode_bursh_action_flag = 0;

/**
 * mode 按钮第一次进入连发状态的标志 0 未触发, 1 已触发
 */
uint8_t mode_button_keybursh_first_flag = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 初始化各设备对应单片机I/O口
 *
 */
void init() {

	IC164Init();

	Display7Seg4Init();

	DS1302Init();
	// 设置初始时分秒
	DS1302SetSecond(0);
	DS1302SetMinute(13);
	DS1302SetHour(3);

	ButtonInit();
	ButtonRegisterModeButtonKeyUpFunc(onModeButtonKeyUp);
	ButtonRegisterModeButtonKeyBurshFunc(onModeButtonKeyBursh);
	ButtonRegisterModeButtonKeyBurshUpFunc(onModeButtonKeyBurshUp);
	ButtonRegisterAddButtonKeyUpFunc(onAddButtonKeyUp);
	ButtonRegisterSubButtonKeyUpFunc(onSubButtonKeyUp);

}

int main(void) {
	init();

	// 秒点闪烁led延时标志计数
	uint8_t dotLedFlagCount = 0;

	while (1) {

		if (!current_clockmode) {
			led_number_hour = DS1302GetHour();
			led_number_minute = DS1302GetMinute();
		}

		// 模式及显示处理

		uint8_t numbers[4];

		// 编辑小时,闪烁小时的两个数字
		if (!Display7Seg4GetFlashDotFlag() && IS_EDIT_HOUR_MODE) {
			numbers[0] = 10;
			numbers[1] = 10;
		} else {
			numbers[0] = led_number_hour / 10;
			numbers[1] = led_number_hour % 10;
		}
		// 编辑分钟,闪烁分钟的两个数字
		if (!Display7Seg4GetFlashDotFlag() && IS_EDIT_MINUTE_MODE) {
			numbers[2] = 10;
			numbers[3] = 10;
		} else {
			numbers[2] = led_number_minute / 10;
			numbers[3] = led_number_minute % 10;
		}

		// 按LED数字位扫描显示
		uint8_t i = 0;
		for (i = 0; i < 4; i++) {
			Display7Seg4SetPositionNumber(numbers[i], i);
			_delay_ms(5);
		}

		// 秒点闪烁处理
		dotLedFlagCount++;
		if (dotLedFlagCount > DOTLED_FLAG_MAXCOUNT) {
			Display7Seg4FlashDot();
			dotLedFlagCount = 0;
		}

		// 按键扫描
		for (i = 0; i < 3; i++) {
			ButtonByIndexScan(i);
		}

	}
}

/**
 * 单击 mode 按钮
 *
 * 编辑模式下，切换编辑 时或分
 * 显示模式下，无操作
 *
 */
void onModeButtonKeyUp() {
	if (current_clockmode) { // 编辑模式下
		current_editunit = !current_editunit; // 切换时分
	}
}

/**
 * mode 按钮按住不放
 *
 * 按住不放，即连发触发时，需做个标志，表示已经触发
 * 在连发释放(burshup)后，解除该标志；
 * 连发触发的调用执行完成后也解除该标志，避免未操作完成时释放。
 *
 * 编辑模式下，写入ds1302，后切换到显示模式
 *
 * 显示模式下，切换到编辑模式
 *
 */

void onModeButtonKeyBursh() {
	// 触发进入标志
	if (!mode_button_keybursh_first_flag) {
		mode_button_keybursh_first_flag = 1;

		if (current_clockmode) {
			DS1302SetHour(led_number_hour);
			DS1302SetMinute(led_number_minute);
			DS1302SetSecond(0);
		}
		current_clockmode = !current_clockmode;
	}

}

/**
 * mode 按钮按钮按住不放后的释放
 * 解除标志
 */
void onModeButtonKeyBurshUp() {
	mode_button_keybursh_first_flag = 0;
}

/**
 * 等同于add 按钮 click
 * 编辑模式下,加小时或者分钟
 *
 */
void onAddButtonKeyUp() {
	if (IS_EDIT_HOUR_MODE) {
		led_number_hour++;
		if (led_number_hour > 23) {
			led_number_hour = 0;
		}
	} else if (IS_EDIT_MINUTE_MODE) {
		led_number_minute++;
		if (led_number_minute > 59) {
			led_number_minute = 0;
		}
	}
}

/**
 * 等同于 sub 按钮 click
 * 编辑模式下,减小时或者分钟
 */
void onSubButtonKeyUp() {
	if (IS_EDIT_HOUR_MODE) {
		if (led_number_hour == 0) {
			led_number_hour = 23;
		} else {
			led_number_hour--;
		}
	} else if (IS_EDIT_MINUTE_MODE) {
		if (led_number_minute == 0) {
			led_number_minute = 59;
		} else {
			led_number_minute--;
		}
	}
}
