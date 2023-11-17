#pragma once

#include "stm32f4xx_hal.h"

#include <stdint.h>
#include <array>

// Valid Servo ids: 0-253
class Servo {
public:
	// Constructors
	Servo();

	Servo(UART_HandleTypeDef *huart_in, uint8_t id_in);

	// Enum for

	// Functions
	bool compare_checksum();

	void read_servo(uint8_t);

	void write_servo();
private:
	UART_HandleTypeDef *huart;
	uint8_t id;
	uint8_t tx_buffer[10];

};
