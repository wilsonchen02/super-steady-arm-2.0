#pragma once

/* The default I2C address of the PCF8574 uses 0x27 for upper 7 bits.
 * This can be configured with pads A0-A2 on the board.
 * LSB dictates R/W.
 *
 * NOTE: this uses the HD44780 LCD controller instruction set:
 * https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
 *
 * Macros from Arduino library
*/

#include "stm32f4xx_hal.h"
#include <string>
#include <algorithm>

#define LCD_I2C_ADDR 0x4E // LSB = 0

// LCD controller commands
#define LCD_CLEAR_DISPLAY 0x1
#define LCD_CURSOR_HOME 0x2
#define LCD_ENTRY_MODE_SET 0x4
#define LCD_DISPLAY_ON_OFF_CTRL 0x8
#define LCD_CURSOR_SHIFT 0x10
#define LCD_FUNCTION_SET 0x20	// 4 bit by default
#define LCD_SET_CGRAM_ADDR 0x40
#define LCD_SET_DDRAM_ADDR 0x80

// LCD Entry Mode Flags
#define LCD_ENTRY_INCREMENT 0x02 // text direction goes right
#define LCD_ENTRY_DECREMENT 0x00 // text direction goes left
#define LCD_ENTRY_SHIFT 0x01	 // enable shift

// LCD Display Flags
#define LCD_DISPLAY_ON 0x04
#define LCD_DISPLAY_OFF 0x00
#define LCD_CURSOR_ON 0x02
#define LCD_CURSOR_OFF 0x00
#define LCD_BLINK_ON 0x01
#define LCD_BLINK_OFF 0x00

// LCD Function Set Flags
#define LCD_FUNCTION_8BIT 0x10
#define LCD_FUNCTION_4BIT 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10_DOTS 0x04
#define LCD_5x8_DOTS 0x00

// LCD Backlight Flags
#define LCD_BACKLIGHT 0x08
#define LCD_NO_BACKLIGHT 0x00

class LCD {
public:
	// Constructor
	LCD(I2C_HandleTypeDef *hi2c_in);

	// Functions
	void send_command(char cmd);

	void send_byte(const char data);

	void send_data(std::string data);

	void init_servo_labels();

	void send_servo_angles(uint16_t arr[6]);

	void clear_screen();

	void set_cursor(uint8_t row, uint8_t col);

private:
	I2C_HandleTypeDef *hi2c;
};
