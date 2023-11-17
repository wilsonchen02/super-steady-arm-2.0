#pragma once

#include "main.h"

#include <stdint.h>

//void servo_write(UART_HandleTypeDef *huart, uint16_t servo_id, uint16_t angle);

// Valid Servo ids: 0-253
class Servo {
public:
	// Constructor
//	Servo();s

	Servo(UART_HandleTypeDef *huart_in, uint8_t id_in);

	// Functions
	void servo_init(UART_HandleTypeDef *huart_in, uint8_t id_in);

	void servo_write(uint16_t angle);

private:
	UART_HandleTypeDef *huart;
	uint8_t id;


};
