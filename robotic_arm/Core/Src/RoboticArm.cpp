#include "RoboticArm.h"


void RoboticArm::add_servo(UART_HandleTypeDef *huart_in, uint8_t id, uint16_t min_angle, uint16_t max_angle) {
	servo.emplace_back(std::make_unique<Servo>(huart_in, id, min_angle, max_angle));
}

void RoboticArm::set_all_angles(const std::vector<uint16_t> &angles) {
	for(int i = 0; i < NUM_SERVOS; ++i) {
		servo[i]->write_angle(angles[i], 0);
	}
}
