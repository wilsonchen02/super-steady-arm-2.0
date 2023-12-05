#include "main.h"
#include "RoboticArm.h"
#include "servo.h"

extern UART_HandleTypeDef huart1;

// for xbee receive
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

extern xbee_buff_t xbee_buff;

// For LCD transmit
extern I2C_HandleTypeDef hi2c1;
static std::unique_ptr<LCD> lcd;
static uint16_t lcd_buf[6];

static std::unique_ptr<RoboticArm> robot_arm;

void init() {
	// Receive xbee angle data
	HAL_UART_Receive_DMA(&huart6, xbee_buff.xbee_buf_8, 12);

	// Initialize Robotic Arm object
	robot_arm = std::make_unique<RoboticArm>();

	// Add and initialize Servo objects in Robotic Arm
	robot_arm->add_servo(&huart1, 1, 300, 656);
	robot_arm->add_servo(&huart1, 2, 0, 1000);
	robot_arm->add_servo(&huart1, 3, 0, 900);
	robot_arm->add_servo(&huart1, 4, 0, 1000);
	robot_arm->add_servo(&huart1, 5, 130, 840);
	robot_arm->add_servo(&huart1, 6, 0, 1000);
	HAL_Delay(100);

	// Initialize LCD
	lcd = std::make_unique<LCD>(&hi2c1);
	HAL_Delay(100);
	lcd->clear_screen();
	HAL_Delay(100);
	lcd->init_servo_labels();
	HAL_Delay(100);

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

	// Update LCD values
	lcd->send_servo_angles(lcd_buf);
}
