#include "main.h"
#include "RoboticArm.h"
#include "servo.h"

extern UART_HandleTypeDef huart1;

// for xbee receive
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

extern xbee_buff_t xbee_buff;

static std::unique_ptr<RoboticArm> robot_arm;

void init() {
	HAL_UART_Receive_DMA(&huart6, xbee_buff.xbee_buf_8, 12);
	//  uint8_t tx_buf[10] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x1E, 0x88, 0x08, 0x00, 0x4B};
	//  uint8_t tx_buf[4][10] = {
	//  // 0 and 1000 for motor 6 joint A (like 70 degrees?)
	//  {0x55, 0x55, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF1},
	//  {0x55, 0x55, 0x06, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x06},
	//  {0x55, 0x55, 0x03, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF4},
	//  {0x55, 0x55, 0x03, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x09}
	//  };

//	servo.emplace_back(std::make_unique<Servo>(&huart1, 1, 282, 656));
//	servo.emplace_back(std::make_unique<Servo>(&huart1, 2, 63, 842));
	Eigen::AngleAxisd rollAngle(0, Eigen::Vector3d::UnitZ());
	robot_arm = std::make_unique<RoboticArm>();

	robot_arm->add_servo(&huart1, 1, 300, 656);
	robot_arm->add_servo(&huart1, 2, 0, 1000);
	robot_arm->add_servo(&huart1, 3, 0, 900);
	robot_arm->add_servo(&huart1, 4, 0, 1000);
	robot_arm->add_servo(&huart1, 5, 130, 840);
	robot_arm->add_servo(&huart1, 6, 0, 1000);
	HAL_Delay(1000);

//	for (size_t i = 0; i < robot_arm->servo.size(); ++i) {
//		robot_arm->servo[i]->write_angle(0, 0);
//		HAL_Delay(1000);
//	}
//	robot_arm->servo[1]->write_angle(0, 0);
//	HAL_Delay(1000);
//	robot_arm->servo[1]->write_angle(500, 0);
//	HAL_Delay(1000);
//	robot_arm->servo[1]->write_angle(1000, 0);
//	HAL_Delay(1000);
//	robot_arm->servo[4]->write_angle(135, 0);
//	HAL_Delay(1000);
}

void loop() {
	std::vector<uint16_t> scaled_input_angles(std::begin(xbee_buff.xbee_buf_16), std::end(xbee_buff.xbee_buf_16));
//	robot_arm->set_all_angles(scaled_input_angles);
	robot_arm->servo[3]->write_angle(xbee_buff.xbee_buf_16[3], 0);
	HAL_Delay(50);

//	robot_arm->servo[2]->read_angle();
//	HAL_Delay(1000);
}
