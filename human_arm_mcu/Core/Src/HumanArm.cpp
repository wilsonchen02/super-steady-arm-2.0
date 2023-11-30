#include <HumanArm.h>
#include <stdio.h>


int HumanArm::init(){
	this->wrist_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_LO);
	this->shoulder_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_HI);
	this->elbow_encoder = std::make_unique<Encoder>(TIM_handle);
	return 0;
}

int HumanArm::spin(){
	float enc_cur_angle = elbow_encoder->get_position();

	std::vector<float> wrist_configuration;
	wrist_IMU->getEulerAngles(wrist_configuration);
	std::vector<float> shoulder_configuration;
	shoulder_IMU->getEulerAngles(shoulder_configuration);

	pack_message(wrist_configuration, enc_cur_angle, shoulder_configuration);
	send_message();
	return 0;
}

int HumanArm::pack_message(std::vector<float> wrist_configuration, float enc_cur_angle, std::vector<float> shoulder_configuration){
	printf("current_encoder_angle: %f\n", enc_cur_angle);
	// TODO: Fill these with actual values depending on input angles;
	/*
	sensor_info.servo0 = ;
	sensor_info.servo1 = ;
	sensor_info.servo2 = ;
	sensor_info.servo3 = ;
	sensor_info.servo4 = ;
	sensor_info.servo5 = ;
	*/
	return 0;
}

int HumanArm::send_message(){
	// Sending 6 * 2 (uint16_t) bytes
	SensorData sensor_info_test = {0xFF33, 0xEE11, 0xDD22, 0xCC33, 0xBB44, 0xAA55};
	uint8_t* buf_tx = reinterpret_cast<uint8_t*>(&sensor_info_test);
	HAL_UART_Transmit(UART_handle, buf_tx, 12, UINT32_MAX);
	return 0;
}
