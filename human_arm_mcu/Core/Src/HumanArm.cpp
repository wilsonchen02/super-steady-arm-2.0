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
	sensor_info.wrist_roll 		= wrist_configuration[0];
	sensor_info.wrist_pitch		= wrist_configuration[1];
	sensor_info.wrist_yaw 		= wrist_configuration[2];
	sensor_info.enc_angle 		= enc_cur_angle;
	sensor_info.shoulder_roll 	= shoulder_configuration[0];
	sensor_info.shoulder_pitch 	= shoulder_configuration[1];
	sensor_info.shoulder_yaw 	= shoulder_configuration[2];
	return 0;
}

int HumanArm::send_message(){
	// TODO: xbee send code goes here
	// need to send 3 + 1 + 3 floats (wrist, encoder, shoulder) = 7 * 4 = 28 bytes
	uint8_t* buf_tx = reinterpret_cast<uint8_t*>(&sensor_info);
	// TODO: maybe timeout shouldn't be UINT32_max long
	// TODO: currently this is blocking. could use nonblockng ..._Transmit_IT instead
	HAL_UART_Transmit(UART_handle, buf_tx, 28, UINT32_MAX);
	return 0;
}
