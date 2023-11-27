#include "Servo.h"
#include <vector>

/* Constructor for servo
 * @param huart_in: pointer to UART handler
 * @param id_in: ID of the servo
 * @param min_angle: min val of servo's limit (using the servo's range system)
 * @param max_angle: max val of servo's limit (using the servo's range system)
 */
Servo::Servo(UART_HandleTypeDef *huart_in, uint8_t id_in, uint16_t min_angle, uint16_t max_angle) :
	huart(huart_in), id(id_in), min_angle(min_angle), max_angle(max_angle) {
	write_limits(min_angle, max_angle);
}

/* Read angle of servo
 * NOTE: This is only for debugging purposes with the logic analyzer,
 * the nucleo is not receiving the return packet
 */
void Servo::read_angle() {
	uint8_t data_length = 0x3;
	uint8_t command_val = 28;
	uint16_t sum = id + data_length + command_val;
	uint16_t neg_sum = ~sum;
	if (sum > 255){
		neg_sum = ~(0xFF&sum);
	}
	uint8_t checksum = (uint8_t)neg_sum;
	uint8_t tx_buf[6] = {0x55, 0x55, id, data_length, command_val, checksum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);
}

void Servo::read_limits() {
	uint8_t data_length = 0x3;
	uint8_t command_val = 21;
	uint16_t sum = id + data_length + command_val;
	uint16_t neg_sum = ~sum;
	if (sum > 255){
		neg_sum = ~(0xFF&sum);
	}
	uint8_t checksum = (uint8_t)neg_sum;
	uint8_t tx_buf[6] = {0x55, 0x55, id, data_length, command_val, checksum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);
}


/* Given an input angle from range 0-1000, translate that to the servo's
 * own range and set the time it takes to get to that angle (between 0 - 30k ms),
 * move the servo to the corresponding angle
 * @param angle: angle metric range 0-1000 that the servo is to go to
 * @param time: time between 0-30k ms that the servo takes to get to angle
 */
void Servo::write_angle(uint16_t angle, uint16_t time) {
	// Return if input angles are invalid
	if (angle > max_angle || angle < min_angle) {
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
//	sum = ~(sum & 0xFF);
	uint16_t neg_sum = ~sum;
	if (sum > 255){
		neg_sum = ~(0xFF & sum);
	}
	uint8_t checksum = (uint8_t)neg_sum;
	uint8_t tx_buf[10] = {0x55, 0x55, id, data_length, command_val, angle_low, angle_high, 0x0, 0x0, checksum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);
}

/* Given servo ID and two angles from range 0-1000,
 * set the min and max angle limits.
 * NOTE: angle limits can be negative
 * @param min_angle: min angle for servo in range 0-1000
 * @param max_angle: max angle for servo in range 0-1000
 */
void Servo::write_limits(uint16_t min_angle, uint16_t max_angle) {
	// Return if input angles are invalid
//	if (min_angle > 1000 || min_angle < 0 || max_angle > 1000 || max_angle < 0) {
//		return;
//	}

	uint8_t min_angle_low = min_angle & 0xFF;
	uint8_t min_angle_high = (min_angle >> 8) & 0xFF;
	uint8_t max_angle_low = max_angle & 0xFF;
	uint8_t max_angle_high = (max_angle >> 8) & 0xFF;
	uint8_t data_length = 0x7;
	uint8_t command_val = 0x14;
	uint16_t sum = id + data_length + command_val + min_angle_low + min_angle_high + max_angle_low + max_angle_high;
	uint16_t neg_sum = ~sum;
	if (sum > 255){
		neg_sum = ~(0xFF & sum);
	}
	uint8_t checksum = (uint8_t)neg_sum;
	uint8_t tx_buf[10] = {0x55, 0x55, id, data_length, command_val, min_angle_low, min_angle_high, max_angle_low, max_angle_high, checksum};
	HAL_UART_Transmit(huart, tx_buf, data_length + 3, 50);

	// Update min and max angle limits
	this->min_angle = min_angle;
	this->max_angle = max_angle;
}
