#include "main.h"
#include "servo.h"

#include <vector>

#define NUM_SERVOS 6

extern UART_HandleTypeDef huart1;

void init() {
	//  uint8_t tx_buf[10] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x1E, 0x88, 0x08, 0x00, 0x4B};
	//  uint8_t tx_buf[4][10] = {
	//  // 0 and 1000 for motor 6 joint A (like 70 degrees?)
	//  {0x55, 0x55, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF1},
	//  {0x55, 0x55, 0x06, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x06},
	//  {0x55, 0x55, 0x03, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF4},
	//  {0x55, 0x55, 0x03, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x09}
	//  };

	std::vector<Servo> servo;
	for(int i = 0; i < NUM_SERVOS; ++i) {
		servo.push_back(Servo(&huart1, i+1));
	}

	servo[0].write_angle(500, 0);
	HAL_Delay(1000);
	servo[0].read_angle();
//	servo[0].write_limits(200, 500);
//	HAL_Delay(1000);
//	servo[3].write_angle(300, 0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[0].write_angle(0, 0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[0].write_angle(1000, 0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[0].write_limits(0, 1000);
//	HAL_Delay(1000);
//	servo[0].write_angle(0, 0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[0].write_angle(1000, 0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[2].write_angle(0);	// Goes to max limit
//	HAL_Delay(1000);
//	servo[2].write_angle(1000);
//	HAL_Delay(1000);

	//  uint8_t tx_buf0[0] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x1E, 0x00, 0x00, 0x00, 0xD3};	// id6
	//  uint8_t tx_buf1[1] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x, 0x00, 0x00, 0x00, 0xD3};
	//  uint8_t tx_buf[10] = {0x00, 0x00, 0x00, 0x07, 0x01, 0x1E, 0x00, 0x00, 0x00, 0xD3};

	//  HAL_UART_Transmit(&huart1, tx_buf[2], 10, 50);
	//	HAL_Delay(1000);
	//	HAL_UART_Transmit(&huart1, tx_buf[3], 10, 50);
	//	HAL_Delay(1000);
	//  HAL_UART_Transmit(&huart1, tx_buf[2], 10, 50);
	//  HAL_Delay(1000);
	//  HAL_UART_Transmit(&huart1, tx_buf[3], 10, 50);
	//  HAL_Delay(1000);

}

void loop() {

}
