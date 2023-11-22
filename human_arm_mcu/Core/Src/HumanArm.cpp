#include <HumanArm.h>
#include <stdio.h>


int HumanArm::init(){
	this->wrist_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_LO);
	this->shoulder_IMU = std::make_unique<IMU>(I2C_handle, IMU_ADDR_HI);
	this->elbow_encoder = std::make_unique<Encoder>(TIM_handle);
}

int HumanArm::spin(){
	float enc_cur_angle = elbow_encoder->get_position();

	std::vector<double> wrist_configuration;
	wrist_IMU->getEulerAngles(wrist_configuration);
	std::vector<double> shoulder_configuration;
	shoulder_IMU->getEulerAngles(shoulder_configuration);

	pack_message(wrist_configuration, enc_cur_angle, shoulder_configuration);
	send_message();
	return 0;
}

int HumanArm::pack_message(std::vector<double> wrist_configuration, float enc_cur_angle, std::vector<double>shoulder_configuration){
	printf("current_encoder_angle: %f\n", enc_cur_angle);
	return 0;
}

int HumanArm::send_message(){
	// TODO: xbee send code goes here
	return -1;
}
