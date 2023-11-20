#pragma once

#include "main.h"

#include <stdint.h>

//void servo_write(UART_HandleTypeDef *huart, uint16_t servo_id, uint16_t angle);

// Valid Servo ids: 0-253
class Servo {
public:
	// Constructor
	Servo(UART_HandleTypeDef *huart_in, uint8_t id_in);

	// Functions
	void init(UART_HandleTypeDef *huart_in, uint8_t id_in);

	void write_angle(uint16_t angle, uint16_t time);

	void read_angle();

	void write_limits(uint16_t min_angle, uint16_t max_angle);

	// TODO: function to update target_angle
//	void update_target_angle();

private:
	UART_HandleTypeDef *huart;
	uint8_t id;
	uint16_t current_angle, target_angle;

};
