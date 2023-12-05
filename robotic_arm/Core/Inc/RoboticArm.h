#pragma once

#include "main.h"
#include "servo.h"
#include "lcd.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <memory>

#define NUM_SERVOS 6

class RoboticArm {
public:
	// Public variables
	// TODO: place this in private after we integrate xbee
	std::vector<std::unique_ptr<Servo>> servo;

	// Functions
	// Add new servo to arm
	void add_servo(UART_HandleTypeDef *huart_in, uint8_t id, uint16_t min_angle, uint16_t max_angle);

	// TODO: take in an array/vector of servo angles (will come from xbee's get_buff() func)
	void set_all_angles(const std::vector<uint16_t> &angles);

private:
	// Private variables
};
