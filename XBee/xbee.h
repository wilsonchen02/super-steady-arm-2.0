#ifndef __XBEE_H
#define __XBEE_H

#include <array>
#include <cstdint>
#include <array>
#include "stm32l4xx_hal.h"

class XBee {

private:
	UART_HandleTypeDef* uart_handle;

public:
	XBee(){uart_handle = NULL;};
	XBee(UART_HandleTypeDef* uart_handle_in);
	std::array<float, 3> getCommand();
	std::array<float, 3> getCommand__Test();
	int setCommand(uint8_t joint_ID, float angle); // humanarm class should be responsible for editing this
};


#endif /* __XBEE_H */
