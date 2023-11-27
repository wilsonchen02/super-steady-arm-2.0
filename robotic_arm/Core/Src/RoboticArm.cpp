#include "RoboticArm.h"

void RoboticArm::add_servo(UART_HandleTypeDef *huart_in, uint8_t id, uint16_t min_angle, uint16_t max_angle) {
	servo.emplace_back(std::make_unique<Servo>(huart_in, id, min_angle, max_angle));
}

void read_xbee_angles() {

}

void RoboticArm::set_all_angles() {
	for(int i = 0; i < NUM_SERVOS; ++i) {
		servo[i]->write_angle(servo_angles[i], 0);
	}
}
