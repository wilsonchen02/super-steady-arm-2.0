#pragma once

#include "main.h"
#include "Servo.h"
#include <stdint.h>
#include <vector>
#include <memory>

#define NUM_SERVOS 6

class RoboticArm {
public:
	// Public variables
	// TODO: place this in private after we integrate xbee
	std::vector<std::unique_ptr<Servo>> servo;

	// Constructor
//	RoboticArm();

	// Functions
	// Add new servo to arm
	void add_servo(UART_HandleTypeDef *huart_in, uint8_t id, uint16_t min_angle, uint16_t max_angle);

	// TODO: function to read xbee vals and send write to servos
	void read_xbee_angles();

	void set_all_angles();

private:
	// Private variables
	// Servo angles (0-1000, received from xbee) to write
	std::vector<uint16_t> servo_angles;
};
