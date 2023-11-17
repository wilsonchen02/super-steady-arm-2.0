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
void Servo::servo_init(UART_HandleTypeDef *huart_in, uint8_t id_in) {
	huart = huart_in;
	id = id_in;
}


/* Given servo ID and an angle from range 0-1000 of the servo's software limits,
 * move the servo to the corresponding angle
 * @param servo_id: servo to move
 * @param angle: angle metric range 0-1000 that the servo is to go to
 */
void Servo::servo_write(uint16_t angle) {
	if (angle > 1000 || angle < 0) {
//		throw std::runtime_error("angle out of range");
		return;
	}
//	float angle_ratio = angle / 1000.0;
	uint8_t angle_low = angle & 0xFF;
	uint8_t angle_high = (angle >> 8) & 0xFF;
	// This should constrain sum to 16 bits
	uint16_t sum = id + angle_low + angle_high + 0x7 + 0x1;
	sum = ~sum & 0xFF;
	uint8_t tx_buf[10] = {0x55, 0x55, id, 0x7, 0x1, angle_low, angle_high, 0x0, 0x0, sum};
	HAL_UART_Transmit(huart, tx_buf, 10, 50);
}

/* Given servo ID and two angles from range 0-1000,
 * set the min and max angle limits
 * @param servo_id: servo to move
 * @param min_angle: min angle for servo in range 0-1000
 * @param max_angle: max angle for servo in range 0-1000
 */
//void servo_write_limits(uint16_t servo_id, uint16_t min_angle, uint16_t max_angle) {
//	if (min_angle > 1000 || min_angle < 0 || max_angle > 1000 || max_angle < 0) {
//		return;
//	}
//	uint8_t angle_low = angle & 0xFF;
//	uint8_t angle_high = (angle >> 8) & 0xFF;
//}
