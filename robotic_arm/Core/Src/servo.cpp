#include "servo.h"

#include <vector>

/* Constructor for servo
 * @param huart_in: pointer to UART handler
 * @param id_in: ID of the servo
 */
Servo::Servo(UART_HandleTypeDef *huart_in, uint8_t id_in) :
	huart(huart_in), id(id_in) {}

/* Initialize private variables for servo
 * @param huart_in: pointer to UART handler
 * @param id_in: ID of the servo
 */
void Servo::init(UART_HandleTypeDef *huart_in, uint8_t id_in) {
	huart = huart_in;
	id = id_in;
}


/* Given an angle from range 0-1000 of the servo's software limits
 * and time it takes to get to that angle (between 0 - 30k ms),
 * move the servo to the corresponding angle
 * @param servo_id: servo to move
 * @param angle: angle metric range 0-1000 that the servo is to go to
 * @param time: time between 0-30k ms that the servo takes to get to angle
 */
void Servo::write_angle(uint16_t angle, uint16_t time) {
	// Return if input angles are invalid
	if (angle > 1000 || angle < 0) {
//		throw std::runtime_error("angle out of range");
		return;
	}
//	float angle_ratio = angle / 1000.0;
	// This should constrain sum to 16 bits
	uint8_t angle_low = angle & 0xFF;
	uint8_t angle_high = (angle >> 8) & 0xFF;
	uint8_t time_low = time & 0xFF;
	uint8_t time_high = (time >> 8) & 0xFF;
	uint8_t data_length = 0x7;
	uint8_t command_val = 0x1;
	uint16_t sum = id + data_length + command_val + angle_low + angle_high;
	sum = ~sum & 0xFF;
	uint8_t tx_buf[10] = {0x55, 0x55, id, data_length, command_val, angle_low, angle_high, 0x0, 0x0, sum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);

	// Update current_angle
	current_angle = angle;
}

void Servo::read_angle() {
	uint8_t data_length = 0x3;
	uint8_t command_val = 0x2;
	uint16_t sum = id + data_length + command_val;
	uint8_t tx_buf[6] = {0x55, 0x55, id, data_length, command_val, sum};
	sum = ~sum & 0xFF;
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);
}

/* Given servo ID and two angles from range 0-1000,
 * set the min and max angle limits
 * @param servo_id: servo to move
 * @param min_angle: min angle for servo in range 0-1000
 * @param max_angle: max angle for servo in range 0-1000
 */
void Servo::write_limits(uint16_t min_angle, uint16_t max_angle) {
	// Return if input angles are invalid
	if (min_angle > 1000 || min_angle < 0 || max_angle > 1000 || max_angle < 0) {
		return;
	}

	uint8_t min_angle_low = min_angle & 0xFF;
	uint8_t min_angle_high = (min_angle >> 8) & 0xFF;
	uint8_t max_angle_low = max_angle & 0xFF;
	uint8_t max_angle_high = (max_angle >> 8) & 0xFF;
	uint8_t data_length = 0x7;
	uint8_t command_val = 0x14;
	uint16_t sum = id + data_length + command_val + min_angle_low + min_angle_high + max_angle_low + max_angle_high;
	sum = ~sum & 0xFF;
	uint8_t tx_buf[10] = {0x55, 0x55, id, data_length, command_val, min_angle_low, min_angle_high, max_angle_low, max_angle_high, sum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);
}
