#include "lcd.h"

// Will do initialization in the constructor too.
// This initialization process comes from the TC2004A datasheet
LCD::LCD(I2C_HandleTypeDef *hi2c_in) :
	hi2c(hi2c_in) {

	// Wait > 40 ms
	HAL_Delay(50);
	send_command(0x30);
	// Wait > 4.1 ms
	HAL_Delay(5);
	send_command(0x30);
	// Wait > 100 us
	HAL_Delay(1);
	send_command(0x30);
	// Enable 4 bit mode
	HAL_Delay(10);
	send_command(0x20);

	// Initialize display
	// 0x28: Set to 4 bit mode, 2 display lines, 5x8 dot display
	HAL_Delay(10);
	send_command(0x28);
	// Turn off display
	HAL_Delay(1);
	send_command(0x08);
	// Clear display
	HAL_Delay(1);
	send_command(0x01);
	// Set entry mode (incremental cursor, no shift
	HAL_Delay(1);
	send_command(0x06);
	// Display on
	HAL_Delay(1);
	send_command(0x0C);
}

/* Sends a command to the LCD. See the HD44780 LCD
 * controller instruction set.
 * @param cmd: command to be sent
 */
void LCD::send_command(char cmd) {
	char data_u, data_l;
	uint8_t cmd_buf[4];

	// 0x0C (0b1100) is to enable backlight and
	data_u = cmd & 0xF0;			// Upper 4 bits
	data_l = (cmd << 4) & 0xF0;		// Lower 4 bits, move to upper 4
	cmd_buf[0] = data_u | 0x0C;
	cmd_buf[1] = data_u | 0x08;
	cmd_buf[2] = data_l | 0x0C;
	cmd_buf[3] = data_l | 0x08;

	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR, (uint8_t *)cmd_buf, 4, 100);
}

/* Sends a byte of data to the LCD.
 * @param data: data to be sent
 */
void LCD::send_byte(const char data) {
	char data_u, data_l;
	uint8_t data_buf[4];

	data_u = data & 0xF0;
	data_l = (data << 4) & 0xF0;
	data_buf[0] = data_u | 0x0D;
	data_buf[1] = data_u | 0x09;
	data_buf[2] = data_l | 0x0D;
	data_buf[3] = data_l | 0x09;

	HAL_I2C_Master_Transmit(hi2c, LCD_I2C_ADDR, (uint8_t *)data_buf, 4, 100);
}

/* Send an array of data to the LCD
 * @param data: string to be printed on LCD
 */
void LCD::send_data(std::string data) {
	const char *char_data = data.c_str();
	while(*char_data) {
		send_byte(*char_data++);
	}
}

/* Wipes the screen
 */
void LCD::clear_screen() {
	send_command(LCD_CLEAR_DISPLAY);
}

/* Sets the cursor to the specified x and y value of the screen (4x20)
 * @param x: row
 * @param y: column
 */
void LCD::set_cursor(uint8_t row, uint8_t col) {
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	char cursor_cmd = (LCD_SET_DDRAM_ADDR | (col + row_offsets[row]));
	send_command(cursor_cmd);
}
