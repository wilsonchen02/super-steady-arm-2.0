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

/* Send a string of data to the LCD
 * @param data: string to be printed on LCD
 */
void LCD::send_data(std::string data) {
	const char *char_data = data.c_str();
	while(*char_data) {
		send_byte(*char_data++);
	}
}

void LCD::init_servo_labels() {
	std::string s0 = "Robotic Arm Angles";
	std::string s1 = "grip ";
	std::string s2 = "elbo ";
	std::string s3 = "wr_R ";
	std::string s4 = "wr_P ";
	std::string s5 = "sh_P ";
	std::string s6 = "sh_Y ";

	clear_screen();
	HAL_Delay(100);

	// Information header on the first line
	set_cursor(0, 0);
	HAL_Delay(100);
	send_data(s0);
	HAL_Delay(100);

	// Row 1
	set_cursor(1, 0);
	HAL_Delay(100);
	send_data(s1);
	HAL_Delay(100);
	set_cursor(1, 10);
	HAL_Delay(100);
	send_data(s2);
	HAL_Delay(100);

	// Row 2
	set_cursor(2, 0);
	HAL_Delay(100);
	send_data(s3);
	HAL_Delay(100);
	set_cursor(2, 10);
	HAL_Delay(100);
	send_data(s4);
	HAL_Delay(100);

	// Row 3
	set_cursor(3, 0);
	HAL_Delay(100);
	send_data(s5);
	HAL_Delay(100);
	set_cursor(3, 10);
	HAL_Delay(100);
	send_data(s6);
	HAL_Delay(100);
}

/* Send all servo angles to LCD
 * @param arr: pointer to starting element of array
 * @param arr_length: length of array
 */
void LCD::send_servo_angles(uint16_t arr[6]) {
	// Convert uint16_t to string
	std::string str_arr[6];
	for(int i = 0; i < 6; ++i) {
		str_arr[i] = std::to_string(arr[i]);
	}

	// Pad front of string with spaces
	size_t n_zero = 4;
	std::string s1 = std::string(n_zero - std::min(n_zero, str_arr[0].length()), ' ') + str_arr[0];
	std::string s2 = std::string(n_zero - std::min(n_zero, str_arr[3].length()), ' ') + str_arr[3];
	std::string s3 = std::string(n_zero - std::min(n_zero, str_arr[1].length()), ' ') + str_arr[1];
	std::string s4 = std::string(n_zero - std::min(n_zero, str_arr[2].length()), ' ') + str_arr[2];
	std::string s5 = std::string(n_zero - std::min(n_zero, str_arr[4].length()), ' ') + str_arr[4];
	std::string s6 = std::string(n_zero - std::min(n_zero, str_arr[5].length()), ' ') + str_arr[5];

	// Row 1
	set_cursor(1, 5);
	HAL_Delay(100);
	send_data(s1);
	HAL_Delay(100);
	set_cursor(1, 15);
	HAL_Delay(100);
	send_data(s2);
	HAL_Delay(100);

	// Row 2
	set_cursor(2, 5);
	HAL_Delay(100);
	send_data(s3);
	HAL_Delay(100);
	set_cursor(2, 15);
	HAL_Delay(100);
	send_data(s4);
	HAL_Delay(100);

	// Row 3
	set_cursor(3, 5);
	HAL_Delay(100);
	send_data(s5);
	HAL_Delay(100);
	set_cursor(3, 15);
	HAL_Delay(100);
	send_data(s6);
	HAL_Delay(100);
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
