#pragma once

/* The default I2C address of the PCF8574 uses 0x27 for upper 7 bits.
 * This can be configured with pads A0-A2 on the board.
 * LSB dictates R/W.
 *
 * NOTE: this uses the HD44780 LCD controller instruction set:
 * https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
 *
*/
#define LCD_I2C_READ_ADDR 0x4E // LSB = 0
#define LCD_I2C_WRITE_ADDR 0x4F // LSB = 1

// LCD controller commands
#define LCD_CLEAR_DISPLAY 0x1
#define LCD_CURSOR_HOME 0x2
#define LCD_ENTRY_MODE_SET 0x4
#define LCD_DISPLAY_ON_OFF_CTRL 0x8
#define LCD_CURSOR_SHIFT 0x10
#define LCD_FUNCTION_SET 0x20
#define LCD_SET_CGRAM_ADDR 0x40
#define LCD_SET_DDRAM_ADDR 0x80

class LCD {
public:
	// Constructor
	LCD();

	// Functions
	void clear_screen();

	void set_cursor();

	void write();

private:
	I2C_HandleTypeDef *hi2c;
};
