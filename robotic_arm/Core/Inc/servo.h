#pragma once

#include "main.h"

#include <stdint.h>

// Valid Servo ids: 0-253
class Servo {
public:
	// Constructor
	Servo(UART_HandleTypeDef *huart_in, uint8_t id_in, uint16_t min_angle, uint16_t max_angle);

	// Functions
	void read_angle();

	void write_angle(uint16_t angle, uint16_t time);

	void write_limits(uint16_t min_angle, uint16_t max_angle);

private:
	UART_HandleTypeDef *huart;
	uint8_t id;
	uint16_t min_angle, max_angle;

};
